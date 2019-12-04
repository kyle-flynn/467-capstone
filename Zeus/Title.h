#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

#include "FontManager.h"


class Title {
public:
	Title();
		
	void setFont(sf::Font& fonts);

	void setCharSize(int size);

	void setTextColor(sf::Color color);

	void setBackColor(sf::Color color);

	void setBorderColor(sf::Color color);

	void setBorderSize(float size);

	void setTitle(std::string newString);

	void setBoxSize(sf::Vector2f size);

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
	sf::Color bgColor;

	sf::Font font;
	std::string newString;

	int boxWidth;
	int boxHeight;
};