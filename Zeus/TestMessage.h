#pragma once

#include "Message.h"

#ifndef GAME_TEST_MESSAGE_H
#define GAME_TEST_MESSAGE_H

class TestMessage : public Message {
public:
	TestMessage(std::string data);
};

#endif