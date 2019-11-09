#include "BattleTextbox.h"
#include "Game.h"
#include "FontManager.h"

BattleTextbox::BattleTextbox() :
combatTextbox(sf::Quads, 12)
{
	this->textboxTexture.loadFromFile("Resources/Sprites/spritesheet_combat.png");
	this->textboxSprite.setTexture(this->textboxTexture);
	this->textboxSprite.setScale(3.0f, 3.0f);
	float diff = Game::WIDTH - this->textboxSprite.getGlobalBounds().width;
	this->textboxSprite.setPosition(diff / 2, 0.0f);

	this->battleText.setFont(FontManager::getInstance().joystick);
	this->battleText.setPosition(this->textboxSprite.getPosition().x + 10.0f, this->textboxSprite.getPosition().y + 5.0f);
	this->battleText.setFillColor(sf::Color::Black);

	this->appendText("Test text.");
	this->initVertices();
}

void BattleTextbox::initVertices() {
	float topPadding = 15.0f;
	float sidePadding = 30.0f;
	float outsideWidth = 90.0f;
	float innerWidth = Game::WIDTH - (2 * outsideWidth) - (2 * sidePadding);
	float height = 90.0f;

	this->drawSquare(this->combatTextbox, 0, sidePadding, topPadding, outsideWidth, height);
	this->drawSquare(this->combatTextbox, 4, sidePadding + outsideWidth, topPadding, innerWidth, height);
	this->drawSquare(this->combatTextbox, 8, sidePadding + outsideWidth + innerWidth, topPadding, outsideWidth, height);

	this->assignTexCoords(this->combatTextbox, 0, 0.0f, 0.0f, 30.0f, 30.0f);
	this->assignTexCoords(this->combatTextbox, 4, 30.0f, 0.0f, 30.0f, 30.0f);
	this->assignTexCoords(this->combatTextbox, 8, 60.0f, 0.0f, 30.0f, 30.0f);
}

void BattleTextbox::drawSquare(sf::VertexArray& vertices, size_t index, float x, float y, float width, float height) {
	vertices[index].position = sf::Vector2f(x, y);
	vertices[index + 1].position = sf::Vector2f(x + width, y);
	vertices[index + 2].position = sf::Vector2f(x + width, y + height);
	vertices[index + 3].position = sf::Vector2f(x, y + height);
}

void BattleTextbox::assignTexCoords(sf::VertexArray& vertices, size_t index, float x, float y, float width, float height) {
	vertices[index].texCoords = sf::Vector2f(x, y);
	vertices[index + 1].texCoords = sf::Vector2f(x + width, y);
	vertices[index + 2].texCoords = sf::Vector2f(x + width, y + height);
	vertices[index + 3].texCoords = sf::Vector2f(x, y + height);
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
	states.texture = &this->textboxTexture;

	// target.draw(this->textboxSprite, states);
	// target.draw(this->battleText, states);
	target.draw(this->combatTextbox, states);
}