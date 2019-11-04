#include "BattleTextbox.h"
#include "Game.h"
#include "FontManager.h"

BattleTextbox::BattleTextbox() {
	this->textboxTexture.loadFromFile("Resources/Sprites/battle_text.png");
	this->textboxSprite.setTexture(this->textboxTexture);
	this->textboxSprite.setScale(3.0f, 3.0f);
	float diff = Game::WIDTH - this->textboxSprite.getGlobalBounds().width;
	this->textboxSprite.setPosition(diff / 2, 0.0f);

	this->battleText.setFont(FontManager::getInstance().joystick);
	this->battleText.setPosition(this->textboxSprite.getPosition().x + 10.0f, this->textboxSprite.getPosition().y + 5.0f);
	this->battleText.setFillColor(sf::Color::Black);

	this->appendText("Lucas is feeling ill... Lucas takes 10hp of damage!");
}

void BattleTextbox::update(float deltaTime) {

}

void BattleTextbox::appendText(const std::string& text) {
	this->battleText.setString(text);
	this->checkForNewlines(text);
}

void BattleTextbox::checkForNewlines(const std::string& text) {
	for (int i = 0; i < this->battleText.getString().getSize(); i++) {
		float x = this->battleText.findCharacterPos(i).x;
		float maxWidth = this->textboxSprite.getGlobalBounds().width - this->battleText.getCharacterSize();
		if (x > maxWidth) {
			std::string newString = std::string(text).insert(i, "-\n");
			if (text[i] == ' ') {
				newString = newString.replace(i + 2, 1, "");
			}
			this->battleText.setString(newString);
			break;
			// this->checkForNewlines(newString);
		}
	}
}

void BattleTextbox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = NULL;

	target.draw(this->textboxSprite, states);
	target.draw(this->battleText, states);
}