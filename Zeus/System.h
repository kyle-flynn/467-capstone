#pragma once

#include <string>

#include "Message.h"

#ifndef GAME_SYSTEM_H
#define GAME_SYSTEM_H

class System {
public:
	System(std::string name) : name(name) {};

	virtual void sendMessage(Message* message) = 0;
	virtual void receiveMessage(Message* message) = 0;
private:
	std::string name;
};

#endif // !GAME_SYSTEM_H