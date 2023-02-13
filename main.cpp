#include <iostream>
#include "SyncServ.h"
#include <thread>

void other_read(std::string& msg) {
	std::cout << "client >>: " << msg << std::endl;
	std::cin >> msg;
	msg += "\r\n";
	msg = "server >>: " + msg;
}


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
	std::string hellostring[] = {"Hello", "Hi", "Nihao", "Poshel nahuy!"};
	std::string ipv4;
	int i = 0;
	while (true)
	{
		try {
			sync_server::handle_connections(other_read,
				[&](boost::asio::ip::tcp::socket& sock) {
					ipv4 = sock.remote_endpoint().address().to_string();
					std::cout << "New connect: " << ipv4 << std::endl;
					sock.write_some(boost::asio::buffer(hellostring[i]));
					i < 3 ? i++ : i = 0;
				}, 
				[&](size_t bytes) {
					if (!bytes) {
						std::cout << "Connection closed" << std::endl;
						std::cout << "Client " << ipv4 << " disconnected";
					}
				return bytes;
				}
			);
		}
		catch (const std::exception&) {
			std::cout << "Connection closed" << std::endl;
		}
	}
}
