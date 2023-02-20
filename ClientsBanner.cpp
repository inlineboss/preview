#include "ClientsBanner.h"
#include <iostream>

ClientsBanner::ClientsBanner(std::vector<std::string> banner, IClients* impl) :
	impl_(impl), banner_(banner), i(0)
{
}

ClientsBanner::~ClientsBanner()
{
}

void ClientsBanner::add(boost::asio::ip::tcp::socket* sock) {
	sock->write_some(boost::asio::buffer(banner_[i]));
	(i<banner_.size()) ? this->i++ : this->i=0;
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
