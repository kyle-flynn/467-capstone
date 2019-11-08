#include "GameDataManager.h"

GameDataManager::GameDataManager() {}

GameDataManager& GameDataManager::getInstance() {
	static GameDataManager instance;
	return instance;
}

entt::registry& GameDataManager::getRegistry() {
	return this->registry;
}