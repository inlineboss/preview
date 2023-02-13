#pragma once
#include <vector>
#include <boost/asio.hpp>

class Clients
{
public:
	Clients();
	~Clients();
	virtual void add(boost::asio::ip::tcp::socket* sock);
	virtual void remove(boost::asio::ip::tcp::socket* sock);
	virtual void each(boost::asio::ip::tcp::socket* sock, std::function <void(boost::asio::ip::tcp::socket*)> other);
	virtual void each(std::function <void(boost::asio::ip::tcp::socket*)> other);

private:
	std::vector<boost::asio::ip::tcp::socket*> client_;
};