#pragma once
#include <string>
#include <SFML/Graphics.hpp>

//enum class type { Weapon, Equippable, Consumable, Other };

class Item {

public:

	enum class type {Weapon, Equippable, Consumable, Other};

	sf::String name, description;
	type itemType;
	weaponType wType;
	float stat;
	sf::Texture icon;

	Item();
	Item(sf::String name);
	Item(sf::String name, type itemType);
	friend bool operator==(Item item1, Item item2);

};

