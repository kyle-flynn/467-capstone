#pragma once

#include <SFML/Graphics.hpp>
#include "Dialogue.h"

class DialogueEditorOptionNode : public sf::Drawable, public sf::Transformable {
	
public:

	DialogueEditorOptionNode(Dialogue::optionNode* node);
	void setSelected(bool select);
	void update(float deltaTime, sf::Vector2i mousePosition);
	Dialogue::optionNode* getNode();

private:

	const int FONT_SIZE = 10;
	sf::RectangleShape rectangle;
	Dialogue::optionNode* node;
	sf::Text text, returnCode, nodeID;
	bool isSelected;
	virtual void draw(sf::RenderTarget&, sf::RenderStates states) const;

};

