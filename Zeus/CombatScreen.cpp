#include "CombatScreen.h"

CombatScreen::CombatScreen() :
	combatDisplay(std::string("Kyle"))
{}

void CombatScreen::update(float deltaTime) {

}

void CombatScreen::draw(sf::RenderWindow& window) {
	window.draw(this->combatDisplay);
}