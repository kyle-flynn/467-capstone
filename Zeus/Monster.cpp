#include "Monster.h"

Monster::Monster() {
	name = sf::String("New Monster");
	description = sf::String("Monster Description");
	mType = type::Ground;
	maxHP = 10;
}

Monster::Monster(sf::String name) {
	this->name = name;
	description = sf::String("Monster Description");
	mType = type::Ground;
	maxHP = 10;
}

bool operator==(Monster m1, Monster m2) {
	if (m1.name == m2.name &&
		m1.maxHP == m2.maxHP &&
		m1.description == m2.description) {
		return true;
	}
	else {
		return false;
	}
}