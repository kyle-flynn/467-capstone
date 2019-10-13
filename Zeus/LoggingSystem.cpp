#include "LoggingSystem.h"

LoggingSystem::LoggingSystem() : System(std::string("Logger")) {
	this->logs = {};
}

void LoggingSystem::sendMessage(Message* message) {
	MessageBus::getInstance().sendMessage(message);
}

void LoggingSystem::receiveMessage(Message* message) {
	// Get the message from the shared pointer
	if (message->getName() == "LOG_MSG") {
		LogMessage* log = (LogMessage*)message;
		// Needs to be a static cast.
		LogData* logData = static_cast<LogData*>(log->getData());
		logs.push(logData);
	}
}