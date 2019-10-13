#pragma once

#include <SFML/Graphics.hpp>

#ifndef GAME_FONT_MANAGER_H
#define GAME_FONT_MANAGER_H

class FontManager {
public:
	static FontManager& getInstance();
	void loadFonts();

	sf::Font oldStandard;
private:
	FontManager();
};

#endif