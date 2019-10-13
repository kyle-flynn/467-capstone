#pragma once

#include <SFML/Graphics.hpp>

#ifndef GAME_MENU_OPTION_H
#define GAME_MENU_OPTION_H

class MenuOption : public sf::Drawable, public sf::Transformable {
public:
	MenuOption(const std::string& text, bool isSelected);
	void setSelected(bool selected);
	void update(float deltaTime, sf::Vector2i mousePosition);
private:
	sf::Text text;
	bool isSelected;
	virtual void draw(sf::RenderTarget&, sf::RenderStates states) const;
};

#endif