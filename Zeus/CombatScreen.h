#pragma once

#include <string>

#include "Screen.h"

#include "PlayerCombatDisplay.h"

#ifndef GAME_COMBAT_SCREEN_H
#define GAME_COMBAT_SCREEN_H

class CombatScreen : public Screen {
public:
	CombatScreen();
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
private:
	PlayerCombatDisplay combatDisplay;
};

#endif