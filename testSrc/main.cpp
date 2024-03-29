/*
 * main.cpp
 *
 * Author: mikejyg
 */

#ifdef _WIN32
#include <mikejyg/sockets/WsaService.h>
#endif

#include "mikejyg/sockets/SockaddrTest.h"
#include "mikejyg/sockets/SocketTest.h"
#include "mikejyg/sockets/AdapterInfo.h"
#include <mikejyg/OstreamBuilder.h>
#include "ServerSelectTest.h"

using namespace mikejyg::sockets;
using namespace std;

void printHelp() {
	cout << "usages: cp2socks command" << endl;
	cout << "\tadapterInfoTest\trun AdapterInfo tests (Windows only)." << endl;
	cout << "\tsockaddrTest\trun SockaddrTest." << endl;
	cout << "\tsocketTest\trun SocketTest." << endl;
	cout << "\tserverSelectTest\trun ServerSelectTest." << endl;
}

int main(int argc, char **argv) {
	StreamSocketTest::sanityCheck();

#ifdef _WIN32
	WsaService::getInstance();
#endif

	if (argc<2) {
		std::cout << "missing command argument." << std::endl;
		printHelp();
		exit(1);
	}

	int argIdx=1;
	std::string cmdStr = argv[argIdx];

	if (cmdStr=="sockaddrTest") {
		SockaddrTest::test(argc-argIdx, argv+argIdx);

#ifdef _WIN32
	} else if (cmdStr=="adapterInfoTest") {
		std::cout << "AdapterInfo..." << std::endl;
		AdapterInfo::ipconfig();
		AdapterInfo::getAdaptersAddresses();

#endif
	} else if (cmdStr=="socketTest") {
		SocketTest socketTest;
		socketTest.test(argc-argIdx, argv+argIdx);

	} else if (cmdStr=="serverSelectTest") {
		ServerSelectTest serverSelectTest;
		serverSelectTest.test();

	} else {
		std::cout << "unknown command: " << cmdStr << std::endl;
		printHelp();
		exit(1);
	}


}

