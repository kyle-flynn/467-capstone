#pragma once

#include "Message.h"

#ifndef GAME_TEST_MESSAGE_H
#define GAME_TEST_MESSAGE_H

struct Test : MessageData {
	std::string data;
};

class TestMessage : public Message {
public:
	TestMessage(Test* data) : Message(std::string("TEST_MSG"), data) {}
	TestMessage& getData() { return this->getData(); };
};

#endif