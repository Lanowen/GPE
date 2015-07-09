#include "GPENet.hpp"

namespace GPENet {

	boost::asio::io_service SocketBase::io_service;
	boost::asio::io_service::work SocketBase::work(SocketBase::io_service);
	boost::thread SocketBase::worker_thread(boost::bind(&SocketBase::serviceRunner));

	void OrderedDatagamHistory::Update(UINT32 ack, UINT32 ack_bitfield){
		UINT32 diff_ack_bitfield = lastProcessedAck_bitfield;

		int offset = ack - lastProcessedAck;

		int bitfieldSize = sizeof(ack_bitfield) * 8;
		if(offset > 0){
			//push in previous ack
			ack_bitfield <<= 1;
			ack_bitfield |= 1;

			if(--offset > 1){
				//offset
				ack_bitfield <<= (offset - 1);
			}

			diff_ack_bitfield <<= (offset-1);

			lastProcessedAck = ack;
		}
		else if(offset <= bitfieldSize) {
			ack_bitfield |= 1<<(-offset - 2); //-1 for lastAck and -1 becuase 1 is already in first bit position
		}
		// else too bad

		diff_ack_bitfield ^= ack_bitfield;

		if(history.size() > 0){
			int x = history.size();

			//std::cout << "Begin history update " << ack << " " << diff_ack_bitfield << " " << history.size() << std::endl;
			//Util::dout <<  "Begin history update " << ack << " " << diff_ack_bitfield << " " << history.size() << std::endl;

			std::map<UINT32, HistoryEntry>::iterator itr = history.begin();
			std::map<UINT32, HistoryEntry>::iterator next;

			if(history.begin() == history.end())
				next = history.end();
			else
				next = history.begin()++;

			for(; itr != history.end();){
				if(itr->first > ack + 32){ //its gone beyond the ack, resend
					int dsf = itr->first;
					owner->SendDatagram(itr->second.datagram);
					history.erase(itr);
					//std::cout << "1: " << dsf << " got removed from the history! " << history.size() << std::endl;
					//Util::dout << "1: " << dsf << " got removed from the history! " << history.size() << std::endl;

					if(next == history.end())
						break;

					itr = next++;
					continue;
				}

				break;
			}

			//std::cout << "1: end for " << history.size() << std::endl;
			//Util::dout << "1: end for " << history.size() << std::endl;
				
			if(history.find(ack) != history.end()){
				history.erase(ack);
				//std::cout << "2: " << ack << " got removed from the history! " << history.size() << std::endl;
				//Util::dout << "2: " << ack << " got removed from the history! " << history.size() << std::endl;
			}

			
			for(int i = ack-1; diff_ack_bitfield > 0; diff_ack_bitfield >>= 1, i--){
				if((diff_ack_bitfield & 1) != 0){
					if(history.find(i) != history.end()){
						history.erase(i);
						//std::cout << "3: " << i << " got removed from the history! " << history.size() << std::endl;
						//Util::dout << "3: " << i << " got removed from the history! " << history.size() << std::endl;
					}
					
				}
			}
			//std::cout << "3: end for " << history.size() << std::endl;
			//Util::dout << "3: end for " << history.size() << std::endl;
		}
	}


	Datagram::Datagram() : updateType(UPDATE_TYPE::NONE), senderid(0), importance(DatagramImportance::UNRELIABLE), sequenceID(0), ack(0), ack_bitfield(), data(new SerializableData()) /* TODO: Make this a static obj so its not allocated all the time */ {

	}

	Datagram::~Datagram() {

	}

	template<class Archive>
	void Datagram::serialize(Archive & ar, const unsigned int version){
		ar & updateType;
		ar & importance;
		ar & senderid;
		ar & sequenceID;
		ar & ack;
		ar & ack_bitfield;
		ar & data;
	}

	HistoryEntry::HistoryEntry() {}
	//HistoryEntry::HistoryEntry(const HistoryEntry &he) { memcpy(this, &he, sizeof(HistoryEntry)); }
	//HistoryEntry& HistoryEntry::operator=(const HistoryEntry &he) { memcpy(this, &he, sizeof(HistoryEntry)); return *this; }

	HistoryEntry::HistoryEntry(Datagram datagram, time_t sendTime) : datagram(datagram), sendTime(sendTime){
	}

	HistoryEntry::~HistoryEntry(){

	}

	inline bool sequenceIDuence_more_recent(unsigned int s1, unsigned int s2, unsigned int max_sequenceIDuence){
		return	(s1 > s2) && (s1 - s2 <= max_sequenceIDuence / 2) ||
			(s2 > s1) && (s2 - s1 >  max_sequenceIDuence / 2);
	}

	OrderedDatagamHistory::OrderedDatagamHistory(Client* owner) : owner(owner) {

	}

	OrderedDatagamHistory::~OrderedDatagamHistory(){

	}

	void OrderedDatagamHistory::PushBackDatagram(Datagram dg){
		HistoryEntry he(dg, clock());
		history[he.datagram.sequenceID] = he;
	}

	void OrderedDatagamHistory::Clear(){
		history.clear();
	}

	void SocketBase::serviceRunner() {
		try {
			SocketBase::io_service.run();
		}
		catch (boost::system::system_error &e) {
			Util::dout << boost::diagnostic_information(e) << std::endl;
		}
		catch (boost::exception &e) {
			Util::dout << boost::diagnostic_information(e);
		}
		catch (const std::exception& e) {
			Util::dout  << e.what() << std::endl;
		}
		
		assert(0);
	}

	SocketBase::SocketBase(udp::endpoint local_endPoint, bool reuse_address) : /*work(new boost::asio::io_service::work(io_service))/*, worker_thread(boost::thread(boost::bind(serviceRunner, boost::ref(io_service)))),*/ socket(new udp::socket(io_service)) {

			socket->open(udp::v4());
			try{
				socket->set_option(boost::asio::socket_base::reuse_address(reuse_address));
				socket->bind(local_endPoint);

				boost::asio::socket_base::non_blocking_io command(true);
				socket->io_control(command);
			}
			catch (boost::system::system_error &e) {
				Util::dout << "Socket Base::SocketBase " << e.what() << std::endl;
				Util::dout << "Socket Base::SocketBase " << boost::diagnostic_information(e) << std::endl;
			}
			catch (std::exception e){
				Util::dout << e.what() << std::endl;
			}

			//worker_thread = boost::thread(boost::bind(serviceRunner, boost::ref(io_service)));
			//worker_thread = boost::thread(boost::bind(&SocketBase::serviceRunner, this));
	}

	SocketBase::SocketBase() : /*io_service(new boost::asio::io_service),*/ /*work(new boost::asio::io_service::work(io_service))/*, worker_thread(boost::thread(boost::bind(serviceRunner, boost::ref(io_service)))), */ socket(new udp::socket(io_service)) {

			socket->open(udp::v4());

			boost::asio::socket_base::non_blocking_io command(true);
			socket->io_control(command);
	}

	SocketBase::~SocketBase(){
			//work.reset();
	}

	void SocketBase::Initialize(){
		//worker_thread = boost::thread(boost::bind(&SocketBase::serviceRunner, this));
	}

	void SocketBase::tryCallCallbacks(Datagram& dg){
		if (callbacks.find(dg.updateType) != callbacks.end()){
			//Util::dout << "Trying to call func" << std::endl;
			callbacks[dg.updateType](dg);
		}

		if (queuedCallbackLookup.find(dg.updateType) != queuedCallbackLookup.end()){
			//Util::dout << "Queueing func" << std::endl;
			//queuedCallbacks[dg.updateType](dg);
			QueuedCallback qcb;
			qcb.callback = queuedCallbackLookup[dg.updateType];
			qcb.param = dg;
			queuedCallbacks.push_back(qcb);
		}
	}


	Datagram SocketBase::parseDatagram(size_t bytes_transferred){
		boost::asio::streambuf b;
		std::iostream s(&b);
		//s << dataBuff.c_array();
		s.write(dataBuff.c_array(), bytes_transferred);
		boost::archive::text_iarchive archive(s);

		Datagram data;

		archive >> data;

		return data;
	}

	void SocketBase::AddQueuedCallback(UINT32 type, boost::function<void(Datagram)> callback){
		queuedCallbackLookup[type] = callback;
	}

	void SocketBase::RemoveQueuedCallback(UINT32 type){
		queuedCallbackLookup.erase(type);
	}

	void SocketBase::AddCallback(UINT32 type, boost::function<void(Datagram)> callback){
		callbacks[type] = callback;
	}

	void SocketBase::RemoveCallback(UINT32 type){
		callbacks.erase(type);
	}

	void SocketBase::fetchCallbacks(){
		std::list<QueuedCallback>::iterator itr = queuedCallbacks.begin();
		for (; itr != queuedCallbacks.end(); itr++){
			itr->callback(itr->param);
		}
		queuedCallbacks.clear();
	}


	Client::Client(udp::endpoint local_endPoint, bool resuse_address) : connected(false), timeSinceLastAck(0), SocketBase(local_endPoint, resuse_address), currentPacketsequenceID(0), senderID(MAXUINT32), lastAck(0), ack_bitfield(0), history(this) {

	}

	void Client::beginListening(){
		std::cout << "Begin listening" << std::endl;
		Util::dout << "Begin listening" << std::endl;
		boost::shared_ptr<udp::endpoint> endpoint(new udp::endpoint());

		socket->async_receive(boost::asio::buffer(dataBuff, MAXBUFFSIZE), boost::bind(&Client::recieved_handler, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, endpoint));
	}

	boost::shared_ptr<Client> Client::CreateForServer(udp::endpoint local_endPoint, udp::endpoint remote_endPoint){
		boost::shared_ptr<Client> client(new Client(local_endPoint, true));

		client->remote_endPoint = remote_endPoint;

		client->Initialize();

		//std::cout << " Connecting...." << std::endl;

		return client;
	}

	void Client::updateAckInfo(Datagram& dg){

		//UINT32 old_bitfield = ack_bitfield;

		int offset = dg.sequenceID - lastAck;

		int bitfieldSize = sizeof(ack_bitfield) * 8;
		if (offset > 0){ //this means lastack is less than sequenceID, this is a newer packet
			//push in previous ack
			ack_bitfield <<= 1;
			ack_bitfield |= 1;

			if (--offset > 1){
				//offset
				ack_bitfield <<= (offset - 1);
			}

			//old_bitfield <<= (offset-1);

			lastAck = dg.sequenceID;
		}
		//else if(offset <= bitfieldSize) { //I don't know why I did this...
		else if (offset < 0 && offset > -bitfieldSize) {
			ack_bitfield |= 1 << (-offset - 2); //-1 for lastAck and -1 becuase 1 is already in first bit position
		}
		// else too bad

		timeSinceLastAck = 0;

		// TODO: I forget
		history.Update(dg.ack, dg.ack_bitfield);
	}

	Datagram& Client::addAckInfo(Datagram& dg){
		dg.ack = lastAck;
		//memcpy(&dg.ack_bitfield, &ack_bitfield, sizeof(ack_bitfield));
		dg.ack_bitfield = ack_bitfield;

		return dg;
	}

	void Client::SendDatagram(Datagram dg){

		dg.sequenceID = currentPacketsequenceID++;

		addAckInfo(dg);
		//dg.senderid = senderID;

		boost::asio::streambuf b;
		std::ostream os(&b);
		boost::archive::text_oarchive archive(os);

		archive << dg;

		socket->async_send_to(b.data(), remote_endPoint, boost::bind(&Client::sent_handler, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, dg));
	}

	template<class T>
	void Client::Send(T& data, UINT32 updateType, DatagramImportance importance){
		boost::shared_ptr<T> temp = boost::make_shared<T>(data);
		Send(boost::dynamic_pointer_cast<SerializableData>(temp), updateType, importance);
	}

	void Client::Send(const boost::shared_ptr<SerializableData> data, UINT32 updateType, DatagramImportance importance){
		Datagram dg;
		dg.updateType = updateType;
		dg.importance = importance;

		//addAckInfo(dg);
		dg.senderid = senderID;

		dg.data = data;

		SendDatagram(dg);
	}


	void Client::Update(double deltaTime){
		timeSinceLastAck += deltaTime;
	}

	boost::shared_ptr<Client> Client::Create(udp::endpoint local_endPoint, udp::endpoint remote_endPoint){
		boost::shared_ptr<Client> client(new Client(local_endPoint));

		client->remote_endPoint = remote_endPoint;

		client->beginListening();

		client->Initialize();

		GPENet::Datagram dg;

		dg.updateType = UPDATE_TYPE::REQUEST_CONNECT;
		dg.importance = DatagramImportance::RELIABLE_UNORDERED;

		client->SendDatagram(dg);

		return client;
	}

	Client::~Client(){
	}


	void Client::sent_handler(const boost::system::error_code& error, std::size_t bytes_transferred, Datagram dg){
		//std::cout << "Sent_handler" << std::endl;
		//Util::dout << "Sent_handler" << std::endl;
		if (!error || error == boost::asio::error::message_size){
			if (dg.importance > DatagramImportance::UNRELIABLE){
				history.PushBackDatagram(dg);
			}
		}
		else {
			std::cout << error.value() << ": " << error.message() << " " << bytes_transferred << std::endl;
			Util::dout << error.value() << ": " << error.message() << " " << bytes_transferred << std::endl;
		}
		//SocketBase::sent_handler(error, bytes_transferred, data);
	}

	void Client::recieved_handler(const boost::system::error_code& error, std::size_t bytes_transferred, boost::shared_ptr<udp::endpoint> endpoint){
		if (!error || error == boost::asio::error::message_size){

			//std::stringstream ss;
			//ss.write(dataBuff.c_array(), bytes_transferred);
			//ss << std::endl;
			//OutputDebugStringA(ss.str().c_str());

			//if(*endpoint == remote_endPoint){
			Datagram dg = parseDatagram(bytes_transferred);

			updateAckInfo(dg);

			switch (dg.updateType){
			case UPDATE_TYPE::PING:
				dg.senderid = senderID;
				dg.updateType = UPDATE_TYPE::PONG;
				SendDatagram(dg);
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

				break;
			}
			tryCallCallbacks(dg);
			//else {
			//	Util::dout << "Update type not found... " << dg.updateType << std::endl;
			//}
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


	/*void Client::RemoveCallback(boost::function<void (Datagram)> callback){
	callbacks.erase(callbacks.find(callback));
	}*/

	bool Client::isConnected(){
		return connected;
	}

	void Client::ClearHistory(){
		history.Clear();
	}


	Server::Server() : SocketBase(udp::endpoint(boost::asio::ip::address_v4::any(), 1774)), clientIDCounter(1), pinger_timer(new boost::asio::deadline_timer(io_service, boost::posix_time::milliseconds(200))){

	}

	void Server::beginListening(){
		boost::shared_ptr<udp::endpoint> endpoint(new udp::endpoint());

		socket->async_receive_from(boost::asio::buffer(dataBuff, MAXBUFFSIZE), *endpoint, boost::bind(&Server::recieved_handler, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, endpoint));
	}

	void Server::Timer_handler(const boost::system::error_code& error, boost::shared_ptr<boost::asio::deadline_timer> timer){
		if (!error || error == boost::asio::error::message_size){
			PingAll();
		}
		else {
			std::cout << error.value() << ": " << error.message() << std::endl;
		}

		if (!error || error != boost::asio::error::operation_aborted){
			timer->expires_from_now(boost::posix_time::milliseconds(200));
			timer->async_wait(boost::bind(&Server::Timer_handler, shared_from_this(), boost::asio::placeholders::error, timer));
		}
	}

	void Server::Update(double deltaTime){
		std::map<UINT32, boost::shared_ptr<Client>>::iterator itr = clients.begin();
		std::list<UINT32> toRemove;
		for (; itr != clients.end(); itr++){
			itr->second->Update(deltaTime);
			if (itr->second->timeSinceLastAck > 5){
				toRemove.push_back(itr->first);
				//Util::dout << "Id : " << itr->first << " has lost connection! " << itr->second->timeSinceLastAck << std::endl;
				SerializableUINT32 data;
				data.val = itr->second->hackedInt;
				SendToExcluding(itr->first, data, UPDATE_TYPE::DISCONNECT, DatagramImportance::RELIABLE_ORDERED);


				// HACK: I forgot what this does
				Datagram dg;
				dg.updateType = UPDATE_TYPE::DISCONNECT;
				dg.data = boost::dynamic_pointer_cast<SerializableData>(boost::make_shared<SerializableUINT32>(data));
				dg.senderid = 0;
				dg.importance = DatagramImportance::RELIABLE_ORDERED;

				tryCallCallbacks(dg);
			}
		}

		if (toRemove.size() > 0){
			clientMtx.lock();
			std::list<UINT32>::iterator removeItr = toRemove.begin();
			for (; removeItr != toRemove.end(); removeItr++){
				itr = clients.find(*removeItr);
				if (itr != clients.end()){
					clients.erase(itr);
				}
			}
			clientMtx.unlock();
		}
	}

	boost::shared_ptr<Server> Server::Create(){
		boost::shared_ptr<Server> server(new Server());

		server->Initialize();

		server->beginListening();

		server->pinger_timer->async_wait(boost::bind(&Server::Timer_handler, server->shared_from_this(), boost::asio::placeholders::error, server->pinger_timer));

		return server;
	}

	Server::~Server(){
		//io_service.stop();
		pinger_timer->cancel();
	}

	void Server::PingAll(){
		std::map<UINT32, boost::shared_ptr<Client>>::iterator itr = clients.begin();
		Datagram dg;
		dg.updateType = UPDATE_TYPE::PING;
		clientMtx.lock();
		for (; itr != clients.end(); itr++){
			itr->second->SendDatagram(dg);
		}
		clientMtx.unlock();
	}

	template<class T>
	void Server::Send(T& data, UINT32 updateType, DatagramImportance importance){
		boost::shared_ptr<T> temp = boost::make_shared<T>(data);
		Send(boost::shared_dynamic_cast<SerializableData>(temp), updateType, importance);
	}

	void Server::Send(const boost::shared_ptr<SerializableData> data, UINT32 updateType, DatagramImportance importance){
		Datagram dg;
		dg.updateType = updateType;
		dg.importance = importance;

		//addAckInfo(dg);
		dg.senderid = 0;

		dg.data = data;

		std::map<UINT32, boost::shared_ptr<Client>>::iterator itr = clients.begin();
		for (; itr != clients.end(); itr++){
			itr->second->SendDatagram(dg);
		}
	}

	void Server::SendTo(UINT32 clientID, const boost::shared_ptr<SerializableData> data, UINT32 updateType, DatagramImportance importance){
		Datagram dg;
		dg.updateType = updateType;
		dg.importance = importance;

		//addAckInfo(dg);
		dg.senderid = 0;

		dg.data = data;

		std::map<UINT32, boost::shared_ptr<Client>>::iterator itr = clients.find(clientID);
		if (itr != clients.end()){
			itr->second->SendDatagram(dg);
		}
	}

	boost::shared_ptr<Client> Server::getClient(UINT32 index){
		return clients[index];
	}

	void Server::SendToExcluding(UINT32 clientID, const boost::shared_ptr<SerializableData> data, UINT32 updateType, DatagramImportance importance){
		Datagram dg;
		dg.updateType = updateType;
		dg.importance = importance;

		//addAckInfo(dg);
		dg.senderid = 0;

		dg.data = data;

		std::map<UINT32, boost::shared_ptr<Client>>::iterator itr = clients.begin();
		for (; itr != clients.end(); itr++){
			if (itr->first == clientID)
				continue;

			itr->second->SendDatagram(dg);
		}
	}

	void Server::recieved_handler(const boost::system::error_code& error, std::size_t bytes_transferred, boost::shared_ptr<udp::endpoint> endpoint){
		//Util::dout << "Server got packet" << std::endl;
		//std::cout << "Server got packet" << std::endl;
		if (!error || error == boost::asio::error::message_size){

			//std::cout.write(dataBuff.c_array(), bytes_transferred);
			//std::cout << std::endl;


			Datagram dg = parseDatagram(bytes_transferred);

			if (clients.find(dg.senderid) != clients.end()){
				clients[dg.senderid]->updateAckInfo(dg);
			}

			switch (dg.updateType){
			case UPDATE_TYPE::REQUEST_CONNECT:
			{
				int cid = clientIDCounter++;
				boost::shared_ptr<Client> c = Client::CreateForServer(socket->local_endpoint(), *endpoint);

				tempClients[cid] = c;
				c->senderID = cid;

				SerializableUINT32 id;
				id.val = cid;
				c->Send<SerializableUINT32>(id, UPDATE_TYPE::CONNECT, DatagramImportance::RELIABLE_UNORDERED);

				Util::dout << "Recieved connection request with ip: " << endpoint->address().to_string() << ":" << endpoint->port() << std::endl;
			}
				break;
			case UPDATE_TYPE::CONNECT:
				if (tempClients.find(dg.senderid) != tempClients.end()){
					clientMtx.lock();
					clients[dg.senderid] = tempClients[dg.senderid];
					tempClients.erase(dg.senderid);
					clientMtx.unlock();

					Util::dout << "Client connected with ip: " << endpoint->address().to_string() << ":" << endpoint->port() << std::endl;
				}
				break;
			case UPDATE_TYPE::DISCONNECT:
			{
				std::map<UINT32, boost::shared_ptr<Client>>::iterator itr = clients.begin(), toRemove;
				for (; itr != clients.end(); itr++){
					if (itr->first == dg.senderid){
						toRemove = itr;
						continue;
					}

					itr->second->SendDatagram(dg);
				}
				Util::dout << "Client with ID " << toRemove->first << " disconnected..." << std::endl;
				clientMtx.lock();
				clients.erase(toRemove);
				clientMtx.unlock();
			}
				break;
			case UPDATE_TYPE::NONE:
				//do nothing
				break;
			default:
			{
				std::map<UINT32, boost::shared_ptr<Client>>::iterator itr = clients.begin();
				for (; itr != clients.end(); itr++){
					if (itr->first == dg.senderid)
						continue;

					itr->second->SendDatagram(dg);
				}
			}
				break;
			}
			tryCallCallbacks(dg);
		}
		else {
			std::cout << error.value() << ": " << error.message() << " " << bytes_transferred << std::endl;
			//socket->async_receive_from(boost::asio::buffer(dataBuff, MAXBUFFSIZE), *endpoint, boost::bind(&Server::recieved_handler, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, endpoint));
		}

		//SocketBase::recieved_handler(error, bytes_transferred, endpoint);

		socket->async_receive_from(boost::asio::buffer(dataBuff, MAXBUFFSIZE), *endpoint, boost::bind(&Server::recieved_handler, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, endpoint));
	}

}