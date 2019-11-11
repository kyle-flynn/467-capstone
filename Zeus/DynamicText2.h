#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>


class DynText2 {
public:
	DynText2(int charSize, sf::Vector2f boxSize, sf::Color textColor, sf::Color borderColor) {
		textbox.setCharacterSize(charSize);
		textbox.setFillColor(textColor);

		box.setSize(boxSize);
		box.setOutlineColor(borderColor);

		//std::string rowStr = std::to_string(row);
		//std::string colStr = std::to_string(col);
		//textbox.setString("For Tile:   [ " + rowStr + " , " + colStr + " ]");

	}

	void setString(int row, int col) {
		std::string rowStr = std::to_string(row);
		std::string colStr = std::to_string(col);
		textbox.setString("For Tile:   [ " + rowStr + " , " + colStr + " ]");
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