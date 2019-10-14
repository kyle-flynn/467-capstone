#include "LoggingSystem.h"

LoggingSystem::LoggingSystem() : System(std::string("Logger")) {
	this->logs = {};
}

void LoggingSystem::sendMessage(Message* message) {
	MessageBus::getInstance().sendMessage(message);
}

void LoggingSystem::receiveMessage(Message* message) {
	// Get the message from the shared pointer
	if (message->type == "LOG_MSG") {
		LogMessage* log = (LogMessage*)message;
		LogData logData = log->data;
		logs.push(&logData);
	}
}