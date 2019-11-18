#pragma once

#include "Character.h"
#include "GameDataManager.h"
#include "InventoryMenu.h"

class Player {

public:

	std::string name;
	std::vector<Character> characters;

	Player();

private:

	int pID;
	std::vector<Character> activeCharacters;
	InventoryMenu inventory;
	QuestMenu questJournal;

};

