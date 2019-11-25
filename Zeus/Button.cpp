#include "Button.h"

Button::Button() {

	charSize = 20;
	buttonSize = { 150, 30 };
	bgColor = sf::Color::Green;
	textColor = sf::Color::Black;
	btnText = "Enter";

	text.setFont(FontManager::getInstance().oldStandard);
	text.setCharacterSize(charSize);
	text.setString(btnText);
	text.setFillColor(textColor);

	button.setSize(buttonSize);
	button.setFillColor(bgColor);

	btnWidth = buttonSize.x;
	btnHeight = buttonSize.y;

}


void Button::setFont(sf::Font& fonts) {
	text.setFont(fonts);
}

void Button::setBackColor(sf::Color color) {
	button.setFillColor(color);
}

void Button::setTextColor(sf::Color color) {
	text.setFillColor(color);
}

void Button::setPosition(sf::Vector2f point) {
	button.setPosition(point);

	// Center text on button:
	float xPos = (point.x + btnWidth / 2) - (text.getLocalBounds().width / 2);
	float yPos = (point.y + btnHeight / 2.2) - (text.getLocalBounds().height / 2);
	text.setPosition(xPos, yPos);
}

// Change selected state:
void Button::drawTo(sf::RenderWindow& window) {
	window.draw(button);
	window.draw(text);
}

// Check if the mouse is within the bounds of the button:
bool Button::isMouseOver(sf::RenderWindow& window) {
	int mouseX = sf::Mouse::getPosition(window).x;
	int mouseY = sf::Mouse::getPosition(window).y;

	int btnPosX = button.getPosition().x;
	int btnPosY = button.getPosition().y;

	int btnxPosWidth = button.getPosition().x + btnWidth;
	int btnyPosHeight = button.getPosition().y + btnHeight;

	if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {
		return true;
	}
	return false;
}

