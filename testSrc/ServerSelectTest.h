/*
 * ServerSelectTest.h
 *
 *  Created on: Mar, 2022
 *      Author: mikejyg
 */

#ifndef SERVERSELECTTEST_H_
#define SERVERSELECTTEST_H_

#include <mikejyg/sockets/ServerSocket.h>
#include <mikejyg/sockets/InetAddress.h>
#include <iostream>
#include <sys/select.h>
#include <mikejyg/ErrorUtils.h>
#include <fcntl.h>
#include <mikejyg/sockets/SelectUtils.h>
#include <mikejyg/sockets/SockaddrUtils.h>

/**
 * a test using select and non-block mode for a TCP server socket.
 */
class ServerSelectTest {
public:
	static const unsigned BUFFER_SIZE=1024;

private:
	int port = 40000;

	char buffer[BUFFER_SIZE];

public:
	void test() {
		mikejyg::sockets::ServerSocket serverSocket(port, mikejyg::sockets::Inet4Address("127.0.0.1"));

			std::cout << "server socket address: " << serverSocket.getSocketAddress().toString() << std::endl;

			serverSocket.listen();

			while (true) {
				std::cout << "accepting connections..." << std::endl;

				auto client = serverSocket.accept();

				auto & streamSocket = std::get<0>(client);
				auto clientFd = streamSocket.getSockfd();
				std::cout << "client connected: fd: " << clientFd
						<< ", client socket: " << std::get<1>(client).toString() << std::endl;

				mikejyg::sockets::SocketUtils::setNonBlock(clientFd);

				while (true) {

					auto k = mikejyg::sockets::SelectUtils::waitForRead(clientFd);

					if (k==0) {
						std::cout << "select() returns 0, exiting..." << std::endl;
						break;
					}

					k = recv(clientFd, buffer, BUFFER_SIZE, 0);

					if (k==0) {
						std::cout << "recv() returns 0 - exiting..." << std::endl;
						break;
					}

					std::cout << "received: \"";
					for (auto i=0; i<k; i++) {
						std::cout << buffer[i];
					}
					std::cout << '"' << std::endl;

				}

				streamSocket.close();

			}

			serverSocket.close();
		}

};

#endif /* SERVERSELECTTEST_H_ */
