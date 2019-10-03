#include "GameplayScreen.h"

GameplayScreen::GameplayScreen() : Screen() {
	int tiles[4][4] = {
		{6,6,6,6},
		{10,0,0,0},
		{10,0,0,0},
		{10,0,0,0}
	};
	this->world = new World(std::string("Resources/Tiles/tileset_grass.png"), tiles, 16, 16);
}


void GameplayScreen::update(float deltaTime) {
	
}

void GameplayScreen::draw(sf::RenderWindow& window) {
	this->world->draw(window);
}