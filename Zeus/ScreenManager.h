#pragma once

#include <SFML/Window.hpp>

#include "Screen.h"

#ifndef GAME_SCREEN_MANAGER_H
#define GAME_SCREEN_MANAGER_H

class ScreenManager {
public:
	static ScreenManager& getInstance();
	void draw(sf::Window& window);
	void setScreen(Screen* screen);
	Screen& getScreen();
private:
	ScreenManager();
	Screen* screen;
};

#endif