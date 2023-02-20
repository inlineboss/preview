#include "ClientsBroadcast.h"

ClientsBroadcast::ClientsBroadcast(IClients*impl):
	impl_(impl)
{
}

ClientsBroadcast::~ClientsBroadcast()
{
}

void ClientsBroadcast::add(boost::asio::ip::tcp::socket* sock) {
	impl_->each(sock, [&](boost::asio::ip::tcp::socket* sock) {
		sock->write_some(boost::asio::buffer("Client " + sock->remote_endpoint().address().to_string() + " connected!\r\n"));
	});
	impl_->add(sock);
}

void ClientsBroadcast::remove(boost::asio::ip::tcp::socket* sock) {
	impl_->remove(sock);

	impl_->each([](boost::asio::ip::tcp::socket* sock) {
		sock->write_some(boost::asio::buffer("Client " + sock->remote_endpoint().address().to_string() + " disconnect!\r\n"));
	});

}

void ClientsBroadcast::each(boost::asio::ip::tcp::socket* sock, std::function <void(boost::asio::ip::tcp::socket*)> other) {
	impl_->each(sock, other);
}


void ClientsBroadcast::each(std::function <void(boost::asio::ip::tcp::socket*)> other) {
	impl_->each(other);
}

void ClientsBroadcast::update(boost::asio::ip::tcp::socket* sock, std::string some) {
	impl_->each(sock, [&](boost::asio::ip::tcp::socket* sock) {
		sock->write_some(boost::asio::buffer("client " + sock->remote_endpoint().address().to_string() + ">>:" + some + "\r\n"));
	});
}
