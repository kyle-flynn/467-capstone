#pragma once

#include <iostream>

#include "System.h"
#include "MessageBus.h"
#include "TestMessage.h"

#ifndef GAME_TEST_SYSTEM_H
#define GAME_TEST_SYSTEM_H

class TestSystem : public System {
public:
	TestSystem();
	void sendMessage(Message* message);
	void receiveMessage(Message* message);
};

#endif