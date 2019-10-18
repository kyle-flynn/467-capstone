#include "DialogueEditorOptionNode.h"
#include "FontManager.h"

DialogueEditorOptionNode::DialogueEditorOptionNode(Dialogue::optionNode* node) {
	sf::Font font = FontManager::getInstance().oldStandard;
	this->rectangle.setSize(sf::Vector2f(120.0f, 50.0f));
	this->rectangle.setFillColor(sf::Color::White);
	this->text.setString(node->optionMsg);
	this->text.setFont(font);
	this->text.setCharacterSize(FONT_SIZE);
	this->returnCode.setString(std::to_string(node->returnCode));
	this->returnCode.setFont(font);
	this->returnCode.setCharacterSize(FONT_SIZE);
	this->nodeID.setString(std::to_string(node->nodeID));
	this->nodeID.setFont(font);
	this->nodeID.setCharacterSize(FONT_SIZE);
	this->isSelected = false;
}

void DialogueEditorOptionNode::setSelected(bool select) {
	this->isSelected = select;
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
}

Dialogue::optionNode* DialogueEditorOptionNode::getNode() {
	return this->node;
}