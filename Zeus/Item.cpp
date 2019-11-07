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