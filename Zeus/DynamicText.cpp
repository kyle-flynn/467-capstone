#include "DynamicText.h"

DynText::DynText() {
	userNum = 0;
	boxSize = { 100, 50 };
	//displayText = "Enter a Number for Map Size";
	charSize = 25;
	textColor = sf::Color::White;
	borderColor = sf::Color::Black;
	bgColor = sf::Color::Black;

	boxWidth = boxSize.x;
	boxHeight = boxSize.y;

	box.setSize(boxSize);
	box.setOutlineColor(borderColor);
	box.setFillColor(bgColor);

	textbox.setFont(FontManager::getInstance().oldStandard);

	std::string numStr = std::to_string(userNum);
	textbox.setString(numStr + "x" + numStr);
	textbox.setCharacterSize(charSize);
	textbox.setFillColor(textColor);
}

void DynText::setFont(sf::Font& fonts) {
	textbox.setFont(fonts);
}

void DynText::setCharSize(int size) {
	textbox.setCharacterSize(size);
}

void DynText::setTextColor(sf::Color color) {
	textbox.setFillColor(color);
}

void DynText::setBackColor(sf::Color color) {
	box.setFillColor(color);
}

void DynText::setBorderColor(sf::Color color) {
	box.setOutlineColor(color);
}

void DynText::setBorderSize(float size) {
	box.setOutlineThickness(size);
}

void DynText::setTextNum(int userNum) {
	std::string numStr = std::to_string(userNum);
	textbox.setString(numStr + "x" + numStr);
}

void DynText::setBoxSize(sf::Vector2f size) {
	box.setSize(size);
	boxWidth = size.x;
	boxHeight = size.y;
}

void DynText::setPosition(sf::Vector2f point) {
	box.setPosition(point);

	// Center text in box:
	float xPos = (point.x + boxWidth / 2) - (textbox.getLocalBounds().width / 2);
	float yPos = (point.y + boxHeight / 2.2) - (textbox.getLocalBounds().height / 2);
	textbox.setPosition(xPos, yPos);
}

void DynText::drawTo(sf::RenderWindow& window) {
	window.draw(box);
	window.draw(textbox);
}