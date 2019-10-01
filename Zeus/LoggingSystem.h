#pragma once

#include "System.h"
#include "Message.h"
#include "MessageBus.h"

#include <iostream>

#ifndef GAME_LOGGING_SYSTEM_H
#define GAME_LOGGING_SYSTEM_H

enum LogLevel {
	COMBAT,
	INFO,
	WARN,
	ERROR
};

struct LogData : MessageData {
	LogLevel level;
	std::string msg;
};

class LoggingSystem : public System {
public:
	LoggingSystem();
	void sendMessage(Message* message);
	void receiveMessage(Message* message);
private:
	std::queue<LogData*> logs;
};

class LogMessage : public Message {
public:
	LogMessage(LogData* data) : Message(std::string("LOG_MSG"), data) {}
	//LogData* getData() { return this->getData(); };
};

#endif