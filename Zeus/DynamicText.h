#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

#include "FontManager.h"

class DynText {
public:
	DynText();

	void setFont(sf::Font& fonts);

	void setCharSize(int size);

	void setTextColor(sf::Color color);

	void setBackColor(sf::Color color);

	void setBorderColor(sf::Color color);

	void setBorderSize(float size);

	void setTextNum(int userNum);

	void setBoxSize(sf::Vector2f size);

	void setPosition(sf::Vector2f point);

	void drawTo(sf::RenderWindow& window);


private:
	sf::RectangleShape box;
	sf::Text textbox;

	//std::string displayText;
	int userNum;
	int charSize;
	sf::Vector2f boxSize;
	sf::Color textColor;
	sf::Color borderColor;
	sf::Color bgColor;
	std::string newString;

	int boxWidth;
	int boxHeight;
};