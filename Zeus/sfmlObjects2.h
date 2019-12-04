//#pragma once

#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "ScreenManager.h"

#include <iostream>
#include "sfmlObjects.h"
//#include "DynamicText.h"

//#ifndef GAME_GAMEPLAY_SFMLOBJECTS2_H
//#define GAME_GAMEPLAY_SFMLOBJECTS2_H


class SFML_Objects2 {
public:
	SFML_Objects2();

	void stage2Objects(int* enteredNum);

	int s2EventLogic(sf::Event event, sf::RenderWindow& window, int** tileVals, int* enteredNum);

	void readyToType(int stageNum);

	void drawTo(int stageNum, sf::RenderWindow& window);

private:
	int enteredNum2 = 1;
	//int* shptr2; // = &enteredNum2;

	int count = 0;
	int* counter = &count;

	int rVal = 0;
	int cVal = 0;
	int* rowVal = &rVal;
	int* colVal = &cVal;

	sf::Texture image1;
	sf::Sprite sprite1;

	Title t2;
	DynText d1, d2;
	Textbox text2;
	Button btn2;

};

//#endif