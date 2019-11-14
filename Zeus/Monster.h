#pragma once

#include <SFML/Graphics.hpp>


class Monster {

public:

	enum class type { Ground, Flying };

	type mType;
	sf::String name, description;
	float maxHP;
	sf::Vector2f loc;
	sf::Texture icon, sprite;
	
	Monster();
	Monster(sf::String name);
	friend bool operator==(Monster m1, Monster m2);
};

