#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#ifndef GAME_TILESHEET_H
#define GAME_TILESHEET_H

class Tilesheet {
public:
	static int create(const std::string& filename, Tilesheet* tilesheet);
private:
	Tilesheet();
	sf::Texture tilesheet;
};

#endif // !GAME_TILESHEET_H
