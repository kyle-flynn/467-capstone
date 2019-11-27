#include "DemoScreen.h"

#include <iostream>

DemoScreen::DemoScreen() {
	Screen();
}

void DemoScreen::update(float deltaTime) {
	Player::getInstance().update(deltaTime, mousePosition);
}

void DemoScreen::update(sf::Event event) {
	Player::getInstance().update(event, mousePosition);
	if (event.type == sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Button::Left) {
		std::cout << mousePosition.x << " " << mousePosition.y << std::endl;
	}
}

void DemoScreen::draw(sf::RenderWindow& window) {
	mousePosition = sf::Mouse::getPosition(window);
	Player::getInstance().draw(window);
}

void DemoScreen::handleEvent(sf::Event event) {
	update(event);
}

