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
	void checkForNewlines(const std::string& text);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif