#include "Quest.h"

#include <iostream>

Quest::Quest() {
	this->name = "New Quest";
	this->goal = "Quest goal";
	this->reward = "Quest Reward;
}

Quest::Quest(sf::String name) {
	this->name = name;
	this->goal = "Goal";
	this->reward = "Reward";
	this->questType = type::Other;
}

Quest::Quest(sf::String name, type questType) {
	this->name = name;
	this->goal = "Goal";
	this->reward = "Reward";
	this->questType = questType;
}

bool operator== (Quest quest1, Quest quest2) {
	if (quest1.name.toAnsiString().compare(quest2.name.toAnsiString()) == 0 &&
		quest1.questType == quest2.questType  == 0) {
		return true;
	}
	else {
		return false;
	}
}