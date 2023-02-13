#include "SyncServ.h"



namespace async_server {
	boost::asio::io_service service;
	size_t read_complete(char* buff, const boost::system::error_code& err, size_t bytes)
	{
		if (err) return 0;
		bool found = std::find(buff, buff + bytes, '\n') < buff + bytes;
		return found ? 0 : 1;
	}

	void defread(std::string&, boost::asio::ip::tcp::socket*) {}
	void defconnect(boost::asio::ip::tcp::socket*) {}
	bool defdisconnect(int bytes, boost::asio::ip::tcp::socket*) {return bytes;};

	 
	void handle_connections(Events events)
	{
		boost::asio::ip::tcp::acceptor acceptor(service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8001));
		while (true) {
			boost::asio::ip::tcp::socket sock(service);
			acceptor.accept(sock);

			std::thread([sock = std::move(sock), events]() mutable {
				char buff[1024];
				events.accept_connet(&sock);
					try {
						while (true)
						{
							size_t bytes = boost::asio::read(sock, boost::asio::buffer(buff), std::bind(read_complete, buff, std::placeholders::_1, std::placeholders::_2));
							if (!events.checkconnect(bytes, &sock)) {
								return;
							};
							std::string msg(buff, bytes);
							if (msg == "exit\r\n") {
								events.checkconnect(0, &sock);
								sock.close();
								return;
							};
							events.other_read(msg, &sock);
							sock.write_some(boost::asio::buffer(msg));
						}
					}
					catch (const std::exception&) {
						events.checkconnect(0, &sock);
					}
				}
			).detach();
		
		}

	}
}