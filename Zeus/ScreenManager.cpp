#include "ScreenManager.h"

ScreenManager::ScreenManager() {
	this->screen = nullptr;
}

ScreenManager& ScreenManager::getInstance() {
	static ScreenManager instance;
	return instance;
}

void ScreenManager::draw(sf::Window& window) {
	if (this->screen != nullptr) {
		this->screen->draw(window);
	}
}

void ScreenManager::setScreen(Screen* screen) {
	this->screen = screen;
}

Screen& ScreenManager::getScreen() {
	return *this->screen;
}