#pragma once

#include "EntityComponentSystem.h"

#ifndef GAME_DATA_MANAGER_H
#define GAME_DATA_MANAGER_H

class GameDataManager {
public:
	GameDataManager& getInstance();
	entt::registry& getRegistry();
private:
	GameDataManager();

	entt::registry registry;
};

#endif