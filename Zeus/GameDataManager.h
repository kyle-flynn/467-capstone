#pragma once

#include "EntityComponentSystem.h"
#include "CharacterEditorScreen.h"
#include "ItemEditorScreen.h"
//#include "QuestEditorScreen.h"
#include "Components.h"
#include "Item.h"
#include "ItemOption.h"
//#include "Quest.h"
//#include "QuestOption.h"
//#include "Character.h"
//#include "CharacterOption.h"
#include "DialogueEditorScreen.h"
#include "MonsterEditorScreen.h"
#include "MonsterOption.h"
#include <nlohmann/json.hpp>

#ifndef GAME_DATA_MANAGER_H
#define GAME_DATA_MANAGER_H

class GameDataManager {
public:

	static GameDataManager& getInstance();
	entt::registry& getRegistry();
	//std::vector<Item> getQuests();
	//void addQuests(std::vector<ItemOption*> quests);
	std::vector<Item> getItems();
	void addItems(std::vector<ItemOption*> items);
	std::vector<Character> getCharacters();
	void addCharacters(std::vector<CharacterOption*> characters);
	std::vector<Dialogue*> getDialogueTrees();
	void addDialogueTrees(std::vector<Dialogue*> trees);
	std::vector<Monster> getMonsters();
	void addMonsters(std::vector<MonsterOption*> monsters);

private:

	GameDataManager();
	void loadAssets();
	//void loadQuests();
	void loadItems();
	void loadCharacters();
	void loadDialogueTrees();
	void loadMonsters();
	void saveItems();
	//void saveQuests();
	void saveCharacters();
	void saveDialogueTrees();
	void saveMonsters();

	entt::registry registry;
	std::vector<Item> items;
	//std::vector<Item> quests;
	std::vector<Character> characters;
	std::vector<Dialogue*> dialogueTrees;
	std::vector<Monster> monsters;

};

#endif