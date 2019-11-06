#include "GameDataManager.h"

GameDataManager::GameDataManager() {}

entt::registry& GameDataManager::getRegistry() {
	return this->registry;
}