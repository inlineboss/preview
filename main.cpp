#include <iostream>
#include "SyncServ.h"
#include <thread>
#include "Clients.h"

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
	std::string hellostring[] = {"Hello\r\n", "Hi\r\n", "Nihao\r\n", "Poshel nahuy!\r\n"};
	Clients clients;
	int i = 0;

	async_server::Events event;

	event.accept_connet = [&](boost::asio::ip::tcp::socket* sock) {
		clients.add(sock);
		std::cout << "New connect: " << sock->remote_endpoint().address().to_string() << std::endl;
		sock->write_some(boost::asio::buffer(hellostring[i]));
		clients.each(sock, [&](boost::asio::ip::tcp::socket* sock) {
			sock->write_some(boost::asio::buffer("Client " + sock->remote_endpoint().address().to_string() + " connected!\r\n"));
		});
		i < 3 ? i++ : i = 0;
	};

	event.other_read = [&](std::string& msg, boost::asio::ip::tcp::socket* sock) {
		clients.each(sock, [&](boost::asio::ip::tcp::socket* sock) {
			sock->write_some(boost::asio::buffer("client " + sock->remote_endpoint().address().to_string() + ">>:" + msg + "\r\n"));
		});
	};

	event.checkconnect = [&](size_t bytes, boost::asio::ip::tcp::socket* sock) {
		if (!bytes) {
			std::cout << "Client " << sock->remote_endpoint().address().to_string() << " disconnected\r\n" << std::endl;
			clients.remove(sock);

			clients.each([](boost::asio::ip::tcp::socket* sock) {
				sock->write_some(boost::asio::buffer("Client " + sock->remote_endpoint().address().to_string() + " disconnect!\r\n"));
			});
		}
		return bytes;
	};

	while (true)
	{
		async_server::handle_connections(event);
	}
}
