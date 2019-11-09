#pragma once

#include <SFML/Graphics.hpp>
#include "FontManager.h"

class EditorText : public sf::Drawable, public sf::Transformable {

public:

	bool isSelected;

	EditorText();
	EditorText(sf::String string);
	void setSelected(bool select);
	void setPressed(bool press);
	void update(float deltaTime, sf::Vector2i mousePosition);
	void update(sf::Event event, sf::Vector2i mousePosition);
	sf::String getDefault();
	void setDefault(sf::String string);
	sf::String getText();
	void setText(sf::String string);
	void setEditable(bool edit);
	void setNumeric(bool num);
	sf::Vector2f getSize();

private:

	bool isPressed, editable, numeric;
	const int TEXT_SIZE = 20;
	sf::Text defaultText, editText;
	
	virtual void draw(sf::RenderTarget&, sf::RenderStates states) const;
};

