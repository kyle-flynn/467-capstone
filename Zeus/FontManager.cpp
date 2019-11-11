#include "FontManager.h"

FontManager::FontManager() {}

FontManager& FontManager::getInstance() {
	static FontManager instance;
	return instance;
}

void FontManager::loadFonts() {
	this->oldStandard.loadFromFile("Resources/Fonts/OldStandard/OldStandardTT-Regular.ttf");
	this->joystick.loadFromFile("Resources/Fonts/blocked/joystix.ttf");
}