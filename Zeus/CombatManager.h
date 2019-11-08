#pragma once

#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>

#include "GameDataManager.h"
#include "Components.h"

#ifndef GAME_COMBAT_MANAGER_H
#define GAME_COMBAT_MANAGER_H

using json = nlohmann::json;

struct Character {
	std::string name;
	std::string spriteSheet;
};

class CombatManager {
public:
	static CombatManager& getInstance();
	void loadEntities(const std::string& fileLoc);
	void initialize();
private:
	CombatManager();
	std::vector<Character*> characterList;
};

#endif