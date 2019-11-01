#pragma once

#include <SFML/Graphics.hpp>
#include "Dialogue.h"
#include "FontManager.h"

class DialogueEditorMessageNode : public sf::Drawable, public sf::Transformable {

public:

	bool isSelected;

	DialogueEditorMessageNode(Dialogue::msgNode* node);
	void setSelected(bool select);
	void setPressed(bool press);
	void update(float delaTime, sf::Vector2i mousePosition);
	void update(sf::Event event, sf::Vector2i mousePosition);
	void edit(std::string message);
	Dialogue::msgNode* getNode();

private:

	bool isPressed;
	const int FONT_SIZE = 20;
	const sf::Vector2f RECT_SIZE = sf::Vector2f(200.0f, 120.0f);
	Dialogue::msgNode* node;
	sf::Text text, nodeID;
	sf::RectangleShape rectangle;

	virtual void draw(sf::RenderTarget&, sf::RenderStates states) const;

};