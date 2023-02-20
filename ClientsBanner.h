#pragma once
#include "Clients.h"

class ClientsBanner : public IClients
{
private:
	IClients* impl_;
	const std::vector<std::string> banner_;
	int i;
public:
	ClientsBanner(std::vector<std::string>, IClients*);
	~ClientsBanner();
	virtual void add(boost::asio::ip::tcp::socket* sock) override;
	virtual void remove(boost::asio::ip::tcp::socket* sock) override;
	virtual void each(boost::asio::ip::tcp::socket* sock, std::function <void(boost::asio::ip::tcp::socket*)> other) override;
	virtual void each(std::function <void(boost::asio::ip::tcp::socket*)> other) override;
	virtual void update(boost::asio::ip::tcp::socket* sock, std::string some) override;

};