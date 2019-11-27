//#pragma once

#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "ScreenManager.h"

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

	void changeWindow(int stageNum, sf::RenderWindow& window);

	int* createArray(int** tileVals, int** temp);

	int s1EventLogic(sf::Event event, sf::RenderWindow& window, int** tileVals, int** temp);

	void readyToType(int stageNum);

	void drawTo(int stageNum, sf::RenderWindow& window);

private:
	int enteredNum = 0;
	int* shptr = &enteredNum;


	Title t1;
	Textbox text1;
	Button btn1;

	//Title t1, t2;
	//DynText d1, d2;
	//Textbox text1, text2;
	//Button btn1, btn2;
};

//#endif