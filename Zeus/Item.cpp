#include "Item.h"

Item::Item() {
	this->name = "New item";
	this->description = "Item description";
	this->itemType = Other;
	this->stat = 0.0;
}

Item::Item(sf::String name) {
	this->name = name;
	this->description = "Item description";
	this->itemType = Other;
	this->stat = 0.0;
}

Item::Item(sf::String name, type itemType) {
	this->name = name;
	this->description = "Item descipriton";
	this->itemType = itemType;
	this->stat = 0.0;
}

bool operator== (Item item1, Item item2) {
	if (item1.name == item2.name &&
		item1.itemType == item2.itemType &&
		item1.stat == item2.stat &&
		item1.description == item2.description) {
		return true;
	}
	else {
		return false;
	}
}