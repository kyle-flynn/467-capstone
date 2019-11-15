#pragma once

#include <algorithm>
#include <fstream>
#include <vector>
#include <random>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>

#include "GameDataManager.h"
#include "Components.h"
#include "BattleTextbox.h"

#ifndef GAME_COMBAT_MANAGER_H
#define GAME_COMBAT_MANAGER_H

using json = nlohmann::json;

class CombatManager {
public:
	static CombatManager& getInstance();
	void loadEntities(const std::string& fileLoc);
	void initialize();
	void processPlayerAction(Action& a);
	void processEnemyAction();
	void determineTurnOrder();
	void setBattleTextbox(BattleTextbox* textbox);
	int getCombatId();
	bool takeTurn();
	bool hasTurnReady();
	bool isBattleFinished();
	bool checkForEnemyTurn();
private:
	CombatManager();
	std::vector<CombatComponent> combatants;
	int combatTurn;
	bool turnReady;
	bool battleFinished;
	BattleTextbox* textbox;
	bool calculateDamage(Move m, entt::entity& entity);
};

#endif