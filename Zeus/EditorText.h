#pragma once

#include <SFML/Graphics.hpp>
#include <iomanip>
#include <sstream>
#include "FontManager.h"

class EditorText : public sf::Drawable, public sf::Transformable {

public:

	bool isSelected;

	EditorText(float maxSize = 0.0f);
	EditorText(sf::String string, float maxSize = 0.0f);
	void setSelected(bool select);
	void setPressed(bool press);
	void update(float deltaTime, sf::Vector2i mousePosition);
	void update(sf::Event event, sf::Vector2i mousePosition);
	sf::String getDefault();
	void setDefault(sf::String string);
	sf::String getText();
	void setText(sf::String string);
	void setColor(sf::Color color);
	void setEditable(bool edit);
	void setNumeric(bool num);
	sf::Vector2f getSize();

private:

	sf::Color color = sf::Color::Black;
	bool isPressed, editable, numeric, numFlag;
	const int TEXT_SIZE = 20;
	float maxSize = 0.0f;
	sf::String defaultText, inputText;
	sf::Text text;
	
	void textWrap();
	virtual void draw(sf::RenderTarget&, sf::RenderStates states) const;
};

