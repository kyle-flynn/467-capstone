#pragma once

#include <string>

#include "MessageBus.h"

#ifndef GAME_SYSTEM_H
#define GAME_SYSTEM_H

class System {
public:
	System(std::string name);

	void sendMessage(std::shared_ptr<Message> message);
	virtual void receiveMessage(std::shared_ptr<Message> message) const = 0;
private:
	std::string name;
};

#endif // !GAME_SYSTEM_H