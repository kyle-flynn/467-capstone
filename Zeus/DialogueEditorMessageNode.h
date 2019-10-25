#pragma once

#include <SFML/Graphics.hpp>
#include "Dialogue.h"

class DialogueEditorMessageNode : public sf::Drawable, public sf::Transformable {

public:

	bool isSelected;

	DialogueEditorMessageNode(Dialogue::msgNode* node);
	void setSelected(bool select);
	void update(float delaTime, sf::Vector2i mousePosition);
	Dialogue::msgNode* getNode();

private:

	const int FONT_SIZE = 20;
	const sf::Vector2f RECT_SIZE = sf::Vector2f(200.0f, 120.0f);
	Dialogue::msgNode* node;
	sf::Text text, nodeID;
	sf::RectangleShape rectangle;

	virtual void draw(sf::RenderTarget&, sf::RenderStates states) const;

};