#pragma once
#include <boost/asio.hpp>
namespace sync_server {
	void defread(std::string&);
	void defconnect(boost::asio::ip::tcp::socket&);
	bool defdisconnect(int);
	void handle_connections(std::function <void(std::string&)> other_read = defread, std::function <void(boost::asio::ip::tcp::socket&)> accept_connet = defconnect, std::function <bool(size_t)> checkconnect = defdisconnect);
}