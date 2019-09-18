#include "Entity.h"

Entity::Entity() {
	/* You can add default, base components to entities here. */
}

void Entity::addComponent(IComponent& component) {
	this->components.insert(std::make_pair(component.getId(), &component));
}

void Entity::removeComponent(int uid) {
	if (this->components.find(uid) != this->components.end()) {
		this->components.erase(uid);
	}
}

IComponent* Entity::getComponent(int uid) {
	return this->components.at(uid);
}

std::unordered_map<int, IComponent*>Entity::getComponents() {
	return this->components;
}