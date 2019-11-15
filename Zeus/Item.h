#pragma once
#include <string>
#include <SFML/Graphics.hpp>

enum class type { Weapon, Equippable, Consumable, Other };
enum class weaponType { Sword, Axe, Hammer, Bow, Dagger };

class Item {

public:

	//enum type {Weapon, Equippable, Consumable, Other};

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

