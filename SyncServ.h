#pragma once
#include <boost/asio.hpp>
namespace async_server {
	void defread(std::string&, boost::asio::ip::tcp::socket*);
	void defconnect(boost::asio::ip::tcp::socket*);
	bool defdisconnect(int, boost::asio::ip::tcp::socket*);

	using ReadMessageEvent = std::function <void(std::string&, boost::asio::ip::tcp::socket*)>;
	using AcceptEvent = std::function <void(boost::asio::ip::tcp::socket*)>;
	using DisconnectEvent = std::function <bool(size_t, boost::asio::ip::tcp::socket*)>;

	struct Events
	{
		ReadMessageEvent other_read = defread;
		AcceptEvent accept_connet = defconnect;
		DisconnectEvent checkconnect = defdisconnect;
	};

	void handle_connections(Events);
}