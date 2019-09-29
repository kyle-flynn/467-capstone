#include "World.h"

World::World(const std::string& filename, int tiles[4][4], int tileWidth, int tileHeight) {
	/* loadFromFile returns a boolean to describe if the load succeeded or not. Throw an error if it does not.
	   Whenever we make a world constructor, we should probably surround it in a try/catch block.
	*/
	if (!this->tilesheet.loadFromFile(filename)) {
		throw std::exception("Error loading tilesheet. File not found.");
	}
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;

	// This is set for static dimensions, a 4x4 tile grid. This can be changed, or made dynamic based upon world parameters.
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			sf::Sprite sprite;
			// This divides the texture sheet into tiles.
			float sheetTilesX = this->tilesheet.getSize().x / tileWidth + 0.0f;
			float sheetTilesY = this->tilesheet.getSize().y / tileHeight + 0.0f;

			float tileX = std::floor(tiles[j][i] / sheetTilesX) + tiles[j][i];
			float tileY = std::floor(tiles[j][i] / sheetTilesY);

			sprite.setTexture(this->tilesheet);
			sprite.setTextureRect(sf::IntRect(tileX * tileWidth + 0.0f, tileY * tileHeight + 0.0f, tileWidth + 0.0f, tileHeight + 0.0f));
			sprite.setPosition((i * tileWidth) + tileWidth + 0.0f, (j * tileHeight) + tileHeight + 0.0f);
			this->sprites.push_back(sprite);
		}
	}
}

void World::draw(sf::RenderWindow& window) {
	for (sf::Sprite sprite : this->sprites) {
		window.draw(sprite);
	}
}