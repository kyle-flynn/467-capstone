#include "BattleTextbox.h"
#include "Game.h"

BattleTextbox::BattleTextbox() {
	this->textboxTexture.loadFromFile("Resources/Sprites/battle_text.png");
	this->textboxSprite.setTexture(this->textboxTexture);
	this->textboxSprite.setScale(3.0f, 3.0f);
	float diff = Game::WIDTH - this->textboxSprite.getGlobalBounds().width;
	this->textboxSprite.setPosition(diff / 2, 0.0f);
}

void BattleTextbox::update(float deltaTime) {

}

void BattleTextbox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = NULL;

	target.draw(this->textboxSprite, states);
}