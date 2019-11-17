#include "CharacterEditorScreen.h"

#include <iostream>

CharacterEditorScreen::CharacterEditorScreen() {
	Screen();
	it = 0;

	BGTexture.loadFromFile("Resources/images/questjournal/book/book.png");
	BGSprite.setTexture(BGTexture);
	BGSprite.setScale((float)(Game::WIDTH / BGTexture.getSize().x), (float)(Game::HEIGHT / BGTexture.getSize().y));
	defaultIcon.loadFromFile("Resources/images/questjournal/icons/9.png");
	defaultAvatar.loadFromFile("Resources/images/questjournal/icons/9.png");
	header.setFont(FontManager::getInstance().oldStandard);
	newChar.setFont(FontManager::getInstance().oldStandard);
	deleteChar.setFont(FontManager::getInstance().oldStandard);
	header.setCharacterSize(32);
	newChar.setCharacterSize(20);
	deleteChar.setCharacterSize(20);
	header.setFillColor(sf::Color::Black);
	newChar.setFillColor(sf::Color::Black);
	deleteChar.setFillColor(sf::Color::Black);
	header.setString(sf::String("Character List"));
	newChar.setString(sf::String("New Chracter"));
	deleteChar.setString(sf::String("Delete Character"));
	header.setPosition(850.0f, 150.0f);
	newChar.setPosition(725.0f, 550.0f);
	deleteChar.setPosition(newChar.getGlobalBounds().width + 850.0f, 550.0f);
	listUp.setRadius(10);
	listDown.setRadius(10);
	listUp.setPointCount(3);
	listDown.setPointCount(3);
	listUp.setFillColor(sf::Color::Black);
	listDown.setFillColor(sf::Color::Black);
	listUp.setPosition(1100.0f, 200.0f);
	listDown.setPosition(1120.0f, 500.0f);
	listDown.setRotation(180.0f);

	activeName.setPosition(150.0f, 150.0f);
	activeType.setPosition(150.0f, 200.0f);
	activeHP.setPosition(150.0f, 250.0f);
	activeMana.setPosition(150.0f, 300.0f);
	activeStamina.setPosition(150.0f, 350.0f);
	activeDescription.setPosition(150.0f, 400.0f);
	activeIcon.setTexture(defaultIcon);
	activeAvatar.setTexture(defaultAvatar);
	activeIcon.setPosition(465.0f, 150.0f);
	activeAvatar.setPosition(465.0f, 350.0f);
	activeIcon.setScale((float)(ICON_SIZE / defaultIcon.getSize().x), (float)(ICON_SIZE / defaultIcon.getSize().y));
	activeAvatar.setScale((float)(AVATAR_WIDTH / defaultAvatar.getSize().x), (float)(AVATAR_HEIGHT / defaultAvatar.getSize().y));
	activeType.setEditable(false);
	activeHP.setNumeric(true);
	activeMana.setNumeric(true);
	activeStamina.setNumeric(true);

	newBounds = sf::Rect<float>(
		725.0f, 550.0f,
		newChar.getGlobalBounds().width,
		newChar.getGlobalBounds().height + 20.0f);
	deleteBounds = sf::Rect<float>(
		deleteChar.getPosition().x, 550.0f,
		deleteChar.getGlobalBounds().width,
		deleteChar.getGlobalBounds().height + 20.0f);
	upBounds = sf::Rect<float>(
		listUp.getPosition().x,
		listUp.getPosition().y,
		listUp.getGlobalBounds().width,
		listUp.getGlobalBounds().height);
	downBounds = sf::Rect<float>(
		listDown.getPosition().x - listDown.getRadius(),
		listDown.getPosition().y - listDown.getRadius(),
		listDown.getPosition().x,
		listDown.getPosition().y);

	loadIcons();
	loadAvatars();
	loadCharacters();
}

void CharacterEditorScreen::update(float deltaTime) {
	sortCharacters();
	activeName.update(deltaTime, mousePosition);
	activeType.update(deltaTime, mousePosition);
	activeHP.update(deltaTime, mousePosition);
	activeMana.update(deltaTime, mousePosition);
	activeStamina.update(deltaTime, mousePosition);
	activeDescription.update(deltaTime, mousePosition);
	for (CharacterOption* c : characters) {
		c->update(deltaTime, mousePosition);
	}
	if (newBounds.contains(mousePosition.x, mousePosition.y)) {
		newChar.setFillColor(sf::Color::Blue);
	}
	else if (deleteBounds.contains(mousePosition.x, mousePosition.y)) {
		deleteChar.setFillColor(sf::Color::Blue);
	}
	else if (upBounds.contains(mousePosition.x, mousePosition.y)) {
		listUp.setFillColor(sf::Color::Blue);
	}
	else if (downBounds.contains(mousePosition.x, mousePosition.y)) {
		listDown.setFillColor(sf::Color::Blue);
	}
	else {
		newChar.setFillColor(sf::Color::Black);
		deleteChar.setFillColor(sf::Color::Black);
		listUp.setFillColor(sf::Color::Black);
		listDown.setFillColor(sf::Color::Black);
	}
}

void CharacterEditorScreen::update(sf::Event event) {
	sf::Rect<float> typeBounds(
		activeType.getPosition().x,
		activeType.getPosition().y,
		activeType.getSize().x,
		activeType.getSize().y);
	activeName.update(event, mousePosition);
	activeType.update(event, mousePosition);
	activeHP.update(event, mousePosition);
	activeMana.update(event, mousePosition);
	activeStamina.update(event, mousePosition);
	activeDescription.update(event, mousePosition);
	if (event.type == sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Button::Left) {
		if (newBounds.contains(mousePosition.x, mousePosition.y)) {
			addCharacter();
		}
		else if (deleteBounds.contains(mousePosition.x, mousePosition.y)) {
			removeCharacter();
		}
		else if (upBounds.contains(mousePosition.x, mousePosition.y)) {
			if (it == 0) {
				it = characters.size() - 1;
			}
			else {
				it--;
			}
		}
		else if (downBounds.contains(mousePosition.x, mousePosition.y)) {
			it = (it + 1) % characters.size();
		}
		else if (typeBounds.contains(mousePosition.x, mousePosition.y)) {
			active->c.playable = active->c.playable ? false : true;
			updateActive();
		}
		else {
			for (CharacterOption* c : characters) {
				if (c->isSelected) {
					changeActive();
				}
			}
		}
	}
	if (active != nullptr) {
		active->c.name = activeName.getText();
		active->c.maxHP = std::stof(activeHP.getText().toAnsiString());
		active->c.maxMana = std::stof(activeMana.getText().toAnsiString());
		active->c.maxStamina = std::stof(activeStamina.getText().toAnsiString());
		active->c.description = activeDescription.getText().toAnsiString();
	}
}

void CharacterEditorScreen::draw(sf::RenderWindow& window) {
	mousePosition = sf::Mouse::getPosition(window);
	window.draw(BGSprite);
	window.draw(header);
	window.draw(newChar);
	window.draw(deleteChar);
	window.draw(listUp);
	window.draw(listDown);
	activeType.setPosition(150.0f, activeName.getPosition().y + activeName.getSize().y + 25.0f);
	activeHP.setPosition(150.0f, activeType.getPosition().y + activeType.getSize().y + 25.0f);
	activeMana.setPosition(150.0f, activeHP.getPosition().y + activeHP.getSize().y + 25.0f);
	activeStamina.setPosition(150.0f, activeMana.getPosition().y + activeMana.getSize().y + 25.0f);
	activeDescription.setPosition(150.0f, activeStamina.getPosition().y + activeStamina.getSize().y + 25.0f);
	window.draw(activeName);
	window.draw(activeType);
	window.draw(activeHP);
	window.draw(activeMana);
	window.draw(activeStamina);
	window.draw(activeDescription);
	window.draw(activeIcon);
	window.draw(activeAvatar);
	drawActive(window);
}

void CharacterEditorScreen::handleEvent(sf::Event event) {
	if (event.type == sf::Event::TextEntered &&
		event.text.unicode == 27) {
		GameDataManager::getInstance().addCharacters(characters);
	}
	update(event);
}

void CharacterEditorScreen::addCharacter() {
	CharacterOption* c = new CharacterOption();
	c->c.icon = defaultIcon;
	c->c.sprite = defaultAvatar;
	characters.push_back(c);
}

void CharacterEditorScreen::removeCharacter() {
	if (active == nullptr) {
		return;
	}
	else {
		for (int i = 0; i < characters.size(); i++) {
			if (characters.at(i) == active) {
				active = nullptr;
				delete characters[i];
				characters.erase(characters.begin() + i);
			}
		}
	}
	changeActive();
}

void CharacterEditorScreen::changeActive() {
	for (CharacterOption* c : characters) {
		if (c->isSelected) {
			active = c;
			updateActive();
			return;
		}
	}
	activeName.setText(sf::String("__________"));
	activeHP.setText(sf::String("__________"));
	activeMana.setText(sf::String("__________"));
	activeStamina.setText(sf::String("__________"));
	activeDescription.setText(sf::String("__________"));
	activeIcon.setTexture(defaultIcon);
	activeAvatar.setTexture(defaultAvatar);
}

void CharacterEditorScreen::loadIcons() {
	for (const auto& entry : std::filesystem::directory_iterator("Resources/images/questjournal/icons")) {
		sf::Texture texture;
		std::cout << entry.path().string() << std::endl;
		texture.loadFromFile(entry.path().string());
		icons.push_back(texture);
	}
}

void CharacterEditorScreen::loadAvatars() {
	for (const auto& entry : std::filesystem::directory_iterator("Resources/images/questjournal/icons")) {
		sf::Texture texture;
		texture.loadFromFile(entry.path().string());
		avatars.push_back(texture);
	}
}

void CharacterEditorScreen::loadCharacters() {
	for (Character c : GameDataManager::getInstance().getCharacters()) {
		CharacterOption* character = new CharacterOption(c);
		character->c.icon = defaultIcon;
		character->c.sprite = defaultAvatar;
		characters.push_back(character);
	}
}

void CharacterEditorScreen::saveCharacters() {
	GameDataManager::getInstance().addCharacters(characters);
}

void CharacterEditorScreen::sortCharacters() {
	std::vector<CharacterOption*> tempChars;
	for (CharacterOption* c : characters) {
		if (c->c.playable == true) {
			tempChars.push_back(c);
		}
	}
	for (CharacterOption* c : characters) {
		if (c->c.playable == false) {
			tempChars.push_back(c);
		}
	}
	characters.clear();
	for (CharacterOption* c : tempChars) {
		characters.push_back(c);
	}
}

void CharacterEditorScreen::updateActive() {
	activeName.setText(sf::String(active->c.name));
	if (active->c.playable) {
		activeType.setText(sf::String("Player"));
	}
	else {
		activeType.setText(sf::String("NPC"));
	}
	activeHP.setText(sf::String(std::to_string(active->c.maxHP)));
	activeMana.setText(sf::String(std::to_string(active->c.maxMana)));
	activeStamina.setText(sf::String(std::to_string(active->c.maxStamina)));
	activeDescription.setText(sf::String(active->c.description));
	activeIcon.setTexture(active->c.icon);
	activeAvatar.setTexture(active->c.sprite);
}

void CharacterEditorScreen::drawActive(sf::RenderWindow& window) {
	for (CharacterOption* c : characters) {
		c->setPosition(0, 0);
	}
	int current = 0;
	int currentIt = it;
	if (characters.size() <= 7) {
		for (CharacterOption* c : characters) {
			c->setPosition(715.0f, 225.0f + current * 35.0f);
			window.draw(*c);
			current++;
		}
		it = 0;
	}
	else {
		while (current < 7) {
			characters.at(currentIt)->setPosition(715.0f, 225.0f + current * 35.0f);
			window.draw(*characters.at(currentIt));
			current++;
			currentIt = (currentIt + 1) % characters.size();
		}
	}
}