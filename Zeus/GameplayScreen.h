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
	void specialKeyPressed(int key);
	void eventLogic(sf::Event event, sf::RenderWindow& window);
	void stage2Logic(int enteredNum);

	void draw(sf::RenderWindow& window);
	

	int* shptr;
	//World* world;
	

private:
	//sf::Vector2i mousePosition;

	sf::Texture image1;

	Title t1, t2;
	Textbox text1;
	Button btn1;

	//void drawActive(sf::RenderWindow& window);
};

#endif