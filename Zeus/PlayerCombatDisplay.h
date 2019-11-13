#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "FontManager.h"
#include "Components.h"

#ifndef GAME_PLAYER_COMBAT_DISPLAY_H
#define GAME_PLAYER_COMBAT_DISPLAY_H

class PlayerCombatDisplay : public sf::Transformable, public sf::Drawable {
public:
	PlayerCombatDisplay(std::string name, sf::Sprite& playerSprite);
	float getWidth();
	void update(float deltaTime);
	void setActive(bool active);
	void setCombatComponent(CombatComponent c);
	CombatComponent& getCombatComponent();
private:
	sf::Texture combatDisplay;
	sf::Sprite battleTextbox;
	sf::Sprite& playerSprite;
	sf::Text name;
	sf::Text hitpoints;
	sf::Text mana;
	CombatComponent combatComponent;
	bool isActive;
	bool up;
	float timeElapsed;
	float spriteScale;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif