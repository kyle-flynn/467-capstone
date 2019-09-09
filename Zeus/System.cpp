#include "System.h"

System::System(std::string name) {
	this->name = name;
}

void System::sendMessage(std::shared_ptr<Message> message) {
	MessageBus::getInstance().sendMessage(message);
}