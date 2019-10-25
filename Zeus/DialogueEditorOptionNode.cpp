#include "DialogueEditorOptionNode.h"
#include "FontManager.h"

DialogueEditorOptionNode::DialogueEditorOptionNode(Dialogue::optionNode* node) {
	this->node = node;
	this->rectangle.setSize(RECT_SIZE);
	//this->rectangle.setFillColor(sf::Color::Transparent);
	this->text.setFont(FontManager::getInstance().oldStandard);
	this->text.setCharacterSize(FONT_SIZE);
	this->text.setFillColor(sf::Color::Black);
	this->text.setString("Message: " + sf::String(node->optionMsg));
	this->text.setPosition(sf::Vector2f(5.0f, 0.0f));
	this->returnCode.setFont(FontManager::getInstance().oldStandard);
	this->returnCode.setCharacterSize(FONT_SIZE);
	this->returnCode.setFillColor(sf::Color::Black);
	this->returnCode.setString("Return Code: " + std::to_string(node->returnCode));
	this->returnCode.setPosition(sf::Vector2f(5.0f, 95.0f));
	this->nodeID.setFont(FontManager::getInstance().oldStandard);
	this->nodeID.setCharacterSize(FONT_SIZE);
	this->nodeID.setFillColor(sf::Color::Black);
	this->nodeID.setString("NodeID: " + sf::String(std::to_string(node->nodeID)));
	this->isSelected = false;
}

void DialogueEditorOptionNode::setSelected(bool select) {
	this->isSelected = select;
	this->rectangle.setFillColor(select ? sf::Color::Blue : sf::Color::White);
}

void DialogueEditorOptionNode::update(float deltaTime, sf::Vector2i mousePosition) {
	sf::Rect<float> bounds(
		this->getPosition().x,
		this->getPosition().y,
		this->rectangle.getGlobalBounds().width,
		this->rectangle.getGlobalBounds().height);
	if (bounds.contains(mousePosition.x, mousePosition.y)) {
		this->setSelected(true);
	}
	else {
		this->setSelected(false);
	}
}

void DialogueEditorOptionNode::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = NULL;
	target.draw(this->rectangle, states);
	target.draw(this->text, states);
	target.draw(this->returnCode, states);
}

Dialogue::optionNode* DialogueEditorOptionNode::getNode() {
	return this->node;
}