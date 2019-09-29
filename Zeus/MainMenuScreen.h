#pragma once

#include "Screen.h"

#ifndef GAME_MAIN_MENU_SCREEN_H
#define GAME_MAIN_MENU_SCREEN_H

class MainMenuScreen : public Screen {
public:
	MainMenuScreen();
	void draw(sf::RenderWindow& window);
};

#endif;