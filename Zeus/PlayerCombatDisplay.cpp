#include "PlayerCombatDisplay.h"

PlayerCombatDisplay::PlayerCombatDisplay(std::string name, sf::Sprite& playerSprite) :
	playerSprite(playerSprite),
	isActive(false),
	up(true),
	timeElapsed(0)
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

	this->hitpointsValue.setString("000");
	this->hitpointsValue.setFont(FontManager::getInstance().joystick);
	this->hitpointsValue.setCharacterSize(22);
	this->hitpointsValue.setLetterSpacing(3.25);
	this->hitpointsValue.setFillColor(sf::Color::Black);


	this->mana.setString("MANA");
	this->mana.setFont(FontManager::getInstance().joystick);
	this->mana.setCharacterSize(22);
	this->mana.setOutlineThickness(1.5f);
	this->mana.setLetterSpacing(1.5f);
	this->mana.setFillColor(sf::Color::White);
	this->mana.setOutlineColor(sf::Color::Black);

	this->manaValue.setString("000");
	this->manaValue.setFont(FontManager::getInstance().joystick);
	this->manaValue.setCharacterSize(22);
	this->manaValue.setLetterSpacing(3.25);
	this->manaValue.setFillColor(sf::Color::Black);

	float width = this->battleTextbox.getGlobalBounds().width;
	sf::FloatRect textRect = this->name.getLocalBounds();
	this->name.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	this->name.setPosition(sf::Vector2f(this->battleTextbox.getGlobalBounds().width / 2.0f, this->getPosition().y + 27.0f));

	this->hitpoints.setPosition(sf::Vector2f(20.0f, 50.0f));
	this->hitpointsValue.setPosition(sf::Vector2f(122.0f, 50.0f));
	this->mana.setPosition(sf::Vector2f(20.0f, 93.0f));
	this->manaValue.setPosition(sf::Vector2f(122.0f, 93.0f));

	// Scale by height.
	float scale = 40.0f / this->playerSprite.getGlobalBounds().height;
	this->spriteScale = scale;
	this->playerSprite.setScale(scale, scale);
	this->playerSprite.setPosition((width / 2) - (this->playerSprite.getGlobalBounds().width / 2), -(this->playerSprite.getGlobalBounds().height / 2));
}

void PlayerCombatDisplay::update(float deltaTime) {
	if (this->isActive) {
		this->timeElapsed += deltaTime;
		if (up) {
			if (this->timeElapsed <= 0.20f) {
				this->playerSprite.move(0.0f, -deltaTime * 24.0f);
			} else {
				this->timeElapsed = 0.0f;
				this->up = false;
			}
		} else {
			if (this->timeElapsed <= 0.20f) {
				this->playerSprite.move(0.0f, deltaTime * 24.0f);
			} else {
				this->timeElapsed = 0.0f;
				this->up = true;
			}
		}
	}
}

void PlayerCombatDisplay::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = NULL;
	target.draw(this->battleTextbox, states);
	target.draw(this->name, states);
	target.draw(this->hitpoints, states);
	target.draw(this->hitpointsValue, states);
	target.draw(this->mana, states);
	target.draw(this->manaValue, states);
	target.draw(this->playerSprite, states);
}

float PlayerCombatDisplay::getWidth() {
	return this->battleTextbox.getGlobalBounds().width;
}

void PlayerCombatDisplay::setActive(bool active) {
	this->playerSprite.setPosition(this->playerSprite.getPosition().x, -(this->playerSprite.getGlobalBounds().height / 2));
	this->isActive = active;
}

void PlayerCombatDisplay::setCombatComponent(CombatComponent c) {
	this->combatComponent = c;
}

void PlayerCombatDisplay::setHealthComponent(HealthComponent& c) {
	this->health = c;
	if (c.hitpoints >= 100) {
		this->hitpointsValue.setString(std::to_string(c.hitpoints));
	} else if (c.hitpoints >= 10) {
		this->hitpointsValue.setString("0" + std::to_string(c.hitpoints));
	} else {
		this->hitpointsValue.setString("00" + std::to_string(c.hitpoints));
	}
}

void PlayerCombatDisplay::forceUpdate() {
	entt::registry& registry = GameDataManager::getInstance().getRegistry();
	auto view = registry.view<BaseComponent, RenderComponent, CombatComponent, HealthComponent, MovesetComponent>();
	for (auto entity : view) {
		auto& combatC = view.get<CombatComponent>(entity);
		auto& healthC = view.get<HealthComponent>(entity);
		if (combatC.combatId == this->combatComponent.combatId) {
			this->setHealthComponent(healthC);
			break;
		}
	}
}

CombatComponent& PlayerCombatDisplay::getCombatComponent() {
	return this->combatComponent;
}