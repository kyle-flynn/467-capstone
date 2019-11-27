#include "Screen.h"
#include "ScreenManager.h"
#include "MainMenuScreen.h"
#include <SFML/Graphics.hpp>

#include <iostream>
//#include "sfmlObjects.h"
#include "sfmlObjects2.h"
#include "sfmlObjects3.h"

//#ifndef GAME_GAMEPLAY_SCREEN_H
//#define GAME_GAMEPLAY_SCREEN_H

class GameplayScreen : public Screen {
public:
	GameplayScreen();

	int** createArray(int** tileVals, int* temp);

	int eventLogic(sf::Event event, sf::RenderWindow& window);

	void draw(int stageNum, sf::RenderWindow& window);

private:
	int defaultStage = 1;
	int* stageNum;
	int defaultInput = 1;
	int* defaultHelp1 = &defaultInput;
	int** temp = &defaultHelp1;
	int defaultTile = 2;
	int* defaultHelp2 = &defaultTile;
	int** tileVals = &defaultHelp2;

	int** p2a;

	SFML_Objects sfmlObj;
	SFML_Objects2 sfmlObj2;
	SFML_Objects3 sfmlObj3;
	//SFML_Objects3 sfmlObj3(tileVals, temp);
};

//#endif