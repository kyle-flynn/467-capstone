#pragma once

#include <memory>
#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "IComponent.h"

#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

class Entity {
public:
	Entity();
	void addComponent(IComponent& component);
	void removeComponent(int uid);
	IComponent* getComponent(int uid);
	std::unordered_map<int, IComponent*> getComponents();
private:
	std::unordered_map<int, IComponent*> components;
};

#endif