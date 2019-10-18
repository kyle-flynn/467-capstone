#include "FontManager.h"

FontManager::FontManager() {}

FontManager& FontManager::getInstance() {
	static FontManager instance;
	return instance;
}

void FontManager::loadFonts() {
	this->oldStandard.loadFromFile("Resources/Fonts/OldStandard/OldStandardTT-Regular.ttf");
	this->minecraft.loadFromFile("Resources/Fonts/Minecraftia/Minecraftia.ttf");
	this->blocked.loadFromFile("Resources/Fonts/blocked/Minecrafter_3.ttf");
}