#include "GameDataManager.h"

GameDataManager::GameDataManager() {}

GameDataManager& GameDataManager::getInstance() {
	static GameDataManager instance;
	return instance;
}

entt::registry& GameDataManager::getRegistry() {
	return this->registry;
}

std::vector<Item> GameDataManager::getItems() {
	return this->items;
}

void GameDataManager::saveItems(std::vector<ItemOption*> items) {
	for (ItemOption* i : items) {
		this->items.push_back(i->item);
	}
}

//std::vector<Character> GameDataManager::getCharacters() {
//	return this->characters;
//}
//
//void GameDataManager::saveCharacters(std::vector<CharacterOption*> characters) {
//	for (CharacterOption* c : characters) {
//		this->characters.push_back(c->c);
//	}
//}

std::vector<Dialogue*> GameDataManager::getDialogueTrees() {
	return dialogueTrees;
}

void GameDataManager::saveDialogueTrees(std::vector<Dialogue*> trees) {
	for (Dialogue* t : trees) {
		this->dialogueTrees.push_back(t);
	}
}

void GameDataManager::loadAssets() {
	loadItems();
	loadCharacters();
	loadDialogueTrees();
}

void GameDataManager::loadItems() {

}

void GameDataManager::loadCharacters() {
}

void GameDataManager::loadDialogueTrees() {
}