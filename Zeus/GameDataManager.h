#pragma once

#include "EntityComponentSystem.h"
#include "CharacterEditorScreen.h"
#include "ItemEditorScreen.h"
#include "DialogueEditorScreen.h"
#include "MonsterEditorScreen.h"
#include "MonsterOption.h"
#include <nlohmann/json.hpp>

#ifndef GAME_DATA_MANAGER_H
#define GAME_DATA_MANAGER_H

class GameDataManager {
public:

	Item nullItem;

	static GameDataManager& getInstance();
	entt::registry& getRegistry();
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
	void loadItems();
	void loadCharacters();
	void loadDialogueTrees();
	void loadMonsters();
	void saveItems();
	void saveCharacters();
	void saveDialogueTrees();
	void saveMonsters();

	entt::registry registry;
	std::vector<Item> items;
	std::vector<Character> characters;
	std::vector<Dialogue*> dialogueTrees;
	std::vector<Monster> monsters;

};

#endif