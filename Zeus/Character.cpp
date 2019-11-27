#include "Character.h"

Character::Character() {
	name = sf::String("New Character");
	description = sf::String("Character description");
	maxHP = 10;
	maxMana = 10;
	maxStamina = 10;
	playable = false;
}

Character::Character(sf::String name) {
	this->name = name;
	description = sf::String("Character description");
	maxHP = 10;
	maxMana = 10;
	maxStamina = 10;
	playable = false;
}

float Character::getAttack() {
	if (offHand.itemType == Item::type::Weapon) {
		return mainHand.stat + offHand.stat;
	}
	else {
		return mainHand.stat;
	}
}

float Character::getDefence() {
	if (offHand.itemType == Item::type::Equippable) {
		return offHand.stat +
			head.stat +
			chest.stat +
			legs.stat;
	}
	else {
		return head.stat +
			chest.stat +
			legs.stat;
	}
}

bool operator==(Character c1, Character c2) {
	if (c1.name == c2.name &&
		c1.maxHP == c2.maxHP &&
		c1.maxMana == c2.maxMana &&
		c1.maxStamina == c2.maxStamina &&
		c1.loc == c2.loc) {
		return true;
	}
	else {
		return false;
	}
}