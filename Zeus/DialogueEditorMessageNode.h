#pragma once

#include <SFML/Graphics.hpp>
#include "Dialogue.h"

class DialogueEditorMessageNode : public sf::Drawable, public sf::Transformable {

public:

	DialogueEditorMessageNode(Dialogue::msgNode* node);
	void setSelected(bool select);
	void update(float delaTime, sf::Vector2i mousePosition);
	Dialogue::msgNode* getNode();

private:

	const int FONT_SIZE = 10;
	Dialogue::msgNode* node;
	sf::Text text, nodeID;
	bool isSelected;

	virtual void draw(sf::RenderTarget&, sf::RenderStates states) const;

};