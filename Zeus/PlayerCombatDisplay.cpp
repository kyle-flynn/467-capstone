#include "PlayerCombatDisplay.h"

PlayerCombatDisplay::PlayerCombatDisplay(std::string name, sf::Sprite& playerSprite) :
	playerSprite(playerSprite)
{
	this->combatDisplay.loadFromFile("Resources/Sprites/player_combat_display.png");
	this->battleTextbox.setTexture(this->combatDisplay);
	this->battleTextbox.setScale(2.0f, 2.0f);
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

	float width = this->battleTextbox.getGlobalBounds().width;
	sf::FloatRect textRect = this->name.getLocalBounds();
	this->name.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	this->name.setPosition(sf::Vector2f(this->battleTextbox.getGlobalBounds().width / 2.0f, this->getPosition().y + 27.0f));

	this->hitpoints.setPosition(sf::Vector2f(20.0f, 50.0f));
	this->mana.setPosition(sf::Vector2f(20.0f, 93.0f));

	// Scale by height.
	float scale = 40.0f / this->playerSprite.getGlobalBounds().height;
	this->playerSprite.setScale(scale, scale);
	this->playerSprite.setPosition((width / 2) - (this->playerSprite.getGlobalBounds().width / 2), -(this->playerSprite.getGlobalBounds().height / 2));
}

void PlayerCombatDisplay::update(float deltaTime) {}

void PlayerCombatDisplay::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = NULL;

	target.draw(this->battleTextbox, states);
	target.draw(this->name, states);
	target.draw(this->hitpoints, states);
	target.draw(this->mana, states);
	target.draw(this->playerSprite, states);
}

float PlayerCombatDisplay::getWidth() {
	return this->battleTextbox.getGlobalBounds().width;
}