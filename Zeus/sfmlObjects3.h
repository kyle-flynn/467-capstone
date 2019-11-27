//#pragma once

#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "ScreenManager.h"

#include "World.h"

#include <iostream>

//#ifndef GAME_GAMEPLAY_SFMLOBJECTS3_H
//#define GAME_GAMEPLAY_SFMLOBJECTS3_H


class SFML_Objects3 {
public:
	SFML_Objects3();

	SFML_Objects3(int** tileVals, int* enteredNum);

	int s3EventLogic(sf::Event event, sf::RenderWindow& window, int** tileVals, int enteredNum);

	void drawTo(int stageNum, sf::RenderWindow& window);

private:
	int dummy1 = 1;
	int* help1 = &dummy1;
	int** def1 = &help1;
	int dummy2 = 2;
	int* def2 = &dummy2;

	World* world;
};

//#endif