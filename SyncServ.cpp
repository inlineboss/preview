#include "SyncServ.h"

namespace sync_server {
	boost::asio::io_service service;
	size_t read_complete(char* buff, const boost::system::error_code& err, size_t bytes)
	{
		if (err) return 0;
		bool found = std::find(buff, buff + bytes, '\n') < buff + bytes;
		// we read one-by-one until we get to enter, no buffering
		return found ? 0 : 1;
	}

	void defread(std::string&) {}
	void defconnect(boost::asio::ip::tcp::socket&) {}
	bool defdisconnect(int bytes) {return bytes;};

	 
	void handle_connections(std::function <void (std::string &)> other_read, std::function <void(boost::asio::ip::tcp::socket&)> accept_connet, std::function <bool(size_t)> checkconnect)
	{
		boost::asio::ip::tcp::acceptor acceptor(service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8001));
		char buff[1024];
		boost::asio::ip::tcp::socket sock(service);
		acceptor.accept(sock);
		accept_connet(sock);
		
			while (true)
			{
				size_t bytes = boost::asio::read(sock, boost::asio::buffer(buff), std::bind(read_complete, buff, std::placeholders::_1, std::placeholders::_2));
				if (!checkconnect(bytes)) {
					return;
				};
				std::string msg(buff, bytes);
				if (msg == "exit\r\n") {
					checkconnect(0);
					sock.close();
					return;
				};
				other_read(msg);
				sock.write_some(boost::asio::buffer(msg));
				

			}

	}
}