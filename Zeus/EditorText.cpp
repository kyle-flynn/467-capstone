#include "EditorText.h"

EditorText::EditorText(float maxSize) {
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
	numeric = false;
	maxSize = maxSize;
}

EditorText::EditorText(sf::String string, float maxSize) {
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
	numeric = false;
	maxSize = maxSize;
}

void EditorText::setSelected(bool select) {
	isSelected = select;
	editText.setFillColor(select ? sf::Color::Blue : sf::Color::Black);
}

void EditorText::setPressed(bool press) {
	isPressed = press;
	numFlag = false;
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
		if (event.text.unicode == 8) {
			if (numeric && editText.getString().getSize() == 1) {
				editText.setString(sf::String("0"));
			}
			else {
				editText.setString(editText.getString().substring(0, editText.getString().getSize() - 1));
			}
		}
		else if (!numeric) {
			editText.setString(editText.getString() + sf::String(event.text.unicode));
		}
		else if (isPressed) {
			if (!numFlag) {
				editText.setString(sf::String("0.0"));
				numFlag = true;
			}
			if (event.text.unicode >= 48 &&
				event.text.unicode <= 57 &&
				std::stof(editText.getString().toAnsiString()) == 0.0) {
				editText.setString(sf::String(event.text.unicode));
			}
			else if (event.text.unicode >= 48 &&
				event.text.unicode <= 57 ||
				event.text.unicode == 46) {
				editText.setString(editText.getString() + sf::String(event.text.unicode));
			}
			else if (event.text.unicode == 13) {
				std::ostringstream out;
				float temp = std::stof(editText.getString().toAnsiString());
				out << std::setprecision(2) << std::fixed << temp;
				editText.setString(sf::String(out.str()));
				setPressed(false);
			}
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

void EditorText::setNumeric(bool num) {
	numeric = num;
}

sf::Vector2f EditorText::getSize() {
	return sf::Vector2f(defaultText.getGlobalBounds().width + editText.getGlobalBounds().width + 20,
		defaultText.getGlobalBounds().height);
}

void EditorText::textWrap() {

}

void EditorText::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = NULL;
	target.draw(defaultText, states);
	target.draw(editText, states);
}