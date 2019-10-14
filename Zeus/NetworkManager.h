#pragma once

#include <SFML/Network.hpp>
#include <vector>
#include <thread>
#include <memory>

#include "MessageBus.h"
#include "Message.h"

#include "LoggingSystem.h"

#ifndef GAME_NETWORK_MANAGER_H
#define GAME_NETWORK_MANAGER_H

class NetworkManager {
public:
	static const int TYPE_DISCONNECTED = 0;
	static const int TYPE_SERVER = 1;
	static const int TYPE_CLIENT = 2;

	static NetworkManager& getInstance();
	void startServer(int port);
	void startClient(const char* address, int port);
	int getNetworkType();
private:
	// These variables are in case of the server scenario.
	sf::TcpListener server;
	std::vector<std::unique_ptr<sf::TcpSocket>> clients;
	// These variables are in case of the client scenario.
	sf::TcpSocket client;

	int networkType;
	bool running;

	NetworkManager();
};

#endif