#pragma once

#include <string>

#ifndef GAME_MESSAGE_H
#define GAME_MESSAGE_H

struct MessageData {};

class Message {
public:
	Message(std::string name, MessageData* data) : name(name), data(data) {};

	std::string getName() { return name; };
	MessageData* getData() { return data; };
private:
	std::string name;
	MessageData* data;
};

#endif // !GAME_MESSAGE_H