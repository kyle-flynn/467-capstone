#pragma once

#include <SFML/Graphics.hpp>
#include "DialogueEditorScreen.h"
#include "Dialogue.h"

class DialogueEditorOptionNode : public sf::Drawable, public sf::Transformable {
	
public:

	const sf::Vector2f RECT_SIZE = sf::Vector2f(200.0f, 120.0f);
	bool isSelected;

	DialogueEditorOptionNode(Dialogue::optionNode* node);
	void setSelected(bool select);
	void setPressed(bool press);
	void update(float deltaTime, sf::Vector2i mousePosition);
	void update(sf::Event event, sf::Vector2i mousePosition);
	void edit(std::string message, int returnCode);
	Dialogue::optionNode* getNode();

private:

	bool isPressed;
	const int FONT_SIZE = 20;
	sf::Vector2f previousLoc;
	sf::RectangleShape rectangle;
	Dialogue::optionNode* node;
	sf::Text text, returnCode, nodeID;

	virtual void draw(sf::RenderTarget&, sf::RenderStates states) const;

};

