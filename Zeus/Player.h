#pragma once

#include "Character.h"
#include "GameDataManager.h"
#include "InventoryMenu.h"
#include "PlayerMenu.h"
#include "QuestMenu.h"
#include "Components.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player {

public:

	std::string name;
	std::vector<Character*> characters;
	PlayerMenu pMenu;
	InventoryMenu inventoryMenu;
	QuestMenu questJournal;

	static Player& getInstance();
	void update(float deltaTime, sf::Vector2i mousePosition);
	void update(sf::Event event, sf::Vector2i mousePosition);
	void draw(sf::RenderWindow& window);

private:

	Player();
	int pID;
	Character* activeCharacter;

};

#endif