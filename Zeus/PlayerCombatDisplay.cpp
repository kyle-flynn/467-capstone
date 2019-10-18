#include "PlayerCombatDisplay.h"

PlayerCombatDisplay::PlayerCombatDisplay(std::string name) {
	this->combatDisplay.loadFromFile("Resources/Sprites/player_combat_display.png");
	this->combatSprite.setTexture(this->combatDisplay);
	this->combatSprite.setScale(2.0f, 2.0f);
	this->name.setString(name);
	this->name.setFont(FontManager::getInstance().joystick);
	this->name.setFillColor(sf::Color::Black);
	this->name.setCharacterSize(22);

	this->hitpoints.setString("HP");
	this->hitpoints.setFont(FontManager::getInstance().joystick);
	this->hitpoints.setCharacterSize(22);
	this->hitpoints.setOutlineThickness(1.5f);
	this->hitpoints.setLetterSpacing(1.5f);
	this->hitpoints.setFillColor(sf::Color::White);
	this->hitpoints.setOutlineColor(sf::Color::Black);

	this->mana.setString("MANA");
	this->mana.setFont(FontManager::getInstance().joystick);
	this->mana.setCharacterSize(22);
	this->mana.setOutlineThickness(1.5f);
	this->mana.setLetterSpacing(1.5f);
	this->mana.setFillColor(sf::Color::White);
	this->mana.setOutlineColor(sf::Color::Black);

	sf::FloatRect textRect = this->name.getLocalBounds();
	this->name.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	this->name.setPosition(sf::Vector2f(this->combatSprite.getGlobalBounds().width / 2.0f, this->getPosition().y + 27.0f));

	this->hitpoints.setPosition(sf::Vector2f(20.0f, 50.0f));
	this->mana.setPosition(sf::Vector2f(20.0f, 90.0f));
}

void PlayerCombatDisplay::update(float deltaTime) {}

void PlayerCombatDisplay::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(this->combatSprite, states);
	target.draw(this->name, states);
	target.draw(this->hitpoints);
	target.draw(this->mana);
}