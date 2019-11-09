#include "Item.h"

#include <iostream>

Item::Item() {
	this->name = "New item";
	this->description = "Item description";
	this->itemType = type::Other;
	this->stat = 0.0;
}

Item::Item(sf::String name) {
	this->name = name;
	this->description = "Item description";
	this->itemType = type::Other;
	this->stat = 0.0;
}

Item::Item(sf::String name, type itemType) {
	this->name = name;
	this->description = "Item description";
	this->itemType = itemType;
	this->stat = 0.0;
}

bool operator== (Item item1, Item item2) {
	if (item1.name.toAnsiString().compare(item2.name.toAnsiString()) == 0 &&
		item1.itemType == item2.itemType &&
		item1.stat == item2.stat &&
		item1.description.toAnsiString().compare(item2.description.toAnsiString()) == 0) {
		return true;
	}
	else {
		return false;
	}
}