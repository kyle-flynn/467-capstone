#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>


class DynText {
public:
	DynText(int userNum, int charSize, sf::Vector2f boxSize, sf::Color textColor, sf::Color borderColor) {
		textbox.setCharacterSize(charSize);
		textbox.setFillColor(textColor);

		box.setSize(boxSize);
		box.setOutlineColor(borderColor);

		std::string numStr = std::to_string(userNum);
		textbox.setString(numStr + "x" + numStr);

	}

	// Make sure font is passed by reference:
	void setFont(sf::Font& fonts) {
		textbox.setFont(fonts);
	}

	void setBackColor(sf::Color color) {
		box.setFillColor(color);
	}

	void setBorderSize(float size) {
		box.setOutlineThickness(size);
	}

	void setPosition(sf::Vector2f point) {
		textbox.setPosition(point);
		box.setPosition(point);
	}

	void drawTo(sf::RenderWindow& window) {
		window.draw(box);
		window.draw(textbox);
	}



private:
	sf::RectangleShape box;
	sf::Text textbox;

};