#pragma once

#include "Screen.h"
#include <SFML/Graphics.hpp>
//#include "World.h"
// new way
#include <iostream>
#include "UserInputField.h"
#include "Button.h"
#include "Title.h"
#include "DynamicText.h"
#include "DynamicText2.h"
#include "EditorText.h"

#ifndef GAME_GAMEPLAY_SCREEN_H
#define GAME_GAMEPLAY_SCREEN_H

class GameplayScreen : public Screen {
public:
	GameplayScreen();

	void changeWindow(int stageNum, sf::RenderWindow& window);

	void specialKeyPressed(int key);

	void stage1Logic(sf::Event event, sf::RenderWindow& window);

	void stage2Logic(int enteredNum);

	void draw(int stageNum, sf::RenderWindow& window);
	

	int* shptr;
	//World* world;
	

private:
	int defaultStage = 1;
	int* stageNum;

	//sf::Vector2u s2Window;
	//sf::Vector2u centerPoint;
	//sf::Vector2i newCenter;

	sf::Texture image1;
	sf::Sprite sprite1;

	Title t1, t2;
	DynText d1;
	Textbox text1;
	Button btn1;

	//void drawActive(sf::RenderWindow& window);
};

#endif