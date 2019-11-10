#pragma once

#include <SFML/Graphics.hpp>
#include "Character.h"
#include "FontManager.h"

class CharacterOption :public sf::Drawable, public sf::Transformable {

public:

	bool isSelected;
	Character c;

	CharacterOption();
	CharacterOption(Character c);
	void setSelected(bool select);
	void setPressed(bool press);
	void update(float deltaTime, sf::Vector2i mousePosition);
	void update(sf::Event event, sf::Vector2i mousePosition);
	sf::String getName();
	sf::String getDescription();
	sf::Sprite getIcon();
	sf::Sprite getAvatar();

private:

	bool isPressed;
	const int TEXT_SIZE = 32;
	sf::Text cName, playable;
	sf::Sprite icon, avatar;

	void updateValues();
	virtual void draw(sf::RenderTarget&, sf::RenderStates states) const;
};

