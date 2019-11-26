#pragma once

#include "Screen.h"
#include <SFML/Graphics.hpp>
//#include "World.h"

#include <iostream>
#include "EditorText.h"

#include "sfmlObjects.h"

#ifndef GAME_GAMEPLAY_SCREEN_H
#define GAME_GAMEPLAY_SCREEN_H

class GameplayScreen : public Screen {
public:
	GameplayScreen();

	int eventLogic(sf::Event event, sf::RenderWindow& window);

	void draw(int stageNum, sf::RenderWindow& window);
	
	//World* world;
	

private:
	int defaultStage = 1;
	int* stageNum;

	SFML_Objects sfmlObj;

	//void drawActive(sf::RenderWindow& window);
};

#endif