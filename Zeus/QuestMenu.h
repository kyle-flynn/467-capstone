#pragma once

#include <SFML/Graphics.hpp>
#include "Character.h"
//#include "Player.h"

#ifndef QUEST_MENU_H
#define QUEST_MENU_H

class QuestMenu : public sf::Drawable, public sf::Transformable {

public:

	bool visible;

	QuestMenu();
	void setVisible(bool vis, Character* character);
	void update(float deltaTime, sf::Vector2i mousePosition);
	void update(sf::Event event, sf::Vector2i mousePosition);

private:

	Character* activeChar;
	int listIt;
	sf::Texture BGTexture;
	sf::Sprite BGSprite;
	const int TEXT_SIZE = 32;
	
	void loadQuests();
	virtual void draw(sf::RenderTarget&, sf::RenderStates states) const;
};

#endif