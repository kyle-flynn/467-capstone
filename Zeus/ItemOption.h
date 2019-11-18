#pragma once

#include <SFML/Graphics.hpp>
#include "Item.h"
#include "FontManager.h"

class ItemOption : public sf::Drawable, public sf::Transformable {

public:

	bool isSelected;
	Item item;

	ItemOption();
	ItemOption(Item item);
	void setSelected(bool select);
	void setPressed(bool press);
	void update(float deltaTime, sf::Vector2i mousePosition);
	void update(sf::Event event, sf::Vector2i mousePosition);
	sf::String getName();
	sf::String getType();
	sf::String getDescription();
	sf::Sprite getIcon();

private:

	bool isPressed;
	const int TEXT_SIZE = 32;
	sf::Text itemName, itemType;
	sf::Sprite sprite;

	void updateValues();
	sf::String typeToString(type type);
	virtual void draw(sf::RenderTarget&, sf::RenderStates states) const;

};
