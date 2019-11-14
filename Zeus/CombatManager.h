#pragma once

#include <algorithm>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>

#include "GameDataManager.h"
#include "Components.h"

#include <iostream>

#ifndef GAME_COMBAT_MANAGER_H
#define GAME_COMBAT_MANAGER_H

using json = nlohmann::json;

class CombatManager {
public:
	static CombatManager& getInstance();
	void loadEntities(const std::string& fileLoc);
	void initialize();
	void processPlayerAction(Action& a);
	void determineTurnOrder();
	int getCombatId();
	bool takeTurn();
	bool hasTurnReady();
private:
	CombatManager();
	std::vector<CombatComponent> combatants;
	int combatTurn;
	bool turnReady;
};

#endif