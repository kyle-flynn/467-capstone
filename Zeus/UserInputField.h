#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

#include "FontManager.h"

// Define keys:
#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class Textbox {
public:
	Textbox();

	void setFont(sf::Font& fonts);

	void setBackColor(sf::Color color);

	void setBorderSize(float size);

	void setBoxSize(sf::Vector2f size);

	void setPosition(sf::Vector2f point);

	void setLimit(bool ToF);

	void setLimit(bool ToF, int lim);

	void setSelected(bool sel);

	std::string getText() {
		return text.str();
	}

	void drawTo(sf::RenderWindow& window);

	void typedOn(sf::Event input);

private:
	sf::RectangleShape box;
	sf::Text textbox;

	std::ostringstream text;
	bool isSelected = false;
	bool hasLimit = false;
	int limit = 0;

	int charSize;
	sf::Vector2f boxSize;
	sf::Color textColor;
	sf::Color borderColor;
	sf::Color bgColor;
	bool sel = true;

	void deleteLastChar();
	void inputLogic(int charTyped);

	int boxWidth;
	int boxHeight;
};