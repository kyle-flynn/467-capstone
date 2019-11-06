#include "CombatManager.h"

CombatManager::CombatManager() {}

CombatManager& CombatManager::getInstance() {
	static CombatManager instance;
	return instance;
}