#include "EditorText.h"

#include <iostream>

EditorText::EditorText(float maxSize) {
	text.setFont(FontManager::getInstance().oldStandard);
	text.setCharacterSize(TEXT_SIZE);
	text.setFillColor(sf::Color::Black);
	text.setString("DEFAULT TEXT");
	isSelected = false;
	isPressed = false;
	editable = true;
	numeric = false;
	this->maxSize = maxSize;
}

EditorText::EditorText(sf::String string, float maxSize) {
	text.setFont(FontManager::getInstance().oldStandard);
	text.setCharacterSize(TEXT_SIZE);
	text.setFillColor(sf::Color::Black);
	defaultText = string;
	text.setString(string);
	isSelected = false;
	isPressed = false;
	editable = true;
	numeric = false;
	this->maxSize = maxSize;
}

void EditorText::setSelected(bool select) {
	isSelected = select;
	text.setFillColor(select ? sf::Color::Blue : sf::Color::Black);
}

void EditorText::setPressed(bool press) {
	isPressed = press;
	numFlag = false;
}

void EditorText::update(float deltaTime, sf::Vector2i mousePosition) {
	sf::Rect<float> bounds(
		getPosition().x,
		getPosition().y,
		text.getGlobalBounds().width,
		text.getGlobalBounds().height);
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
		text.getGlobalBounds().width,
		text.getGlobalBounds().height);
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
		if (event.text.unicode == 8) {
			if (numeric && text.getString().getSize() == 1) {
				inputText = "0.0";
			}
			else {
				inputText = inputText.substring(0, inputText.getSize() - 1);
			}
		}
		else if (!numeric) {
			inputText += event.text.unicode;
		}
		else if (isPressed) {
			if (!numFlag) {
				inputText = "0.0";
				numFlag = true;
			}
			if (event.text.unicode >= 48 &&
				event.text.unicode <= 57 &&
				stof(inputText.toAnsiString()) == 0.0) {
				inputText = event.text.unicode;
			}
			else if (event.text.unicode >= 48 &&
				event.text.unicode <= 57 ||
				event.text.unicode == 46) {
				inputText += event.text.unicode;
			}
			else if (event.text.unicode == 13) {
				std::ostringstream out;
				float temp = stof(inputText.toAnsiString());
				out << std::setprecision(2) << std::fixed << temp;
				inputText = sf::String(out.str());
				setPressed(false);
			}
		}
		textWrap();
	}
}

sf::String EditorText::getDefault() {
	return defaultText;
}

void EditorText::setDefault(sf::String string) {
	defaultText = string;
}

sf::String EditorText::getText() {
	return inputText;
}

void EditorText::setText(sf::String string) {
	inputText = string;
	textWrap();
}

void EditorText::setColor(sf::Color color) {
	this->color = color;
	defaultText.setFillColor(color);
	editText.setFillColor(color);
}

void EditorText::setEditable(bool edit) {
	editable = edit;
}

void EditorText::setNumeric(bool num) {
	numeric = num;
}

sf::Vector2f EditorText::getSize() {
	return sf::Vector2f(text.getGlobalBounds().width, text.getGlobalBounds().height);
}

void EditorText::textWrap() {
	sf::String string = defaultText + " " + inputText;
	text.setString("");
	sf::Text temp;
	temp.setFont(FontManager::getInstance().oldStandard);
	temp.setCharacterSize(TEXT_SIZE);
	temp.setString(string);
	if (temp.getGlobalBounds().width < 300) {
		text.setString(string);
		return;
	}
	else {
		int previous = 0, lastSpace = 0;
		for (int i = 0; i < string.getSize(); i++) {
			if (string[i] == 32) {
				temp.setString(string.substring(previous, i - previous));
				if (temp.getGlobalBounds().width > 300) {
					if (previous == 0) {
						text.setString(string.substring(previous, lastSpace));
						previous = lastSpace;
						lastSpace = i;
					}
					else {
						text.setString(text.getString() + "\n" + string.substring(previous + 1, lastSpace - previous));
						previous = lastSpace;
						lastSpace = i;
					}
				}
				else {
					lastSpace = i;
				}
			}
		}
		if (text.getString() == sf::String("")) {
			text.setString(string);
		}
		else {
			text.setString(text.getString() + "\n" + string.substring(previous + 1, sf::String::InvalidPos));
		}
	}
}

void EditorText::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = NULL;
	target.draw(text, states);
}