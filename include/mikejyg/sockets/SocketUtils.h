/*
 * SocketUtils.h
 *
 *  Created on: Jul 21, 2019
 *      Author: mikejyg
 */

#ifndef MIKEJYG_SOCKETUTILS_H_
#define MIKEJYG_SOCKETUTILS_H_

#ifdef _WIN32

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <winsock2.h>

#else
#include <sys/socket.h>

#endif

#include "sockfdDefs.h"
#include <sys/types.h>
#include <stdexcept>
#include <mikejyg/ErrorUtils.h>
#include <fcntl.h>
#include <string>

namespace mikejyg { namespace sockets {

/**
 * utilities for socket.
 */
class SocketUtils {
public:
	static int socket(int domain, int type, int protocol=0) {
		auto sockfd = ::socket(domain, type, protocol);
		if (sockfd==INVALID_SOCKET)
			throw ErrorUtils::ErrnoException("socket() failed:");
		return sockfd;
	}

	static void bind(SockFdType sockfd, const struct sockaddr *address, socklen_t address_len) {
		auto k = ::bind(sockfd, address, address_len);
		if (k!=0)
			throw ErrorUtils::ErrnoException("bind() failed:");
	}

	static void connect(SockFdType sockfd, const struct sockaddr *addr, socklen_t addrlen) {
		auto k = ::connect(sockfd, addr, addrlen);
		if (k!=0) {
			throw ErrorUtils::ErrnoException("connect() failed:");
		}
	}

	/**
	 * a more user friendly version of ::getsockname()
	 */
	static std::pair<std::unique_ptr<struct sockaddr_storage>, socklen_t> getsockname(SockFdType sockfd) {
		auto * addr = new struct sockaddr_storage;
		socklen_t address_len = sizeof(struct sockaddr_storage);

		auto k = ::getsockname(sockfd, (struct sockaddr*)addr, &address_len);
		if (k!=0)
			throw ErrorUtils::ErrnoException("getsockname() failed:");

		return std::pair<std::unique_ptr<struct sockaddr_storage>, socklen_t>(std::unique_ptr<struct sockaddr_storage>(addr), address_len);

	}

	static void setNonBlock(int sockfd) {
		auto k = fcntl(sockfd, F_SETFL, O_NONBLOCK);
//		std::cout << "fcntl() returns: " << k << std::endl;
		if (k)
			throw std::runtime_error(std::string("fcntl() returns non-zero: ") + std::to_string(k));
	}


};

}} /* namespace mikejyg::sockets */

#endif /* MIKEJYG_SOCKETUTILS_H_ */
