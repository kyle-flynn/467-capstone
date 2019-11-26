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
	
	//void stage1Objects();

	void stage2Objects();

	void stage2Objects(int enteredNum);

	void changeWindow(int stageNum, sf::RenderWindow& window);

	void createArray(int enteredNum);

	int s1EventLogic(sf::Event event, sf::RenderWindow& window);

	int s2EventLogic(sf::Event event, sf::RenderWindow& window);

	void readyToType(int stageNum);

	void drawTo(int stageNum, sf::RenderWindow& window);


private:
	//int defaultStage = 1;
	//int* stageNum;

	int enteredNum = 0;
	int* shptr;

	int** tileVals;

	sf::Texture image1;
	sf::Sprite sprite1;

	Title t1, t2;
	DynText d1, d2;
	Textbox text1, text2;
	Button btn1, btn2;
};

//#endif