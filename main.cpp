#include <iostream>
#include "SyncServ.h"
#include <thread>
#include "Clients.h"
#include "ClientsBroadcast.h"
#include "ClientsCache.h"
#include "ClientsLogger.h"
#include "ClientsBanner.h"

/*
void other_read(std::string& msg) {
	std::cout << "client "<< ipv4 << ">>:" << msg << std::endl;
	std::cin >> msg;
	msg += "\r\n";
	msg = "server >>: " + msg;
}
*/
/*
void accept_connet (boost::asio::ip::tcp::socket& sock){
	ipv4 = sock.remote_endpoint().address().to_string();
  std::cout << "New connect: " << ipv4 << std::endl;
  sock.write_some(boost::asio::buffer("Hello\r\n"));
}
*/
/*
bool checkconnect(int bytes) {
	if (!bytes) {
		std::cout << "Connection closed" << std::endl;
		std::cout << "Client " << ipv4 << " disconnected";
	}
	return bytes;
	
}
*/

int main(int argc, char* argv[])
{
	std::vector<std::string> hellostring = {"Hello\r\n", "Hi\r\n", "Nihao\r\n", "Poshel nahuy!\r\n"};
	
	IClients *clients = 
		new ClientsBanner(hellostring,
			new ClientsLogger (
				new ClientsBroadcast(
					new ClientsCache()
				)
			)
		);

	int i = 0;

	async_server::Events event;


	event.accept_connet = [&](boost::asio::ip::tcp::socket* sock) {
		clients->add(sock);
	};


	event.other_read = [&](std::string& msg, boost::asio::ip::tcp::socket* sock) {
		clients->update(sock, msg);
	};


	event.checkconnect = [&](size_t bytes, boost::asio::ip::tcp::socket* sock) {
		clients->remove(sock);
		
		return bytes;
	};

	while (true)
	{
		async_server::handle_connections(event);
	}
}
