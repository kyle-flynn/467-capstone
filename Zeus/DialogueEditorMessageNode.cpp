#include "DialogueEditorMessageNode.h"

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
	if (press) {
		this->previousLoc = this->getNode()->loc;
	}
	else if (dynamic_cast<DialogueEditorScreen&>(ScreenManager::getInstance().getScreen()).optionOverlap(this->getNode())) {
		this->getNode()->loc = this->previousLoc;
	}
}

void DialogueEditorMessageNode::update(float deltaTime, sf::Vector2i mousePosition) {
	sf::Rect<float> bounds(
		this->getPosition().x,
		this->getPosition().y,
		this->rectangle.getGlobalBounds().width,
		this->rectangle.getGlobalBounds().height);
	if (this->isPressed) {
		this->getNode()->loc = sf::Vector2f(mousePosition.x, mousePosition.y);
	}
}

void DialogueEditorMessageNode::update(sf::Event event, sf::Vector2i mousePosition) {
	sf::Rect<float> bounds(
		this->getPosition().x,
		this->getPosition().y,
		this->rectangle.getGlobalBounds().width,
		this->rectangle.getGlobalBounds().height);
	if (event.type == sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Button::Left &&
		bounds.contains(mousePosition.x, mousePosition.y)) {
		this->setPressed(true);
		this->setSelected(true);
	}
	else if (this->isPressed && event.type == sf::Event::MouseButtonReleased &&
		event.mouseButton.button == sf::Mouse::Button::Left) {
		this->setPressed(false);
	}
	else if (event.type == sf::Event::MouseButtonReleased &&
		event.mouseButton.button == sf::Mouse::Button::Left &&
		!bounds.contains(mousePosition.x, mousePosition.y)) {
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