#pragma once

#include "System.h"
#include "Message.h"
#include "MessageBus.h"

#include <iostream>

#ifndef GAME_LOGGING_SYSTEM_H
#define GAME_LOGGING_SYSTEM_H

enum LogLevel : sf::Uint8 {
	COMBAT=0,
	INFO=1,
	WARN=2,
	ERROR=3
};

struct LogData {
	LogLevel level;
	std::string msg;
};

struct LogMessage : public Message {
	LogMessage() {};
	LogMessage(LogData data) : Message(std::string("LOG_MSG")) {};
	LogData data;

	friend sf::Packet& operator <<(sf::Packet& packet, const LogMessage& message) {
		return packet << message.data.level << message.data.msg;
	}
};

class LoggingSystem : public System {
public:
	LoggingSystem();
	void sendMessage(Message* message);
	void receiveMessage(Message* message);
private:
	std::queue<LogData*> logs;
};

#endif