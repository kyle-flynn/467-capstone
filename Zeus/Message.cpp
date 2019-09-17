#include "Message.h"

Message::Message(std::string name, std::shared_ptr<void> data) {
	this->name = name;
	this->data = data;
}

std::string Message::getName() {
	return this->name;
}

std::shared_ptr<void> Message::getData() {
	return this->data;
}