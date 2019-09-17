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
class Message;
class System;

class MessageBus {
public:
	static MessageBus& getInstance();

	void start();
	void terminate();
	void setUpdatesPerSecond(double updates);
	void sendMessage(std::shared_ptr<Message> message);
	void addSystem(std::shared_ptr<System> system);
private:
	MessageBus();

	double ups;
	bool running;
	std::queue<std::shared_ptr<Message>> messages;
	std::vector<std::shared_ptr<System>> systems;
	void poll();
};

#endif // !GAME_MESSAGE_BUS_H