#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

#include "FontManager.h"


class Title {
public:
	Title();
		//sf::Vector2f getSize();

		// Make sure font is passed by reference:
	void setFont(sf::Font& fonts);

	void setBackColor(sf::Color color);

	void setBorderSize(float size);

	void setPosition(sf::Vector2f point);

	void drawTo(sf::RenderWindow& window);

private:
	sf::RectangleShape box;
	sf::Text title;

	sf::Vector2f boxSize;
	std::string titleText;
	int charSize;
	sf::Color textColor;
	sf::Color borderColor;

	sf::Font font;

	int boxWidth;
	int boxHeight;
};