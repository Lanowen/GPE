#include <GPENet.hpp>
#include <iostream>

#include <SerializationClassExports.hpp>

using namespace boost::asio::ip;

int main(){
	std::cout << "Creating Server..." << std::endl;
	boost::shared_ptr<GPENet::Server> server = GPENet::Server::Create();
	std::cout << "Created Server..." << std::endl;

	//boost::shared_ptr<GPENet::Client> client = GPENet::Client::Create(udp::endpoint(boost::asio::ip::address_v4::any(), 2211), udp::endpoint(boost::asio::ip::address_v4::from_string("127.0.0.1"), 1774));
	//client->Send<int>(1, GPENet::UPDATE_TYPE::REQUEST_CONNECT);

	//Sleep(2000);

	//server->blah();

	/*boost::shared_ptr<GPENet::Client> client1 = GPENet::Client::Create(udp::endpoint(boost::asio::ip::address_v4::any(), 1777), udp::endpoint(boost::asio::ip::address_v4::from_string("127.0.0.1"), 1778));
	boost::shared_ptr<GPENet::Client> client2 = GPENet::Client::Create(udp::endpoint(boost::asio::ip::address_v4::any(), 1778), udp::endpoint(boost::asio::ip::address_v4::from_string("127.0.0.1"), 1777));
	boost::shared_ptr<GPENet::Client> client3 = GPENet::Client::Create(udp::endpoint(boost::asio::ip::address_v4::any(), 1779), udp::endpoint(boost::asio::ip::address_v4::from_string("127.0.0.1"), 1777));

	client1->Send<int>(1, GPENet::UPDATE_TYPE::PING);
	client2->Send<int>(1, GPENet::UPDATE_TYPE::PING);
	client3->Send<int>(1, GPENet::UPDATE_TYPE::PING);*/

	//boost::shared_ptr<GPENet::Client> client = GPENet::Client::Create(boost::asio::ip::udp::endpoint(boost::asio::ip::address_v4::any(), 0), boost::asio::ip::udp::endpoint(boost::asio::ip::address_v4::from_string("127.0.0.1"), 1774));

	/*GPENet::Datagram dg;

	dg.pid = GPENet::UPDATE_TYPE::REQUEST_CONNECT;

	client->Send(dg);*/

	//server.reset();

	//boost::shared_ptr<GPENet::Client> client = GPENet::Client::Create(udp::endpoint(boost::asio::ip::address_v4::any(), 1779), udp::endpoint(boost::asio::ip::address_v4::from_string("127.0.0.1"), 1776));
	//client->Send<int>(1, GPENet::UPDATE_TYPE::CONNECT);


	//boost::shared_ptr<GPENet::Client> client = GPENet::Client::Create(udp::endpoint(boost::asio::ip::address_v4::any(), 1774), udp::endpoint(boost::asio::ip::address_v4::from_string("127.0.0.1"), 1776));

	
	

	while(true){
		Sleep(100);
	}

	return 0;
}

//#include <boost/asio.hpp>
//#include <boost/array.hpp>
//#include <iostream>
//
//using namespace boost::asio::ip;
//
//boost::asio::io_service io_service;
//
//size_t maxSize = 65507;
//boost::array<char, 65507> dataBuff;
//
//
//
//udp::socket* socketb;
//
//udp::endpoint sender_endpoint;
//
// void handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred){
//	 std::cout << sender_endpoint.address().to_string() << std::endl;
//	  if (!error || error == boost::asio::error::message_size){
//		  std::cout << std::string(dataBuff.c_array()).substr(0,bytes_transferred) << std::endl;
//	  }
//	  else {
//		  std::cout << error.value() << ": " << error.message() << " " << bytes_transferred << std::endl;
//		  socketb->async_receive_from(boost::asio::buffer(dataBuff, maxSize), sender_endpoint, handle_receive);
//	  }
//
//	  socketb->async_receive_from(boost::asio::buffer(dataBuff, maxSize), sender_endpoint, handle_receive);
// }
//
//int main(){
//
//	std::cout << "Creating socket..." << std::endl;
//	socketb = new udp::socket(io_service, udp::endpoint(udp::v4(), 1774));
//
//	std::cout << "Waiting for incoming data..." << std::endl << std::endl;
//	socketb->async_receive_from(boost::asio::buffer(dataBuff, maxSize), sender_endpoint, handle_receive);
//	
//
//	//std::auto_ptr<boost::asio::io_service::work> work(new boost::asio::io_service::work(io_service));
//	io_service.run();
//	
//
//	std::cout << "Done" << std:: endl;
//
//	while(true) {
//		Sleep(100);
//	}
//
//	return 0;
//}