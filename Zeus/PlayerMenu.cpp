#include "PlayerMenu.h"

PlayerMenu::PlayerMenu() {
	visible = true;
	charIt = 0;
	activeChar = nullptr;

	chars.setSize(sf::Vector2f(850.0f, 120.0f));
	chars.setPosition(250, 600);
	charStat.setSize(sf::Vector2f(250.0f, 320.0f));
	charStat.setPosition(0, 400);
	menuOptions.setSize(sf::Vector2f(180.0f, 250.0f));
	menuOptions.setPosition(1100, 470);

	int current = 0;
	for (int i = 0; i < 6; i++) {
		sf::Text text;
		text.setFont(FontManager::getInstance().oldStandard);
		text.setCharacterSize(TEXT_SIZE);
		text.setFillColor(sf::Color::Black);
		text.setPosition(10, 410 + current * 40);
		current++;
		statDescriptors.push_back(text);
	}
	statDescriptors.at(0).setString("Name:");
	statDescriptors.at(1).setString("Health:");
	statDescriptors.at(2).setString("Mana:");
	statDescriptors.at(3).setString("Stamina:");
	statDescriptors.at(4).setString("Attack:");
	statDescriptors.at(5).setString("Defence:");
}

void PlayerMenu::setVisible(bool vis) {
	visible = vis;
}

void PlayerMenu::update(float deltaTime, sf::Vector2i mousePosition) {

}

void PlayerMenu::update(sf::Event event, sf::Vector2i mousePosition) {
}

void PlayerMenu::addCharacter(Character* character) {
	characters.push_back(character);
}

void PlayerMenu::removeCharacter() {
	for (Character* c : characters) {
		if (c == activeChar) {
			delete c;
		}
	}
}

void PlayerMenu::updateActive(Character* character) {
	activeChar = character;
	if (characters.size() <= 1) {
		return;
	}
	else {
		charIt = charIt + 1 % characters.size();
		activeChar = characters.at(charIt);
		statDescriptors.at(0).setString("Name: " + activeChar->name);
		statDescriptors.at(1).setString("Health: " + std::to_string(activeChar->maxHP));
		statDescriptors.at(2).setString("Mana: " + std::to_string(activeChar->maxMana));
		statDescriptors.at(3).setString("Stamina: " + std::to_string(activeChar->maxStamina));
		statDescriptors.at(4).setString("Attack: " + std::to_string(activeChar->getAttack()));
		statDescriptors.at(5).setString("Defence: " + std::to_string(activeChar->getDefence()));
	}
}

void PlayerMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = NULL;
	if (visible) {
		target.draw(charStat);
		target.draw(chars);
		target.draw(menuOptions);

		//Draws the current player characters in the game
		int current = 0;
		for (Character* c : characters) {
			sf::Texture texture = c->icon;
			sf::Sprite sprite;
			sprite.setTexture(texture);
			sprite.setPosition(260 + current * 100, 610);
			target.draw(sprite);
			current++;
		}

		//Draws selected players stats
		for (sf::Text t : statDescriptors) {
			\
				target.draw(t);
		}
	}
}
