#include "World.h"

World::World(const std::string& filename, int tiles[4][4], int tileWidth, int tileHeight) {
	if (!this->tilesheet.loadFromFile(filename)) {
		throw std::exception("Error loading tilesheet. File not found.");
	}
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			sf::Sprite sprite;
			float sheetTilesX = this->tilesheet.getSize().x / tileWidth;
			float sheetTilesY = this->tilesheet.getSize().y / tileHeight;
			float tileX = std::floor(tiles[j][i] / sheetTilesX) + tiles[j][i];
			float tileY = std::floor(tiles[j][i] / sheetTilesY);
			sprite.setTexture(this->tilesheet);
			sprite.setTextureRect(sf::IntRect(tileX * tileWidth, tileY * tileHeight, tileWidth, tileHeight));
			sprite.setPosition((i * tileWidth) + tileWidth, (j * tileHeight) + tileHeight);
			this->sprites.push_back(sprite);
		}
	}
}

void World::draw(sf::RenderWindow& window) {
	for (sf::Sprite sprite : this->sprites) {
		window.draw(sprite);
	}
}