#pragma once

#include <SFML/Graphics.hpp>

#include "Screen.h"

#ifndef GAME_SCREEN_MANAGER_H
#define GAME_SCREEN_MANAGER_H

class ScreenManager {
public:
	static ScreenManager& getInstance();
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	void setScreen(Screen* screen);
	Screen& getScreen();
private:
	ScreenManager();
	Screen* screen;
};

#endif