#pragma once

#include <SFML/Window.hpp>

#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

class Screen {
public:
	Screen();
	void draw(sf::Window& window);
};

#endif