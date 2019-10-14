#include "NetworkManager.h"

#include <iostream>

NetworkManager::NetworkManager() {
	this->networkType = 0;
	this->running = false;
}

NetworkManager& NetworkManager::getInstance() {
	static NetworkManager instance;
	return instance;
}

void NetworkManager::startServer(int port) {
	std::thread serverThread([=]() {
		sf::Socket::Status status = this->server.listen(port);

		if (status != sf::Socket::Done) {
			// ERROR
		} else {
			std::cout << "Server has started." << std::endl;
		}
	});
	serverThread.detach();
}

void NetworkManager::startClient(const char* address, int port) {
	std::thread clientThread([=]() {
		sf::Socket::Status status = this->client.connect(address, port);

		if (status != sf::Socket::Done) {
			// ERROR
		} else {
			this->running = true;
			while (running) {
				sf::Packet packet;
				this->client.receive(packet);

				Message message;
				if (packet >> message) {
					if (message.type == "LOG_MSG") {
						LogMessage logMessage;
						packet >> logMessage;
					}
				} else {
					// ERROR
				}
			}
		}
	});
	clientThread.detach();
}

int NetworkManager::getNetworkType() { 
	return this->networkType; 
}
