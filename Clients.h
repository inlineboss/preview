#pragma once
#include <vector>
#include <boost/asio.hpp>

class IClients
{
public:
	virtual ~IClients() {};
	virtual void add(boost::asio::ip::tcp::socket* sock) = 0;
	virtual void remove(boost::asio::ip::tcp::socket* sock) = 0;
	virtual void each(boost::asio::ip::tcp::socket* sock, std::function <void(boost::asio::ip::tcp::socket*)> other) = 0;
	virtual void each(std::function <void(boost::asio::ip::tcp::socket*)> other) = 0;
	virtual void update(boost::asio::ip::tcp::socket* sock, std::string some) = 0;
};