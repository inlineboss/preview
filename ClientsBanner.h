#pragma once
#include "Clients.h"

class ClientsBanner : public IClients
{
private:
	IClients* impl_;
	const std::string banner_;
public:
	ClientsBanner(std::string, IClients*);
	~ClientsBanner();
	virtual void add(boost::asio::ip::tcp::socket* sock) override;
	virtual void remove(boost::asio::ip::tcp::socket* sock) override;
	virtual void each(boost::asio::ip::tcp::socket* sock, std::function <void(boost::asio::ip::tcp::socket*)> other) override;
	virtual void each(std::function <void(boost::asio::ip::tcp::socket*)> other) override;
	virtual void update(boost::asio::ip::tcp::socket* sock, std::string some) override;

};