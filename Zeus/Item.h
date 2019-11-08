#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Item {

public:

	enum type {Weapon, Equippable, Consumable, Other};

	sf::String name, description;
	type itemType;
	float stat;
	sf::Texture icon;

	Item();
	Item(sf::String name);
	Item(sf::String name, type itemType);
	friend bool operator==(Item item1, Item item2);

};

