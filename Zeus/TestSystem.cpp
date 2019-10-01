#include "TestSystem.h"

TestSystem::TestSystem() : System(std::string("TestSystem")) {
	
}

void TestSystem::sendMessage(Message* message) {
	MessageBus::getInstance().sendMessage(message);
}

void TestSystem::receiveMessage(Message* message) {
	// Get the message from the shared pointer
	if (message->getName() == "TEST_MSG") {
		TestMessage testMesssage = (TestMessage&) message;
		//std::cout << testMesssage.getData() << std::endl;
	}
}