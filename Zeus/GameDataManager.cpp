#include "GameDataManager.h"

GameDataManager::GameDataManager() {
	loadAssets();
}

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

std::vector<Quest> GameDataManager::getQuests() {
	return this->quests;
}

void GameDataManager::addQuests(std::vector<ItemOption*> questss) {
	for (ItemOption* i : quests) {
		this->quests.push_back(i->quest);
	}
	saveItems();
}

void GameDataManager::addItems(std::vector<ItemOption*> items) {
	for (ItemOption* i : items) {
		this->items.push_back(i->item);
	}
	saveItems();
}

std::vector<Character> GameDataManager::getCharacters() {
	return this->characters;
}

void GameDataManager::addCharacters(std::vector<CharacterOption*> characters) {
	for (CharacterOption* c : characters) {
		this->characters.push_back(c->c);
	}
	saveCharacters();
}

std::vector<Dialogue*> GameDataManager::getDialogueTrees() {
	return dialogueTrees;
}

void GameDataManager::addDialogueTrees(std::vector<Dialogue*> trees) {
	for (Dialogue* t : trees) {
		this->dialogueTrees.push_back(t);
	}
	saveDialogueTrees();
}

std::vector<Monster> GameDataManager::getMonsters() {
	return monsters;
}

void GameDataManager::addMonsters(std::vector<MonsterOption*> monsters) {
	for (MonsterOption* m : monsters) {
		this->monsters.push_back(m->m);
	}
	saveMonsters();
}

void GameDataManager::loadAssets() {
	loadQuests();
	loadItems();
	loadCharacters();
	loadDialogueTrees();
	loadMonsters();
}

void GameDataManager::loadItems() {
	std::ifstream ifs("quest.json");
	nlohmann::json j;
	Quest quest;
	ifs >> j;
	for (int i = 0; i < j.size(); i++) {
		quest.name = j[i].at("name").get<std::string>();
		quest.questType = (Quest::type)(j[i].at("type").get<int>());
		quest.description = j[i].at("description").get<std::string>();
		quest.reward = j[i].at("reward").get<std::string>();
		quests.push_back(quest);
	}
	ifs.close();
}

void GameDataManager::loadItems() {
	std::ifstream ifs("items.json");
	nlohmann::json j;
	Item item;
	ifs >> j;
	for (int i = 0; i < j.size(); i++) {
		item.name = j[i].at("name").get<std::string>();
		item.itemType = (Item::type)(j[i].at("type").get<int>());
		item.stat = j[i].at("stat").get<int>();
		item.description = j[i].at("description").get<std::string>();
		items.push_back(item);
	}
	ifs.close();
}

void GameDataManager::loadCharacters() {
	std::ifstream ifs("characters.json");
	nlohmann::json j;
	Character character;
	ifs >> j;
	for (int i = 0; i < j.size(); i++) {
		character.name = j[i].at("name").get<std::string>();
		character.maxHP = j[i].at("hp").get<double>();
		character.maxMana = j[i].at("mana").get<double>();
		character.maxStamina = j[i].at("stamina").get<double>();
		character.description = j[i].at("description").get<std::string>();
		character.playable = j[i].at("playable").get<bool>();
		characters.push_back(character);
	}
	ifs.close();
}

void GameDataManager::loadDialogueTrees() {
}

void GameDataManager::loadMonsters() {
	std::ifstream ifs("monsters.json");
	nlohmann::json j;
	Monster m;
	ifs >> j;
	for (int i = 0; i < j.size(); i++) {
		m.name = j[i].at("name").get<std::string>();
		m.maxHP = j[i].at("hp").get<double>();
		m.mType = (Monster::type)(j[i].at("type").get<int>());
		m.description = j[i].at("description").get<std::string>();
		monsters.push_back(m);
	}
	ifs.close();
}
void GameDataManager::saveItems() {
	nlohmann::json j = nlohmann::json::array();
	std::ofstream o("quests.json");
	int it = 0;
	for (Item i : quests) {
		j[it]["name"] = i.name;
		j[it]["type"] = i.questType;
		j[it]["reward"] = i.reward;
		j[it]["description"] = i.description;
		it++;
	}
	o << std::setw(4) << j << std::endl;
	o.close();
}


void GameDataManager::saveItems() {
	nlohmann::json j = nlohmann::json::array();
	std::ofstream o("items.json");
	int it = 0;
	for (Item i : items) {
		j[it]["name"] = i.name;
		j[it]["type"] = i.itemType;
		j[it]["stat"] = i.stat;
		j[it]["description"] = i.description;
		it++;
	}
	o << std::setw(4) << j << std::endl;
	o.close();
}

void GameDataManager::saveCharacters() {
	nlohmann::json j = nlohmann::json::array();
	std::ofstream o("characters.json");
	int it = 0;
	for (Character c : characters) {
		j[it]["name"] = c.name;
		j[it]["hp"] = c.maxHP;
		j[it]["mana"] = c.maxMana;
		j[it]["stamina"] = c.maxStamina;
		j[it]["description"] = c.description;
		j[it]["playable"] = c.playable;
		it++;
	}
	o.clear();
	o << std::setw(4) << j << std::endl;
	o.close();
}

void GameDataManager::saveDialogueTrees() {
}

void GameDataManager::saveMonsters() {
	nlohmann::json j = nlohmann::json::array();
	std::ofstream o("monsters.json");
	int it = 0;
	for (Monster m : monsters) {
		j[it]["name"] = m.name;
		j[it]["type"] = m.mType;
		j[it]["hp"] = m.maxHP;
		j[it]["description"] = m.description;
	}
	o << std::setw(4) << j << std::endl;
	o.close();
}