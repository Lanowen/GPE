#pragma once

#include <boost\asio.hpp>
#include <boost\smart_ptr.hpp>
#include <boost\array.hpp>
#include <boost\thread.hpp>
#include <list>
#include <deque>
#include <vector>

#include <boost\serialization\serialization.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost\serialization\vector.hpp>
#include <boost\serialization\binary_object.hpp>
#include <boost\archive\text_iarchive.hpp>
#include <boost\archive\text_oarchive.hpp>
//#include <boost/archive/binary_oarchive.hpp>
//#include <boost/archive/binary_iarchive.hpp>
#include <ostream>
#include <iostream>
//#include <boost\any.hpp>
#include <random>
#include <map>

#include <SerializeableData.hpp>

#include <boost/serialization/split_free.hpp>

//#include <boost\serialization\void_cast.hpp>

//#include <BaseTsd.h>

#include <Util.hpp>

namespace GPENet {

	#define MAXBUFFSIZE 65507
	//#define SERVER_PORT 1775

	
	typedef unsigned int UINT32;
	typedef unsigned char BYTE;

	#define MAXUINT32 ((UINT32)~((UINT32)0))

	enum UPDATE_TYPE {
		NONE = 0,
		PING = 44516,
		PONG,
		REQUEST_CONNECT,
		CONNECT,
		DISCONNECT,
		E_LAST
	};

	enum DatagramImportance {
		UNRELIABLE,
		RELIABLE_ORDERED, 
		RELIABLE_UNORDERED
	};

	class Datagram {
	public:
		UINT32 updateType;
		UINT32 importance;
		UINT32 senderid;
		UINT32 sequenceID;
		UINT32 ack;
		UINT32 ack_bitfield;
		boost::shared_ptr<SerializableData> data;		

		template<class T>
		boost::shared_ptr<T> getData(){
			return boost::shared_polymorphic_downcast<T, SerializableData>(data);
		}

	public:
		Datagram() : updateType(UPDATE_TYPE::NONE), senderid(0), importance(DatagramImportance::UNRELIABLE), sequenceID(0), ack(0), ack_bitfield(), data(new SerializableData()) /* TODO: Make this a static obj so its not allocated all the time */ {

		}

		virtual ~Datagram() {

		}

	private:
		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive & ar, const unsigned int version){
			ar & updateType;
			ar & importance;
			ar & senderid;
			ar & sequenceID;			
			ar & ack;
			ar & ack_bitfield;
			ar & data;
		}
	};

	using namespace boost::asio::ip;

	class HistoryEntry{
		friend class OrderedDatagamHistory;
		friend std::map<UINT32, HistoryEntry>;

	private:
		HistoryEntry() {}
		
	public:

		HistoryEntry(Datagram datagram, time_t sendTime) : datagram(datagram), sendTime(sendTime){
		}

		virtual ~HistoryEntry(){

		}

	private:
		Datagram datagram;
		time_t sendTime;
	};

	inline bool sequenceIDuence_more_recent( unsigned int s1, unsigned int s2, unsigned int max_sequenceIDuence ){
		return	( s1 > s2 ) && ( s1 - s2 <= max_sequenceIDuence / 2 ) || 
				( s2 > s1 ) && ( s2 - s1 >  max_sequenceIDuence / 2 );
	}

	class OrderedDatagamHistory {

	friend class Client;

	private:
		OrderedDatagamHistory(Client* owner) : owner(owner) {

		}

		virtual ~OrderedDatagamHistory(){

		}

	public:

		void Update(UINT32 ack, UINT32 diff_ack_bitfield);

		void PushBack(HistoryEntry he){
			history[he.datagram.sequenceID] = he;
		}

		void Clear(){
			history.clear();
		}

	private:
		std::map<UINT32, HistoryEntry> history;
		UINT32 lastProcessedAck;
		UINT32 lastProcessedAck_bitfield;
		Client* owner;
	};

	//static void serviceRunner(boost::shared_ptr<boost::asio::io_service> io_service){
	static void serviceRunner(boost::asio::io_service& io_service){
		io_service.run();
		assert(0);
	}

	class SocketBase {
		friend class Server;
		friend class Client;

	protected:

		SocketBase(udp::endpoint local_endPoint, bool reuse_address = false) : /*io_service(new boost::asio::io_service),*/ work(new boost::asio::io_service::work(io_service)),worker_thread(nullptr), socket(new udp::socket(io_service)) {

			socket->open(udp::v4());
			try{
				socket->set_option(boost::asio::socket_base::reuse_address(reuse_address));
				socket->bind(local_endPoint);

				boost::asio::socket_base::non_blocking_io command(true);
				socket->io_control(command);
			}
			catch(std::exception e){
				Util::dout << e.what() << std::endl;
			}

			
		}

		SocketBase() : /*io_service(new boost::asio::io_service),*/ work(new boost::asio::io_service::work(io_service)), worker_thread(nullptr), socket(new udp::socket(io_service)) {

			socket->open(udp::v4());

			boost::asio::socket_base::non_blocking_io command(true);
			socket->io_control(command);
		}

		virtual ~SocketBase(){
			work.reset();
		}

		

		void Initialize(){

			worker_thread = std::auto_ptr<boost::thread>(new boost::thread(boost::bind(serviceRunner, boost::ref(io_service))));
		}

		Datagram parseDatagram(size_t bytes_transferred){
			boost::asio::streambuf b;
			std::iostream s(&b);
			//s << dataBuff.c_array();
			s.write(dataBuff.c_array(), bytes_transferred);
			boost::archive::text_iarchive archive(s);
			
			Datagram data;

			archive >> data;

			return data;
		}

		

	protected:
		//boost::shared_ptr<boost::asio::io_service> io_service;
		static boost::asio::io_service io_service;
		boost::shared_ptr<udp::socket> socket;
		std::auto_ptr<boost::thread> worker_thread;

		std::auto_ptr<boost::asio::io_service::work> work;
		boost::array<char, MAXBUFFSIZE> dataBuff;
	};

	

	class Client : public SocketBase, public boost::enable_shared_from_this<Client> {
		friend class Server;
		friend class OrderedDatagamHistory;
	
	private:

		Client(udp::endpoint local_endPoint, bool resuse_address = false) : connected(false), SocketBase(local_endPoint, resuse_address), currentPacketsequenceIDuence(0), senderID(MAXUINT32), lastAck(0), ack_bitfield(0), history(this) {
			
		}

		void beginListening(){
			std::cout << "Begin listening" << std::endl;
			Util::dout << "Begin listening" << std::endl;
			boost::shared_ptr<udp::endpoint> endpoint(new udp::endpoint());

			socket->async_receive(boost::asio::buffer(dataBuff, MAXBUFFSIZE), boost::bind(&Client::recieved_handler, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, endpoint));
		}

		static boost::shared_ptr<Client> CreateForServer(udp::endpoint local_endPoint, udp::endpoint remote_endPoint){
			boost::shared_ptr<Client> client(new Client(local_endPoint, true));

			//client->Connect(remote_endPoint);

			client->remote_endPoint = remote_endPoint;

			client->Initialize();

			//std::cout << " Connecting...." << std::endl;

			return client;
		}

		void updateAckInfo(Datagram& dg){

			//UINT32 old_bitfield = ack_bitfield;

			int offset = dg.sequenceID - lastAck;

			int bitfieldSize = sizeof(ack_bitfield) * 8;
			if(offset > 0){
				//push in previous ack
				ack_bitfield <<= 1;
				ack_bitfield |= 1;

				if(--offset > 1){
					//offset
					ack_bitfield <<= (offset - 1);
				}

				//old_bitfield <<= (offset-1);

				lastAck = dg.sequenceID;
			}
			else if(offset <= bitfieldSize) {
				ack_bitfield |= 1<<(-offset - 2); //-1 for lastAck and -1 becuase 1 is already in first bit position
			}
			// else too bad

			//TODO:
			history.Update(dg.ack, dg.ack_bitfield);
		}	

		Datagram& addAckInfo(Datagram& dg){
			dg.ack = lastAck;
			//memcpy(&dg.ack_bitfield, &ack_bitfield, sizeof(ack_bitfield));
			dg.ack_bitfield = ack_bitfield;

			return dg;
		}

		void SendDatagram(Datagram dg){

			dg.sequenceID = currentPacketsequenceIDuence++;

			addAckInfo(dg);
			//dg.senderid = senderID;

			boost::asio::streambuf b;
			std::ostream os(&b);
			boost::archive::text_oarchive archive(os);
					
			archive << dg;			

			socket->async_send_to(b.data(), remote_endPoint, boost::bind(&Client::sent_handler, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, dg));
		}

	public:

		template<class T>
		void Send(T& data, UINT32 updateType, DatagramImportance importance = DatagramImportance::UNRELIABLE){
			boost::shared_ptr<T> temp = boost::make_shared<T>(data);
			Send(boost::shared_dynamic_cast<SerializableData>(temp), updateType, importance);
		}

		void Send(const boost::shared_ptr<SerializableData> data, UINT32 updateType, DatagramImportance importance = DatagramImportance::UNRELIABLE){
			Datagram dg;
			dg.updateType = updateType;
			dg.importance = importance;

			//addAckInfo(dg);
			dg.senderid = senderID;

			dg.data = data;

			SendDatagram(dg);
		}

		
		void Update(double deltaTime){

		}
		
		static boost::shared_ptr<Client> Create(udp::endpoint local_endPoint, udp::endpoint remote_endPoint){
			boost::shared_ptr<Client> client(new Client(local_endPoint));

			//client->Connect(remote_endPoint);

			client->remote_endPoint = remote_endPoint;

			client->beginListening();

			client->Initialize();

			GPENet::Datagram dg;

			dg.updateType = UPDATE_TYPE::REQUEST_CONNECT;
			dg.importance = DatagramImportance::RELIABLE_UNORDERED;

			client->SendDatagram(dg);

			return client;
		}

		virtual ~Client(){
		}

		virtual void sent_handler(const boost::system::error_code& error, std::size_t bytes_transferred, Datagram dg){
			//std::cout << "Sent_handler" << std::endl;
			//Util::dout << "Sent_handler" << std::endl;
			if (!error || error == boost::asio::error::message_size){
				if(dg.importance > DatagramImportance::UNRELIABLE){
					history.PushBack(HistoryEntry(dg, clock()));
				}
			}
			else {
				std::cout << error.value() << ": " << error.message() << " " << bytes_transferred << std::endl;
				Util::dout << error.value() << ": " << error.message() << " " << bytes_transferred << std::endl;
			}
			//SocketBase::sent_handler(error, bytes_transferred, data);
		}		

		virtual void recieved_handler(const boost::system::error_code& error, std::size_t bytes_transferred, boost::shared_ptr<udp::endpoint> endpoint){
			if (!error || error == boost::asio::error::message_size){

				//std::stringstream ss;
				//ss.write(dataBuff.c_array(), bytes_transferred);
				//ss << std::endl;
				//OutputDebugStringA(ss.str().c_str());

				//if(*endpoint == remote_endPoint){
					Datagram dg = parseDatagram(bytes_transferred);

					updateAckInfo(dg);

					switch(dg.updateType){
					case UPDATE_TYPE::PING:
						dg.senderid = senderID;
						Send(dg, UPDATE_TYPE::PONG);
						break;
					case UPDATE_TYPE::REQUEST_CONNECT:
						//do nothing, drop packet;
						break;
					case UPDATE_TYPE::CONNECT:
						{
						//senderID = *dg.getData<int>();
						boost::shared_ptr<SerializableUINT32> sdf = dg.getData<SerializableUINT32>();
						senderID = sdf->val;

						{
						Datagram newDatagram;
						newDatagram.updateType = UPDATE_TYPE::CONNECT;
						newDatagram.senderid = senderID;
						newDatagram.importance = DatagramImportance::RELIABLE_UNORDERED;
						SendDatagram(newDatagram);
						}

						connected = true;

						Util::dout << "Connection established with server with ip: " << endpoint->address().to_string() << ":" << endpoint->port() << ", my senderID is: " << senderID << std::endl;
						}
						break;
					case UPDATE_TYPE::NONE:
						//do nothing
						break;
					default:
						if(callbacks.find(dg.updateType) != callbacks.end() ){
							Util::dout << "Trying to call func" << std::endl;
							callbacks[dg.updateType](dg);
						}
						else {
							Util::dout << "Update type not found... " << dg.updateType << std::endl;
						}
						break;
					}
				//}
			}
			else {
				std::cout << error.value() << ": " << error.message() << " " << bytes_transferred << std::endl;
				Util::dout << error.value() << ": " << error.message() << " " << bytes_transferred << std::endl;
				//socket->async_receive(boost::asio::buffer(dataBuff, MAXBUFFSIZE), boost::bind(&Client::recieved_handler, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, endpoint));
			}

			//SocketBase::recieved_handler(error, bytes_transferred, endpoint);

			socket->async_receive(boost::asio::buffer(dataBuff, MAXBUFFSIZE), boost::bind(&Client::recieved_handler, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, endpoint));
		}

		void AddCallback(UINT32 type, boost::function<void (Datagram)> callback){
			callbacks[type] = callback;
		}

		void RemoveCallback(UINT32 type){
			callbacks.erase(type);
		}

		/*void RemoveCallback(boost::function<void (Datagram)> callback){
			callbacks.erase(callbacks.find(callback));
		}*/

		bool isConnected(){
			return connected;
		}

		void ClearHistory(){
			history.Clear();
		}

	private:
		bool connected;

		UINT32 senderID;
		UINT32 lastAck;
		UINT32 ack_bitfield;

		UINT32 currentPacketsequenceIDuence;

		udp::endpoint remote_endPoint;

		OrderedDatagamHistory history;
		std::deque<Datagram> sendQueue;

		std::map<UINT32, boost::function<void (Datagram)>> callbacks;
	};

	class Server : public SocketBase, public boost::enable_shared_from_this<Server> {

	private:

		Server() : SocketBase(udp::endpoint(boost::asio::ip::address_v4::any(), 1774)), clientIDCounter(0), pinger_timer( new boost::asio::deadline_timer(io_service, boost::posix_time::milliseconds(200))){
			
		}

		void beginListening(){
			boost::shared_ptr<udp::endpoint> endpoint(new udp::endpoint());

			socket->async_receive_from(boost::asio::buffer(dataBuff, MAXBUFFSIZE), *endpoint, boost::bind(&Server::recieved_handler, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, endpoint));
		}

		void Timer_handler(const boost::system::error_code& error, boost::shared_ptr<boost::asio::deadline_timer> timer){
			if (!error || error == boost::asio::error::message_size){
				PingAll();
			}
			else {
				std::cout << error.value() << ": " << error.message() << std::endl;
			}

			if(!error || error != boost::asio::error::operation_aborted){
				timer->expires_from_now(boost::posix_time::milliseconds(200));
				timer->async_wait(boost::bind(&Server::Timer_handler, shared_from_this(), boost::asio::placeholders::error, timer));
			}
		}

	public:

		static boost::shared_ptr<Server> Create(){
			boost::shared_ptr<Server> server(new Server());

			server->Initialize();

			server->beginListening();

			server->pinger_timer->async_wait(boost::bind(&Server::Timer_handler, server->shared_from_this(), boost::asio::placeholders::error, server->pinger_timer));

			return server;
		}

		virtual ~Server(){
			//io_service.stop();
			pinger_timer->cancel();
		}	

		void PingAll(){
			std::map<UINT32, boost::shared_ptr<Client>>::iterator itr = clients.begin();
			Datagram dg;
			dg.updateType = UPDATE_TYPE::PING;
			for(;itr != clients.end(); itr++){
				itr->second->SendDatagram(dg);
			}
		}

		virtual void recieved_handler(const boost::system::error_code& error, std::size_t bytes_transferred, boost::shared_ptr<udp::endpoint> endpoint){
			//Util::dout << "Server got packet" << std::endl;
			//std::cout << "Server got packet" << std::endl;
			if (!error || error == boost::asio::error::message_size){

				//std::cout.write(dataBuff.c_array(), bytes_transferred);
				//std::cout << std::endl;


				Datagram dg = parseDatagram(bytes_transferred);

				if(clients.find(dg.senderid) != clients.end()){
					clients[dg.senderid]->updateAckInfo(dg);
				}

				switch(dg.updateType){
				case UPDATE_TYPE::REQUEST_CONNECT:
					{
					int cid = clientIDCounter++;
					boost::shared_ptr<Client> c = Client::CreateForServer(socket->local_endpoint(), *endpoint);
					
					tempClients[cid] = c;
					c->senderID = cid;

					SerializableUINT32 id;
					id.val = cid;
					c->Send<SerializableUINT32>(id, UPDATE_TYPE::CONNECT, DatagramImportance::RELIABLE_UNORDERED);

					std::cout << "Recieved connection request with ip: " << endpoint->address().to_string() << ":" << endpoint->port() << std::endl;
					}
					break;
				case UPDATE_TYPE::CONNECT:
					if(tempClients.find(dg.senderid) != tempClients.end()){
						clients[dg.senderid] = tempClients[dg.senderid];
						tempClients.erase(dg.senderid);

						std::cout << "Client connected with ip: " << endpoint->address().to_string() << ":" << endpoint->port() << std::endl;
					}
					break;
				case UPDATE_TYPE::DISCONNECT:
					
					std::map<UINT32, boost::shared_ptr<Client>>::iterator itr = clients.begin(), toRemove;
					for(;itr != clients.end(); itr++){
						if(itr->first == dg.senderid){
							toRemove = itr;
							continue;
						}

						itr->second->SendDatagram(dg);
					}
					std::cout << "Client with ID " << toRemove->first << " disconnected..." << std::endl;
					clients.erase(toRemove);
					break;
				case UPDATE_TYPE::NONE:
					//do nothing
					break;
				default:
					std::map<UINT32, boost::shared_ptr<Client>>::iterator itr = clients.begin();
					for(;itr != clients.end(); itr++){
						if(itr->first == dg.senderid)
							continue;

						itr->second->SendDatagram(dg);
					}
					break;
				}
			}
			else {
				std::cout << error.value() << ": " << error.message() << " " << bytes_transferred << std::endl;
				//socket->async_receive_from(boost::asio::buffer(dataBuff, MAXBUFFSIZE), *endpoint, boost::bind(&Server::recieved_handler, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, endpoint));
			}

			//SocketBase::recieved_handler(error, bytes_transferred, endpoint);

			socket->async_receive_from(boost::asio::buffer(dataBuff, MAXBUFFSIZE), *endpoint, boost::bind(&Server::recieved_handler, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, endpoint));
		}

	private:
		UINT32 clientIDCounter;
		std::map<UINT32, boost::shared_ptr<Client>> tempClients;
		std::map<UINT32, boost::shared_ptr<Client>> clients;

		boost::shared_ptr<boost::asio::deadline_timer> pinger_timer;
	};
}