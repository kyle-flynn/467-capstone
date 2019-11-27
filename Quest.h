#pragma once
#include <string>
#include <SFML/Graphics.hpp>

//enum class type {Name, Goal, Reward};

class Quest {

public:

	enum class type {name, goal, reward};

	sf::String name, goal,reward;
	type questType;
	float stat;

	Quest();
	Quest(sf::String name);
	Quest(sf::String name, String goal, String reward);
	friend bool operator==(Quest quest1, Quest quest2);

};

