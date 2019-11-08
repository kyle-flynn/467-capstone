#include "CombatScreen.h"

#include "CombatManager.h"

CombatScreen::CombatScreen() :
	combatDisplay(std::string("Kyle")),
	textbox()
{
	this->combatDisplay.setPosition(0.0f, 592.0f);
	CombatManager::getInstance().loadEntities("Resources/test_characters.json");
}

void CombatScreen::update(float deltaTime) {

}

void CombatScreen::draw(sf::RenderWindow& window) {
	window.draw(this->combatDisplay);
	window.draw(this->textbox);
}