#include "CharacterOption.h"

CharacterOption::CharacterOption() {
	isSelected = false;
	isPressed = false;
	cName.setFont(FontManager::getInstance().oldStandard);
	playable.setFont(FontManager::getInstance().oldStandard);
	cName.setCharacterSize(TEXT_SIZE);
	playable.setCharacterSize(TEXT_SIZE);
	cName.setFillColor(sf::Color::Black);
	playable.setFillColor(sf::Color::Black);
	cName.setString(sf::String("DEFAULT TEXT"));
	playable.setString(sf::String("NPC"));
	playable.setPosition(235.0f, 0.0f);
	c = Character();
}

CharacterOption::CharacterOption(Character c) {
	isSelected = false;
	isPressed = false;
	cName.setFont(FontManager::getInstance().oldStandard);
	playable.setFont(FontManager::getInstance().oldStandard);
	cName.setCharacterSize(TEXT_SIZE);
	playable.setCharacterSize(TEXT_SIZE);
	cName.setFillColor(sf::Color::Black);
	playable.setFillColor(sf::Color::Black);
	cName.setString(c.name);
	playable.setString(sf::String(c.playable ? "Player" : "NPC"));
	playable.setPosition(235.0f, 0.0f);
	this->c = c;
}

void CharacterOption::setSelected(bool select) {
	isSelected = select;
	cName.setFillColor(select ? sf::Color::Blue : sf::Color::Black);
	playable.setFillColor(select ? sf::Color::Blue : sf::Color::Black);
}

void CharacterOption::setPressed(bool press) {
	isPressed = press;
}

void CharacterOption::update(float deltaTime, sf::Vector2i mousePosition) {
	sf::Rect<float> bounds(
		getPosition().x,
		getPosition().y,
		playable.getPosition().x + playable.getGlobalBounds().width,
		cName.getGlobalBounds().height + 7);
	if (bounds.contains(mousePosition.x, mousePosition.y)) {
		setSelected(true);
	}
	else {
		setSelected(false);
	}
	updateValues();
}

void CharacterOption::update(sf::Event event, sf::Vector2i mousePosition) {

}

sf::String CharacterOption::getName() {
	return c.name;
}

sf::String CharacterOption::getDescription() {
	return c.description;
}

sf::Sprite CharacterOption::getIcon() {
	return icon;
}

sf::Sprite CharacterOption::getAvatar() {
	return avatar;
}

void CharacterOption::updateValues() {
	cName.setString(c.name);
	playable.setString(sf::String(c.playable ? "Player" : "NPC"));
}

void CharacterOption::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = NULL;
	target.draw(cName, states);
	target.draw(playable, states);
}