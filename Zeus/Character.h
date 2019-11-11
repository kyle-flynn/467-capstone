#pragma once

#include <SFML/Graphics.hpp>

#include "Item.h"

class Character {

public:

	sf::String name, description;
	float maxHP, maxMana, maxStamina;
	sf::Texture icon, sprite;
	bool playable;
	sf::Vector2f loc;
	std::vector<Item> equipment;
	Item head, chest, legs, mainHand, offHand, back;

	Character();
	Character(sf::String name);
	friend bool operator==(Character c1, Character c2);

};

