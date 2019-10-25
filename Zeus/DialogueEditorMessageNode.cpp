#include "DialogueEditorMessageNode.h"
#include "FontManager.h"

DialogueEditorMessageNode::DialogueEditorMessageNode(Dialogue::msgNode* node) {
	//sf::Font font = FontManager::getInstance().oldStandard;
	this->node = node;
	this->rectangle.setSize(RECT_SIZE);
	//this->rectangle.setFillColor(sf::Color::Transparent);
	this->text.setFont(FontManager::getInstance().oldStandard);
	this->text.setCharacterSize(FONT_SIZE);
	this->text.setFillColor(sf::Color::Black);
	this->text.setString("Message: " + sf::String(node->message));
	this->text.setPosition(sf::Vector2f(5.0f, 0.0f));
	this->nodeID.setFont(FontManager::getInstance().oldStandard);
	this->nodeID.setCharacterSize(FONT_SIZE);
	this->nodeID.setFillColor(sf::Color::Black);
	this->nodeID.setString("NodeID: " + sf::String(std::to_string(node->nodeID)));
	this->isSelected = false;
}

void DialogueEditorMessageNode::setSelected(bool select) {
	this->isSelected = select;
}

void DialogueEditorMessageNode::update(float deltaTime, sf::Vector2i mousePosition) {
	sf::Rect<float> bounds(
		this->getPosition().x,
		this->getPosition().y,
		this->text.getGlobalBounds().width,
		this->text.getGlobalBounds().height);
	if (bounds.contains(mousePosition.x, mousePosition.y)) {
		this->setSelected(true);
	}
	else {
		this->setSelected(false);
	}
}

void DialogueEditorMessageNode::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = NULL;
	target.draw(this->rectangle, states);
	target.draw(this->text, states);
}

Dialogue::msgNode* DialogueEditorMessageNode::getNode() {
	return this->node;
}