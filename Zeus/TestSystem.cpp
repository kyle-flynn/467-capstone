#include "TestSystem.h"

TestSystem::TestSystem() : System(std::string("TestSystem")) {

}

void TestSystem::receiveMessage(std::shared_ptr<Message> message) const {
	// Get the message from the shared pointer
	Message* mPtr = message.get();
	if (mPtr->getName() == "TEST_MSG") {
		TestMessage* testMesssage = (TestMessage*) mPtr;
		std::string* data = static_cast<std::string*>(testMesssage->getData().get());
		std::cout << *data << std::endl;
	}
}