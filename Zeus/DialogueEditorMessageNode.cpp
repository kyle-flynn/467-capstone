#include "DialogueEditorMessageNode.h"
#include "FontManager.h"
#include <iostream>

DialogueEditorMessageNode::DialogueEditorMessageNode(Dialogue::msgNode* node) {
	this->node = node;
	this->rectangle.setSize(RECT_SIZE);
	//this->rectangle.setFillColor(sf::Color::Transparent);
	this->text.setFont(FontManager::getInstance().oldStandard);
	this->text.setCharacterSize(FONT_SIZE);
	this->text.setFillColor(sf::Color::Black);
	this->text.setString(sf::String(node->message));
	this->text.setPosition(sf::Vector2f(5.0f, 0.0f));
	this->nodeID.setFont(FontManager::getInstance().oldStandard);
	this->nodeID.setCharacterSize(FONT_SIZE);
	this->nodeID.setFillColor(sf::Color::Black);
	this->nodeID.setString(sf::String(std::to_string(node->nodeID)));
	this->isSelected = false;
	this->isPressed = false;
}

void DialogueEditorMessageNode::setSelected(bool select) {
	this->isSelected = select;
}

void DialogueEditorMessageNode::setPressed(bool press) {
	this->isPressed = press;
}

void DialogueEditorMessageNode::update(float deltaTime, sf::Vector2i mousePosition) {
	sf::Rect<float> bounds(
		this->getPosition().x,
		this->getPosition().y,
		this->rectangle.getGlobalBounds().width,
		this->rectangle.getGlobalBounds().height);
	if (this->isPressed && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		this->getNode()->loc = sf::Vector2f(mousePosition.x, mousePosition.y);
	}
	else if (bounds.contains(mousePosition.x, mousePosition.y) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		this->setSelected(true);
		this->setPressed(true);
	}
	else {
		this->setSelected(false);
		this->setPressed(false);
	}
}

void DialogueEditorMessageNode::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = NULL;
	target.draw(this->rectangle, states);
	target.draw(this->text, states);
}

void DialogueEditorMessageNode::edit(std::string message) {
	this->text.setString(sf::String(message));
	this->node->message = message;
}

Dialogue::msgNode* DialogueEditorMessageNode::getNode() {
	return this->node;
}