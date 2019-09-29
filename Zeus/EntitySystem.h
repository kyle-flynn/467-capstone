#pragma once

#include <unordered_map>

#include "System.h"

#ifndef GAME_TEST_SYSTEM_H
#define GAME_TEST_SYSTEM_H

class EntitySystem : public System {
public:
	EntitySystem();

	void receiveMessage(std::shared_ptr<Message> message) const;
};

#endif