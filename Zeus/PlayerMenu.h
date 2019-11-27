#pragma once

#include <SFML/Graphics.hpp>
#include "FontManager.h"
#include "Character.h"
//#include "Player.h"

#ifndef PLAYER_MENU_H
#define PLAYER_MENU_H

class PlayerMenu : public sf::Drawable, public sf::Transformable {

public:

	bool visible;

	PlayerMenu();
	void setVisible(bool vis);
	void update(float deltaTime, sf::Vector2i mousePosition);
	void update(sf::Event event, sf::Vector2i mousePosition);
	void addCharacter(Character* character);
	void removeCharacter();
	void updateActive(Character* character);

private:

	int charIt;
	Character* activeChar;
	std::vector<Character*> characters;
	const int TEXT_SIZE = 32, ICON_SIZE = 100;
	sf::RectangleShape charStat, chars, menuOptions;
	std::vector<sf::Text> statDescriptors;
	sf::Text stats, charHeader;

	virtual void draw(sf::RenderTarget&, sf::RenderStates states) const;
};

#endif