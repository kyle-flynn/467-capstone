#include "EntitySystem.h"

EntitySystem::EntitySystem() : System(std::string("EntitySystem")) {

}

void EntitySystem::receiveMessage(std::shared_ptr<Message> message) const {
	// Get the message from the shared pointer
	Message* mPtr = message.get();
	if (mPtr->getName() == "ENTITY_ADD") {

		/*
		TestMessage* testMesssage = (TestMessage*)mPtr;
		std::string* data = static_cast<std::string*>(testMesssage->getData().get());
		std::cout << *data << std::endl;
		*/
	}
}