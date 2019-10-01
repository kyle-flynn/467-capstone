#pragma once

#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include <queue>
#include <vector>

#include <SFML/System/Clock.hpp>

#include "Message.h"
#include "System.h"

#ifndef GAME_MESSAGE_BUS_H
#define GAME_MESSAGE_BUS_H

/* Forward declarations */

class MessageBus {
public:
	static MessageBus& getInstance();

	void start();
	void terminate();
	void setUpdatesPerSecond(double updates);
	void sendMessage(Message* message);
	void addSystem(System* system);
private:
	MessageBus();

	double ups;
	bool running;
	std::queue<Message*> messages;
	std::vector<System*> systems;
	void poll();
};

#endif // !GAME_MESSAGE_BUS_H