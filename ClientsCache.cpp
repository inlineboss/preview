#include "ClientsCache.h"

ClientsCache::ClientsCache()
{
}

ClientsCache::~ClientsCache()
{
}

void ClientsCache::add(boost::asio::ip::tcp::socket* sock) {
	this->client_.push_back(sock);
}

void ClientsCache::remove(boost::asio::ip::tcp::socket* sock) {
	for (int client = 0; client_.size() > client; client++) {
		if (client_[client] == sock) {
			this->client_.erase(this->client_.begin() + client);
			break;
		}
	}
}

void ClientsCache::each(boost::asio::ip::tcp::socket* sock, std::function <void(boost::asio::ip::tcp::socket*)> other) {
	for (int client = 0; client_.size() > client; client++) {
		if (client_[client]->remote_endpoint().address().to_string() != sock->remote_endpoint().address().to_string())
			other(client_[client]);
	}
}


void ClientsCache::each(std::function <void(boost::asio::ip::tcp::socket*)> other) {
	this->each(nullptr, other);
}

void ClientsCache::update(boost::asio::ip::tcp::socket* sock, std::string some) {

}
