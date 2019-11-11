#include "GameplayScreen.h"

GameplayScreen::GameplayScreen() : Screen() {
	// Texture Sheet dimensions are 12x21 (value range: 0-251)

	// Empty Values for texture sheet: 
	// 8, 67, 80, 92, 
	// 104-106, 116, 190, 196, 
	// 202, 208-214, 220-227, 231-239, 243-251
	int tiles[4][4] = {
		{54,55,56,20},
		{66,198,68,44},
		{78,79,80,228},
		{48,49,50,240}
	};
	this->world = new World(std::string("Resources/Tiles/tileset_grass.png"), tiles, 16, 16);
}

void GameplayScreen::draw(sf::RenderWindow& window) {
	this->world->draw(window);
}