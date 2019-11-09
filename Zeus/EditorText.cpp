#include "EditorText.h"

#include <iostream>

EditorText::EditorText() {
	defaultText.setFont(FontManager::getInstance().oldStandard);
	editText.setFont(FontManager::getInstance().oldStandard);
	defaultText.setCharacterSize(TEXT_SIZE);
	editText.setCharacterSize(TEXT_SIZE);
	defaultText.setFillColor(sf::Color::Black);
	editText.setFillColor(sf::Color::Black);
	defaultText.setString(sf::String("DEFAULT TEXT: "));
	editText.setString(sf::String("DEFAULT TEXT"));
	editText.setPosition(defaultText.getPosition().x + defaultText.getLocalBounds().width + 20,
		defaultText.getPosition().y);
	isSelected = false;
	isPressed = false;
	editable = true;
}

EditorText::EditorText(sf::String string) {
	defaultText.setFont(FontManager::getInstance().oldStandard);
	editText.setFont(FontManager::getInstance().oldStandard);
	defaultText.setCharacterSize(TEXT_SIZE);
	editText.setCharacterSize(TEXT_SIZE);
	defaultText.setFillColor(sf::Color::Black);
	editText.setFillColor(sf::Color::Black);
	defaultText.setString(string);
	editText.setString(sf::String("DEFAULT TEXT"));
	editText.setPosition(defaultText.getPosition().x + defaultText.getLocalBounds().width + 20,
		defaultText.getPosition().y);
	isSelected = false;
	isPressed = false;
	editable = true;
}

void EditorText::setSelected(bool select) {
	isSelected = select;
	editText.setFillColor(select ? sf::Color::Blue : sf::Color::Black);
}

void EditorText::setPressed(bool press) {
	isPressed = press;
}

void EditorText::update(float deltaTime, sf::Vector2i mousePosition) {
	sf::Rect<float> bounds(
		getPosition().x,
		getPosition().y,
		defaultText.getGlobalBounds().width + editText.getGlobalBounds().width + 20,
		defaultText.getGlobalBounds().height);
	if (bounds.contains(mousePosition.x, mousePosition.y)) {
		setSelected(true);
	}
	else {
		setSelected(false);
	}
}

void EditorText::update(sf::Event event, sf::Vector2i mousePosition) {
	sf::Rect<float> bounds(
		getPosition().x,
		getPosition().y,
		defaultText.getGlobalBounds().width + editText.getGlobalBounds().width + 20,
		defaultText.getGlobalBounds().height);
	if (event.type == sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Button::Left) {
		if (bounds.contains(mousePosition.x, mousePosition.y)) {
			setPressed(true);
		}
		else {
			setPressed(false);
		}
	}
	else if (event.type == sf::Event::TextEntered && isPressed && editable) {
		std::cout << event.text.unicode << std::endl;
		if (event.text.unicode == 8) {
			editText.setString(editText.getString().substring(0, editText.getString().getSize() - 1));
		}
		else {
			editText.setString(editText.getString() + sf::String(event.text.unicode));
		}
	}
}

sf::String EditorText::getDefault() {
	return defaultText.getString();
}

void EditorText::setDefault(sf::String string) {
	defaultText.setString(string);
}

sf::String EditorText::getText() {
	return editText.getString();
}

void EditorText::setText(sf::String string) {
	editText.setString(string);
}

void EditorText::setEditable(bool edit) {
	editable = edit;
}

sf::Vector2f EditorText::getSize() {
	return sf::Vector2f(defaultText.getGlobalBounds().width + editText.getGlobalBounds().width + 20,
		defaultText.getGlobalBounds().height);
}

void EditorText::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = NULL;
	target.draw(defaultText, states);
	target.draw(editText, states);
}