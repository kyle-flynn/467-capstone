#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>


class Pic {
public:
	Pic(sf::Image image) {
		
		//box.setSize(boxSize);

		// Get these for later use:
		//boxWidth = boxSize.x;
		//boxHeight = boxSize.y;
	}
	/*
	void setImage(sf::Texture& images) {
		box.create(images);
	}

	void setPosition(sf::Vector2f point) {
		//box.setPosition(point);
	}
	
	void setImage(sf::Image& images) {
		box.setTexture(images);
	}

	void drawTo(sf::RenderWindow& window) {
		window.draw(box);
	}
	*/


private:
	sf::Texture box;

	//int boxWidth;
	//int boxHeight;
};