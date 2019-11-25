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
	//void update(float deltaTime);
	//void update(sf::Event event);
	void draw(sf::RenderWindow& window);
	//void handleEvent(sf::Event event);
	//void changeActive();

	int* shptr;
	//World* world;
	

private:
	//sf::Vector2i mousePosition;

	Title t1;
	Textbox text1;
	Button btn1;

	//void drawActive(sf::RenderWindow& window);
};

#endif