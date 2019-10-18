#include "DialogueEditorMessageNode.h"
#include "FontManager.h"

DialogueEditorMessageNode::DialogueEditorMessageNode(Dialogue::msgNode* node) {
	sf::Font font = FontManager::getInstance().oldStandard;
	this->node = node;
	this->text.setString(node->message);
	this->text.setFont(font);
	this->text.setCharacterSize(FONT_SIZE);
	this->nodeID.setString(std::to_string(node->nodeID));
	this->nodeID.setFont(font);
	this->nodeID.setCharacterSize(FONT_SIZE);
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
	target.draw(this->text, states);
}

Dialogue::msgNode* DialogueEditorMessageNode::getNode() {
	return this->node;
}