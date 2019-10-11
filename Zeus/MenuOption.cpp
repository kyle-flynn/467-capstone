#include "MenuOption.h"
#include "FontManager.h"

#include <iostream>

MenuOption::MenuOption(const std::string& text, bool isSelected) {
	this->text.setFont(FontManager::getInstance().oldStandard);
	this->text.setCharacterSize(32);
	this->text.setString(text);
	this->setSelected(isSelected);
}

void MenuOption::setSelected(bool isSelected) {
	this->isSelected = isSelected;
	this->text.setFillColor(isSelected ? sf::Color(13, 64, 192) : sf::Color::White);
}

void MenuOption::update(float deltaTime, sf::Vector2i mousePosition) {
	sf::Rect<float> bounds(this->getPosition(), sf::Vector2f(this->text.getGlobalBounds().width, this->text.getGlobalBounds().height));
	if (bounds.contains(sf::Vector2f(mousePosition.x, mousePosition.y))) {
		this->setSelected(true);
	} else {
		this->setSelected(false);
	}
}

void MenuOption::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = NULL;
	//target.draw(this->goalText);
	target.draw(this->text, states);
}