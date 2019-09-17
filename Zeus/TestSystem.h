#pragma once

#include <iostream>

#include "System.h"
#include "TestMessage.h"

#ifndef GAME_TEST_SYSTEM_H
#define GAME_TEST_SYSTEM_H

class TestSystem : public System {
public:
	TestSystem();

	void receiveMessage(std::shared_ptr<Message> message) const;
};

#endif