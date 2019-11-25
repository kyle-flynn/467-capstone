#include "Title.h"

Title::Title() {
	boxSize = { 700, 100 };
	titleText = "Enter a Number for Map Size";
	charSize = 30;
	textColor = sf::Color::Yellow;
	borderColor = sf::Color::Red;

	//if (!font.loadFromFile("arial.ttf"))
		//std::cout << "Font not found!\n";
	
	box.setSize(boxSize);
	box.setOutlineColor(borderColor);

	//box.setPosition(point);

	boxWidth = boxSize.x;
	boxHeight = boxSize.y;

	title.setFont(FontManager::getInstance().oldStandard);
	title.setString(titleText);
	title.setCharacterSize(charSize);
	title.setFillColor(textColor);
	
}

void Title::setFont(sf::Font& fonts) {
	title.setFont(fonts);
}

void Title::setBackColor(sf::Color color) {
	box.setFillColor(color);
}

void Title::setBorderSize(float size) {
	box.setOutlineThickness(size);
}

void Title::setPosition(sf::Vector2f point) {
	box.setPosition(point);

	// Center text on button:
	float xPos = (point.x + boxWidth / 2) - (title.getLocalBounds().width / 2);
	float yPos = (point.y + boxHeight / 2.2) - (title.getLocalBounds().height / 2);
	title.setPosition(xPos, yPos);
}

void Title::drawTo(sf::RenderWindow& window) {
	window.draw(box);
	window.draw(title);
}