#pragma once

#include <SFML/Graphics.hpp>

#ifndef GAME_BATTLE_TEXTBOX_H
#define GAME_BATTLE_TEXTBOX_H

class BattleTextbox : public sf::Drawable, sf::Transformable {
public:
	BattleTextbox();
	void update(float deltaTime);
	void appendText(const std::string& text);
private:
	sf::Texture textboxTexture;
	sf::Sprite textboxSprite;
	sf::Text battleText;
	sf::VertexArray combatTextbox;

	void checkForNewlines(const std::string& text);
	void initVertices();
	void drawSquare(sf::VertexArray& vertices, size_t index, float x, float y, float width, float height);
	void assignTexCoords(sf::VertexArray& vertices, size_t index, float x, float y, float width, float height);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif