#pragma once
//#include "Screen.h"
#include <SFML/Graphics.hpp>

#include <iostream>
#include "UserInputField.h"
#include "Button.h"
#include "Title.h"
#include "DynamicText.h"

//#ifndef GAME_GAMEPLAY_SFMLOBJECTS_H
//#define GAME_GAMEPLAY_SFMLOBJECTS_H


class SFML_Objects {
public:
	SFML_Objects();

	void stage2Objects(int enteredNum);

	void stage2ObjectsInLoop(int enteredNum);

	void changeWindow(int stageNum, sf::RenderWindow& window);

	void createArray(int enteredNum);

	int s1EventLogic(sf::Event event, sf::RenderWindow& window);

	int s2EventLogic(sf::Event event, sf::RenderWindow& window);

	int s3EventLogic(sf::Event event, sf::RenderWindow& window);

	void readyToType(int stageNum);

	void drawTo(int stageNum, sf::RenderWindow& window);


private:
	int enteredNum = 0;
	int* shptr = &enteredNum;

	int enteredNum2 = 0;
	int* shptr2 = &enteredNum2;

	int count = 0;
	int* counter = &count;

	int rVal;
	int cVal;
	int* rowVal = &rVal;
	int* colVal = &cVal;

	int** tileVals;

	sf::Texture image1;
	sf::Sprite sprite1;

	Title t1, t2;
	DynText d1, d2;
	Textbox text1, text2;
	Button btn1, btn2;
};

//#endif