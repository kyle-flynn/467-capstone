#include "EntitySystem.h"

EntitySystem::EntitySystem() : System(std::string("EntitySystem")) {

}

void EntitySystem::sendMessage(Message* message) {
	MessageBus::getInstance().sendMessage(message);
}

void EntitySystem::receiveMessage(Message* message) {}