#include "GameplayScreen.h"
#include "ScreenManager.h"
#include "MainMenuScreen.h"


#include <iostream>

GameplayScreen::GameplayScreen() {
	Screen();

	this->stageNum = &defaultStage;

	//this->world = new World(std::string("Resources/Tiles/tileset_grass.png"), tiles, 16, 16);
}

int GameplayScreen::eventLogic(sf::Event event, sf::RenderWindow& window) {

	sfmlObj.readyToType(*stageNum);

	switch (*stageNum) {
	case 1:
		*stageNum = sfmlObj.s1EventLogic(event, window);
		break;
	case 2:
		*stageNum = sfmlObj.s2EventLogic(event, window);
		break;
	case 3:
		*stageNum = sfmlObj.s3EventLogic(event, window);
		break;
	}

	return *stageNum;
}

void GameplayScreen::draw(int stageNum, sf::RenderWindow& window) {
	sfmlObj.drawTo(stageNum, window);

	//this->world->draw(window);
}