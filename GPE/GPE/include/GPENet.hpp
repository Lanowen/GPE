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

#include "SerializeableData.hpp"

#include <boost/serialization/split_free.hpp>

//#include <boost\serialization\void_cast.hpp>

//#include <BaseTsd.h>

#include "Util.hpp"

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
		inline boost::shared_ptr<T> getData() {
			//return boost::shared_polymorphic_downcast<T, SerializableData>(data);
			return boost::dynamic_pointer_cast<T, SerializableData>(data);
		}

	public:
		Datagram();

		virtual ~Datagram();

	private:
		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive & ar, const unsigned int version);
	};

	using namespace boost::asio::ip;

	class HistoryEntry{
		friend class OrderedDatagamHistory;
		//friend std::map<UINT32, HistoryEntry>;

	public:
	//private:
		HistoryEntry();
		//HistoryEntry(const HistoryEntry &he);
		//HistoryEntry& operator=(const HistoryEntry &he);	

		HistoryEntry(Datagram datagram, time_t sendTime);

		virtual ~HistoryEntry();

	private:
		Datagram datagram;
		time_t sendTime;
	};

	class OrderedDatagamHistory {

	friend class Client;

	private:
		OrderedDatagamHistory(Client* owner);

		virtual ~OrderedDatagamHistory();

	public:

		void Update(UINT32 ack, UINT32 diff_ack_bitfield);

		void PushBackDatagram(Datagram dg);

		void Clear();

	private:
		std::map<UINT32, HistoryEntry> history;
		UINT32 lastProcessedAck;
		UINT32 lastProcessedAck_bitfield;
		Client* owner;
	};

	class SocketBase /*: public boost::enable_shared_from_this<SocketBase>*/ {
		friend class Server;
		friend class Client;
		friend class boost::thread;

	private:
		struct QueuedCallback {
			boost::function<void (Datagram)> callback;
			Datagram param;
		};

		void serviceRunner();

	protected:

		SocketBase(udp::endpoint local_endPoint, bool reuse_address = false);

		SocketBase();

		virtual ~SocketBase();

		void Initialize();

		void tryCallCallbacks(Datagram& dg);
		
		Datagram parseDatagram(size_t bytes_transferred);

	public:

		template<class T>
		inline void Send(T& data, UINT32 updateType, DatagramImportance importance = DatagramImportance::UNRELIABLE) {
			boost::shared_ptr<T> temp = boost::make_shared<T>(data);
			Send(boost::dynamic_pointer_cast<SerializableData>(temp), updateType, importance);
		}

		virtual void Send(const boost::shared_ptr<SerializableData> data, UINT32 updateType, DatagramImportance importance = DatagramImportance::UNRELIABLE) = 0;

		virtual void Update(double deltaTime) = 0;

		void AddQueuedCallback(UINT32 type, boost::function<void(Datagram)> callback);

		void RemoveQueuedCallback(UINT32 type);

		void AddCallback(UINT32 type, boost::function<void(Datagram)> callback);

		void RemoveCallback(UINT32 type);

		void fetchCallbacks();

	public:
		boost::shared_ptr<void*> userData;
		UINT32 hackedInt;


	protected:
		//boost::shared_ptr<boost::asio::io_service> io_service;
		static boost::asio::io_service io_service;
		boost::shared_ptr<udp::socket> socket;
		//std::auto_ptr<boost::thread> worker_thread;
		boost::thread worker_thread;

		std::auto_ptr<boost::asio::io_service::work> work;
		boost::array<char, MAXBUFFSIZE> dataBuff;
		
		std::map<UINT32, boost::function<void (Datagram)>> callbacks;
		std::map<UINT32, boost::function<void (Datagram)>> queuedCallbackLookup;
		
		std::list<QueuedCallback> queuedCallbacks;
	};

	

	class Client : public SocketBase, public boost::enable_shared_from_this<Client> {
		friend class Server;
		friend class OrderedDatagamHistory;
	
	private:

		Client(udp::endpoint local_endPoint, bool resuse_address = false);

		void beginListening();

		static boost::shared_ptr<Client> CreateForServer(udp::endpoint local_endPoint, udp::endpoint remote_endPoint);

		void updateAckInfo(Datagram& dg);

		Datagram& addAckInfo(Datagram& dg);

		void SendDatagram(Datagram dg);

	public:

		template<class T>
		void Send(T& data, UINT32 updateType, DatagramImportance importance = DatagramImportance::UNRELIABLE);

		virtual void Send(const boost::shared_ptr<SerializableData> data, UINT32 updateType, DatagramImportance importance = DatagramImportance::UNRELIABLE);

		
		virtual void Update(double deltaTime);
		
		static boost::shared_ptr<Client> Create(udp::endpoint local_endPoint, udp::endpoint remote_endPoint);

		virtual ~Client();

	private:

		virtual void sent_handler(const boost::system::error_code& error, std::size_t bytes_transferred, Datagram dg);

		virtual void recieved_handler(const boost::system::error_code& error, std::size_t bytes_transferred, boost::shared_ptr<udp::endpoint> endpoint);
		

		/*void RemoveCallback(boost::function<void (Datagram)> callback);*/

	public:

			bool isConnected();

			void ClearHistory();

	private:
		bool connected;

		UINT32 senderID;
		UINT32 lastAck;
		UINT32 ack_bitfield;

		double timeSinceLastAck;

		UINT32 currentPacketsequenceID;

		udp::endpoint remote_endPoint;

		OrderedDatagamHistory history;
		std::deque<Datagram> sendQueue;

	};

	class Server : public SocketBase, public boost::enable_shared_from_this<Server>  {

	private:

		Server();

		void beginListening();

		void Timer_handler(const boost::system::error_code& error, boost::shared_ptr<boost::asio::deadline_timer> timer);

	public:

		virtual void Update(double deltaTime);

		static boost::shared_ptr<Server> Create();

		virtual ~Server();

		void PingAll();

		template<class T>
		void Send(T& data, UINT32 updateType, DatagramImportance importance = DatagramImportance::UNRELIABLE);

		virtual void Send(const boost::shared_ptr<SerializableData> data, UINT32 updateType, DatagramImportance importance = DatagramImportance::UNRELIABLE);

		template<class T>
		inline void SendTo(UINT32 clientID, T& data, UINT32 updateType, DatagramImportance importance = DatagramImportance::UNRELIABLE) {
			boost::shared_ptr<T> temp = boost::make_shared<T>(data);
			SendTo(clientID, boost::dynamic_pointer_cast<SerializableData>(temp), updateType, importance);
		}

		virtual void SendTo(UINT32 clientID, const boost::shared_ptr<SerializableData> data, UINT32 updateType, DatagramImportance importance = DatagramImportance::UNRELIABLE);

		boost::shared_ptr<Client> getClient(UINT32 index);

		template<class T>
		inline void SendToExcluding(UINT32 clientID, T& data, UINT32 updateType, DatagramImportance importance = DatagramImportance::UNRELIABLE){
			boost::shared_ptr<T> temp = boost::make_shared<T>(data);
			SendToExcluding(clientID, boost::dynamic_pointer_cast<SerializableData>(temp), updateType, importance);
		}

		virtual void SendToExcluding(UINT32 clientID, const boost::shared_ptr<SerializableData> data, UINT32 updateType, DatagramImportance importance = DatagramImportance::UNRELIABLE);

	private:

		virtual void recieved_handler(const boost::system::error_code& error, std::size_t bytes_transferred, boost::shared_ptr<udp::endpoint> endpoint);

	private:
		UINT32 clientIDCounter;
		std::map<UINT32, boost::shared_ptr<Client>> tempClients;
		std::map<UINT32, boost::shared_ptr<Client>> clients;

		boost::shared_ptr<boost::asio::deadline_timer> pinger_timer;
		boost::recursive_mutex clientMtx;
	};
}