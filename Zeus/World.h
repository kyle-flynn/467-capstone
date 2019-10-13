#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>
#include <cmath>
#include <iostream>

#ifndef GAME_WORLD_H
#define GAME_WORLD_H

class World {
public:
	World(const std::string& filename, int tiles[4][4], int tileWidth, int tileHeight);
	void draw(sf::RenderWindow& window);
private:
	sf::Texture tilesheet;
	std::vector<sf::Sprite> sprites;
	int tileWidth;
	int tileHeight;
};

#endif // !GAME_WORLD_H
