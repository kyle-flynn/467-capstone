#pragma once

#include <SFML/Graphics.hpp>

#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

class Screen {
public:
	Screen();
	virtual void draw(sf::RenderWindow& window);
};

#endif