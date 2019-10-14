#pragma once

#include <unordered_map>

#include "System.h"
#include "MessageBus.h"

#ifndef GAME_TEST_SYSTEM_H
#define GAME_TEST_SYSTEM_H

class EntitySystem : public System {
public:
	EntitySystem();
	void sendMessage(Message* message);
	void receiveMessage(Message* message);
};

#endif