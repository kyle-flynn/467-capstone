#pragma once

#include "EntityComponentSystem.h"

#ifndef GAME_COMBAT_MANAGER_H
#define GAME_COMBAT_MANAGER_H

class CombatManager {
public:
	static CombatManager& getInstance();
private:
	CombatManager();
	void reset();
};

#endif