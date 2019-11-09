#pragma once

#include <string>
#include <vector>

#include "Game.h"
#include "Screen.h"
#include "GameDataManager.h"
#include "PlayerCombatDisplay.h"
#include "BattleTextbox.h"

#ifndef GAME_COMBAT_SCREEN_H
#define GAME_COMBAT_SCREEN_H

class CombatScreen : public Screen {
public:
	CombatScreen();
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
private:
	std::vector<PlayerCombatDisplay*> combatDisplays;
	std::vector<entt::entity*> enemies;
	BattleTextbox textbox;
};

#endif