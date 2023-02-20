#include "ClientsBanner.h"
#include <iostream>

ClientsBanner::ClientsBanner(std::string banner, IClients* impl) :
	impl_(impl), banner_(banner)
{

}

ClientsBanner::~ClientsBanner()
{
}

void ClientsBanner::add(boost::asio::ip::tcp::socket* sock) {
	sock->write_some(boost::asio::buffer(banner_));
	impl_->add(sock);
}

void ClientsBanner::remove(boost::asio::ip::tcp::socket* sock) {
	impl_->remove(sock);
}

void ClientsBanner::each(boost::asio::ip::tcp::socket* sock, std::function <void(boost::asio::ip::tcp::socket*)> other) {
	impl_->each(sock, other);
}


void ClientsBanner::each(std::function <void(boost::asio::ip::tcp::socket*)> other) {
	impl_->each(other);
}

void ClientsBanner::update(boost::asio::ip::tcp::socket* sock, std::string some) {
	impl_->update(sock, some);
}
