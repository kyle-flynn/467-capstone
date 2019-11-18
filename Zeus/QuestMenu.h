#pragma once

#include <SFML/Graphics.hpp>

#include "Player.h"

class QuestMenu : public sf::Drawable, public sf::Transformable {

public:

	bool visible;

	QuestMenu();
	void setVisible(bool vis);
	void update(float deltaTime, sf::Vector2i mousePosition);
	void update(sf::Event event, sf::Vector2i mousePosition);

private:

	int listIt;
	sf::Texture BGTexture;
	sf::Sprite BGSprite;
	const int TEXT_SIZE = 32;

	virtual void draw(sf::RenderTarget&, sf::RenderStates states) const;
};

