#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>


class Title {
public:
	Title(std::string titleText, sf::Vector2f boxSize, int charSize, sf::Color textColor, sf::Color borderColor) {
		//title.setSize(boxSize);
		box.setSize(boxSize);
		box.setOutlineColor(borderColor);

		// Get these for later use:
		boxWidth = boxSize.x;
		boxHeight = boxSize.y;

		title.setString(titleText);
		title.setCharacterSize(charSize);
		title.setFillColor(textColor);

	}

	// Make sure font is passed by reference:
	void setFont(sf::Font& fonts) {
		title.setFont(fonts);
	}

	void setBackColor(sf::Color color) {
		box.setFillColor(color);
	}

	void setBorderSize(float size) {
		box.setOutlineThickness(size);
	}

	void setPosition(sf::Vector2f point) {
		box.setPosition(point);

		// Center text on button:
		float xPos = (point.x + boxWidth / 2) - (title.getLocalBounds().width / 2);
		float yPos = (point.y + boxHeight / 2.2) - (title.getLocalBounds().height / 2);
		title.setPosition(xPos, yPos);
	}

	void drawTo(sf::RenderWindow& window) {
		window.draw(box);
		window.draw(title);
	}



private:
	sf::RectangleShape box;
	sf::Text title;

	int boxWidth;
	int boxHeight;
};