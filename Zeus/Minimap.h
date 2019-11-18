#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>

#ifndef GAME_MINIMAP_H
#define GAME_MINIMAP_H

class Minimap {

private:
	sf::Texture pixelsheet;
	std::vector<sf::Sprite> sprites;
	Minimap(int userInput);
	//int tileWidth;
	//int tileHeight;
};

#endif // !GAME_MINIMAP_H