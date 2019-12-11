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
			this->running = true;
			selector.add(this->server);
			std::cout << "Server is running" << std::endl;
			while (this->running) {
				if (selector.wait()) {
					// Incoming connection
					if (selector.isReady(this->server)) {
						std::cout << "New connection" << std::endl;
						auto client = std::make_unique<sf::TcpSocket>();
						if (this->server.accept(*client) != sf::Socket::Done) {
							std::cout << "Error accepting new connection" << std::endl;
						} else {
							selector.add(*client);
							this->clients.push_back(std::move(client));
						}
					// Incoming packet
					} else {
						
					}
				}
			}
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
			std::cout << "Connected to host" << std::endl;
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
