#include "ScreenManager.h"

ScreenManager::ScreenManager() {
	this->screen = nullptr;
}

ScreenManager& ScreenManager::getInstance() {
	static ScreenManager instance;
	return instance;
}

void ScreenManager::update(float deltaTime) {
	if (this->screen) {
		this->screen->update(deltaTime);
	}
}

void ScreenManager::draw(sf::RenderWindow& window) {
	if (this->screen) {
		this->screen->draw(window);
	}
}

void ScreenManager::handleEvent(sf::Event event) {
	if (this->screen) {
		this->screen->handleEvent(event);
	}
}

void ScreenManager::setScreen(Screen* screen) {
	this->screen = screen;
}

Screen& ScreenManager::getScreen() {
	return *this->screen;
}