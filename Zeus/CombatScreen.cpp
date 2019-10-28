#include "CombatScreen.h"

CombatScreen::CombatScreen() :
	combatDisplay(std::string("Kyle")),
	textbox()
{
	this->combatDisplay.setPosition(0.0f, 592.0f);
}

void CombatScreen::update(float deltaTime) {

}

void CombatScreen::draw(sf::RenderWindow& window) {
	window.draw(this->combatDisplay);
	window.draw(this->textbox);
}