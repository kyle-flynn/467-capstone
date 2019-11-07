#include "ItemOption.h"

#include <iostream>

ItemOption::ItemOption() {
	isSelected = false;
	isPressed = false;
	itemName.setFont(FontManager::getInstance().oldStandard);
	itemName.setCharacterSize(TEXT_SIZE);
	itemName.setFillColor(sf::Color::Black);
	itemName.setString(sf::String("New item"));
	itemType.setFont(FontManager::getInstance().oldStandard);
	itemType.setCharacterSize(TEXT_SIZE);
	itemType.setFillColor(sf::Color::Black);
	itemType.setString(sf::String("Other"));
	itemType.setPosition(235.0f, 0.0f);
	item = Item();
}

ItemOption::ItemOption(Item item) {
	isSelected = false;
	isPressed = false;
	itemName.setFont(FontManager::getInstance().oldStandard);
	itemName.setCharacterSize(TEXT_SIZE);
	itemName.setFillColor(sf::Color::Black);
	itemName.setString(item.name);
	itemType.setFont(FontManager::getInstance().oldStandard);
	itemType.setCharacterSize(TEXT_SIZE);
	itemType.setFillColor(sf::Color::Black);
	itemType.setString(typeToString(item.itemType));
	itemType.setPosition(200.0f, 0.0f);
	this->item = item;
}

void ItemOption::setSelected(bool select) {
	isSelected = select;
	itemName.setFillColor(select ? sf::Color::Blue : sf::Color::Black);
	itemType.setFillColor(select ? sf::Color::Blue : sf::Color::Black);
}

void ItemOption::setPressed(bool press) {
	isPressed = press;
}

void ItemOption::update(float deltaTime, sf::Vector2i mousePosition) {
	sf::Rect<float> bounds(
		getPosition().x,
		getPosition().y,
		itemType.getPosition().x + itemType.getGlobalBounds().width,
		itemName.getGlobalBounds().height + 7);
	if (bounds.contains(mousePosition.x, mousePosition.y)) {
		setSelected(true);
	}
	else {
		setSelected(false);
	}
}

void ItemOption::update(sf::Event event, sf::Vector2i mousePosition) {

}

sf::String ItemOption::getName() {
	return itemName.getString();
}

sf::String ItemOption::getType() {
	return itemType.getString();
}

sf::Sprite ItemOption::getIcon() {
	return sprite;
}

sf::String ItemOption::typeToString(Item::type type) {
	switch (type) {
	case Item::Weapon:
		return sf::String("Weapon");
	case Item::Equippable:
		return sf::String("Equippable");
	case Item::Consumable:
		return sf::String("Consumable");
	case Item::Other:
		return sf::String("Other");
	}
}

void ItemOption::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = NULL;
	target.draw(sprite, states);
	target.draw(itemName, states);
	target.draw(itemType, states);
}