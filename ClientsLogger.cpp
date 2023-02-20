#include "ClientsLogger.h"
#include <iostream>

ClientsLogger::ClientsLogger(IClients* impl) :
	impl_(impl)
{
}

ClientsLogger::~ClientsLogger()
{
}

void ClientsLogger::add(boost::asio::ip::tcp::socket* sock) {
	std::cout << "New connect: " << sock->remote_endpoint().address().to_string() << std::endl;
	impl_->add(sock);
}

void ClientsLogger::remove(boost::asio::ip::tcp::socket* sock) {
	std::cout << "Client " << sock->remote_endpoint().address().to_string() << " disconnected\r\n" << std::endl;
	impl_->remove(sock);
}

void ClientsLogger::each(boost::asio::ip::tcp::socket* sock, std::function <void(boost::asio::ip::tcp::socket*)> other) {
	impl_->each(sock, other);
}


void ClientsLogger::each(std::function <void(boost::asio::ip::tcp::socket*)> other) {
	impl_->each(other);
}

void ClientsLogger::update(boost::asio::ip::tcp::socket* sock, std::string some) {
	std::cout << sock->remote_endpoint().address().to_string() << some;
	impl_->update(sock, some);
}
