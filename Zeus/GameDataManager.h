#pragma once

#include "EntityComponentSystem.h"
#include "Components.h"
#include "Item.h"
#include "ItemOption.h"
//#include "Character.h"
//#include "CharacterOption.h"
#include "DialogueEditorScreen.h"
#include "Dialogue.h"

#ifndef GAME_DATA_MANAGER_H
#define GAME_DATA_MANAGER_H

class GameDataManager {
public:

	static GameDataManager& getInstance();
	entt::registry& getRegistry();
	std::vector<Item> getItems();
	void saveItems(std::vector<ItemOption*> items);
	//std::vector<Character> getCharacters();
	//void saveCharacters(std::vector<CharacterOption*> characters);
	std::vector<Dialogue*> getDialogueTrees();
	void saveDialogueTrees(std::vector<Dialogue*> trees);

private:

	GameDataManager();
	void loadAssets();
	void loadItems();
	void loadCharacters();
	void loadDialogueTrees();

	entt::registry registry;
	std::vector<Item> items;
	//std::vector<Character> characters;
	std::vector<Dialogue*> dialogueTrees;

};

#endif