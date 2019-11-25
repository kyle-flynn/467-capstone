#include "MonsterOption.h"

MonsterOption::MonsterOption() {
	isSelected = false;
	isPressed = false;
	mName.setFont(FontManager::getInstance().oldStandard);
	type.setFont(FontManager::getInstance().oldStandard);
	mName.setCharacterSize(TEXT_SIZE);
	type.setCharacterSize(TEXT_SIZE);
	mName.setFillColor(sf::Color::Black);
	type.setFillColor(sf::Color::Black);
	mName.setString(sf::String("DEFAULT TEXT"));
	type.setString(sf::String("Ground"));
	type.setPosition(235.0f, 0.0f);
	m = Monster();
}

MonsterOption::MonsterOption(Monster m) {
	isSelected = false;
	isPressed = false;
	mName.setFont(FontManager::getInstance().oldStandard);
	type.setFont(FontManager::getInstance().oldStandard);
	mName.setCharacterSize(TEXT_SIZE);
	type.setCharacterSize(TEXT_SIZE);
	mName.setFillColor(sf::Color::Black);
	type.setFillColor(sf::Color::Black);
	mName.setString(sf::String("DEFAULT TEXT"));
	type.setString(sf::String("Ground"));
	type.setPosition(235.0f, 0.0f);
	this->m = m;
}

void MonsterOption::setSelected(bool select) {
	isSelected = select;
	mName.setFillColor(select ? sf::Color::Blue : sf::Color::Black);
	type.setFillColor(select ? sf::Color::Blue : sf::Color::Black);
}

void MonsterOption::setPressed(bool press) {
	isPressed = press;
}

void MonsterOption::update(float deltaTime, sf::Vector2i mousePostiion) {
	sf::Rect<float> bounds(
		getPosition().x,
		getPosition().y,
		type.getPosition().x + type.getGlobalBounds().width,
		mName.getGlobalBounds().height + 7);
	if (bounds.contains(mousePostiion.x, mousePostiion.y)) {
		setSelected(true);
	}
	else {
		setSelected(false);
	}
	updateValues();
}

void MonsterOption::update(sf::Event event, sf::Vector2i mousePosition) {
}

sf::String MonsterOption::getName() {
	return m.name;
}

sf::String MonsterOption::getDescription() {
	return m.description;
}

sf::Sprite MonsterOption::getIcon() {
	return icon;
}

sf::Sprite MonsterOption::getAvatar() {
	return avatar;
}

void MonsterOption::updateValues() {
	mName.setString(m.name);
	type.setString(sf::String(m.mType == Monster::type::Ground ? "Ground" : "Air"));
}

void MonsterOption::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = NULL;
	target.draw(mName, states);
	target.draw(type, states);
}
