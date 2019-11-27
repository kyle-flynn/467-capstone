#include "MonsterEditorScreen.h"

#include <iostream>
#include "PlayerMenu.h"

MonsterEditorScreen::MonsterEditorScreen() {
	Screen();
	it = 0;

	BGTexture.loadFromFile("Resources/images/questjournal/book/book.png");
	BGSprite.setTexture(BGTexture);
	BGSprite.setScale((float)(Game::WIDTH / BGTexture.getSize().x), (float)(Game::HEIGHT / BGTexture.getSize().y));
	defaultIcon.loadFromFile("Resources/images/questjournal/icons/9.png");
	defaultAvatar.loadFromFile("Resources/images/questjournal/icons/9.png");
	header.setFont(FontManager::getInstance().oldStandard);
	newMonster.setFont(FontManager::getInstance().oldStandard);
	deleteMonster.setFont(FontManager::getInstance().oldStandard);
	header.setCharacterSize(32);
	newMonster.setCharacterSize(20);
	deleteMonster.setCharacterSize(20);
	header.setFillColor(sf::Color::Black);
	newMonster.setFillColor(sf::Color::Black);
	deleteMonster.setFillColor(sf::Color::Black);
	header.setString(sf::String("Character List"));
	newMonster.setString(sf::String("New Chracter"));
	deleteMonster.setString(sf::String("Delete Character"));
	header.setPosition(850.0f, 150.0f);
	newMonster.setPosition(725.0f, 550.0f);
	deleteMonster.setPosition(newMonster.getGlobalBounds().width + 850.0f, 550.0f);
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
	activeDescription.setPosition(150.0f, 400.0f);
	activeIcon.setTexture(defaultIcon);
	activeAvatar.setTexture(defaultAvatar);
	activeIcon.setPosition(465.0f, 150.0f);
	activeAvatar.setPosition(465.0f, 350.0f);
	activeIcon.setScale((float)(ICON_SIZE / defaultIcon.getSize().x), (float)(ICON_SIZE / defaultIcon.getSize().y));
	activeAvatar.setScale((float)(AVATAR_WIDTH / defaultAvatar.getSize().x), (float)(AVATAR_HEIGHT / defaultAvatar.getSize().y));
	activeType.setEditable(false);
	activeHP.setNumeric(true);

	newBounds = sf::Rect<float>(
		725.0f, 550.0f,
		newMonster.getGlobalBounds().width,
		newMonster.getGlobalBounds().height + 20.0f);
	deleteBounds = sf::Rect<float>(
		deleteMonster.getPosition().x, 550.0f,
		deleteMonster.getGlobalBounds().width,
		deleteMonster.getGlobalBounds().height + 20.0f);
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
	loadMonsters();
}

void MonsterEditorScreen::update(float deltaTime) {
	sortMonsters();
	activeName.update(deltaTime, mousePosition);
	activeType.update(deltaTime, mousePosition);
	activeHP.update(deltaTime, mousePosition);
	activeDescription.update(deltaTime, mousePosition);
	for (MonsterOption* c : monsters) {
		c->update(deltaTime, mousePosition);
	}
	if (newBounds.contains(mousePosition.x, mousePosition.y)) {
		newMonster.setFillColor(sf::Color::Blue);
	}
	else if (deleteBounds.contains(mousePosition.x, mousePosition.y)) {
		deleteMonster.setFillColor(sf::Color::Blue);
	}
	else if (upBounds.contains(mousePosition.x, mousePosition.y)) {
		listUp.setFillColor(sf::Color::Blue);
	}
	else if (downBounds.contains(mousePosition.x, mousePosition.y)) {
		listDown.setFillColor(sf::Color::Blue);
	}
	else {
		newMonster.setFillColor(sf::Color::Black);
		deleteMonster.setFillColor(sf::Color::Black);
		listUp.setFillColor(sf::Color::Black);
		listDown.setFillColor(sf::Color::Black);
	}
}

void MonsterEditorScreen::update(sf::Event event) {
	sf::Rect<float> typeBounds(
		activeType.getPosition().x,
		activeType.getPosition().y,
		activeType.getSize().x,
		activeType.getSize().y);
	activeName.update(event, mousePosition);
	activeType.update(event, mousePosition);
	activeHP.update(event, mousePosition);
	activeDescription.update(event, mousePosition);
	if (event.type == sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Button::Left) {
		if (newBounds.contains(mousePosition.x, mousePosition.y)) {
			addMonster();
		}
		else if (deleteBounds.contains(mousePosition.x, mousePosition.y)) {
			removeMonster();
		}
		else if (upBounds.contains(mousePosition.x, mousePosition.y)) {
			if (it == 0) {
				it = monsters.size() - 1;
			}
			else {
				it--;
			}
		}
		else if (downBounds.contains(mousePosition.x, mousePosition.y)) {
			it = (it + 1) % monsters.size();
		}
		else if (typeBounds.contains(mousePosition.x, mousePosition.y)) {
			if (active->m.mType == Monster::type::Ground) {
				active->m.mType = Monster::type::Flying;
			}
			else {
				active->m.mType = Monster::type::Ground;
			}
			updateActive();
		}
		else {
			for (MonsterOption* m : monsters) {
				if (m->isSelected) {
					changeActive();
				}
			}
		}
	}
	if (active != nullptr) {
		active->m.name = activeName.getText();
		active->m.maxHP = std::stof(activeHP.getText().toAnsiString());
		active->m.description = activeDescription.getText().toAnsiString();
	}
}

void MonsterEditorScreen::draw(sf::RenderWindow& window) {
	mousePosition = sf::Mouse::getPosition(window);
	window.draw(BGSprite);
	window.draw(header);
	window.draw(newMonster);
	window.draw(deleteMonster);
	window.draw(listUp);
	window.draw(listDown);
	window.draw(activeName);
	activeType.setPosition(150.0f, activeName.getSize().y + activeName.getPosition().y + 25.0f);
	activeHP.setPosition(150.0f, activeType.getSize().y + activeType.getPosition().y + 25.0f);
	activeDescription.setPosition(150.0f, activeHP.getSize().y + activeHP.getPosition().y + 25.0f);
	window.draw(activeType);
	window.draw(activeHP);
	window.draw(activeDescription);
	window.draw(activeIcon);
	window.draw(activeAvatar);
	drawActive(window);

}

void MonsterEditorScreen::handleEvent(sf::Event event) {
	if (event.type == sf::Event::TextEntered &&
		event.text.unicode == 27) {
		GameDataManager::getInstance().addMonsters(monsters);
	}
	update(event);
}

void MonsterEditorScreen::addMonster() {
	MonsterOption* m = new MonsterOption();
	m->m.icon = defaultIcon;
	m->m.sprite = defaultAvatar;
	monsters.push_back(m);
}

void MonsterEditorScreen::removeMonster() {
	if (active == nullptr) {
		return;
	}
	else {
		for (int i = 0; i < monsters.size(); i++) {
			if (monsters.at(i) == active) {
				active = nullptr;
				std::cout << monsters.size() << std::endl;
				delete monsters[i];
				std::cout << monsters.size() << std::endl;
				monsters.erase(monsters.begin() + i);
			}
		}
	}
	changeActive();
}

void MonsterEditorScreen::changeActive() {
	for (MonsterOption* m : monsters) {
		if (m->isSelected) {
			active = m;
			updateActive();
			return;
		}
	}
	activeName.setText(sf::String("__________"));
	activeHP.setText(sf::String("__________"));
	activeDescription.setText(sf::String("__________"));
	activeIcon.setTexture(defaultIcon);
	activeAvatar.setTexture(defaultAvatar);
}

void MonsterEditorScreen::loadIcons() {
	for (const auto& entry : std::filesystem::directory_iterator("Resources/images/questjournal/icons")) {
		sf::Texture texture;
		std::cout << entry.path().string() << std::endl;
		texture.loadFromFile(entry.path().string());
		icons.push_back(texture);
	}
}

void MonsterEditorScreen::loadAvatars() {
	for (const auto& entry : std::filesystem::directory_iterator("Resources/images/questjournal/icons")) {
		sf::Texture texture;
		texture.loadFromFile(entry.path().string());
		avatars.push_back(texture);
	}
}

void MonsterEditorScreen::loadMonsters() {
	for (Monster m : GameDataManager::getInstance().getMonsters()) {
		MonsterOption* monster = new MonsterOption(m);
		monster->m.icon = defaultIcon;
		monster->m.sprite = defaultAvatar;
		monsters.push_back(monster);
	}
}

void MonsterEditorScreen::saveMonsters() {
	GameDataManager::getInstance().addMonsters(monsters);
}

void MonsterEditorScreen::sortMonsters() {
	std::vector<MonsterOption*> tempMonsters;
	for (MonsterOption* m : monsters) {
		if (m->m.mType == Monster::type::Ground) {
			tempMonsters.push_back(m);
		}
	}
	for (MonsterOption* m : monsters) {
		if (m->m.mType == Monster::type::Flying) {
			tempMonsters.push_back(m);
		}
	}
	monsters.clear();
	for (MonsterOption* m : tempMonsters) {
		monsters.push_back(m);
	}
}

void MonsterEditorScreen::updateActive() {
	activeName.setText(sf::String(active->m.name));
	if (active->m.mType == Monster::type::Ground) {
		activeType.setText(sf::String("Ground"));
	}
	else {
		activeType.setText(sf::String("Air"));
	}
	activeHP.setText(sf::String(std::to_string(active->m.maxHP)));
	activeDescription.setText(sf::String(active->m.description));
	activeIcon.setTexture(active->m.icon);
	activeAvatar.setTexture(active->m.sprite);
}

void MonsterEditorScreen::drawActive(sf::RenderWindow& window) {
	for (MonsterOption* m : monsters) {
		m->setPosition(0, 0);
	}
	int current = 0;
	int currentIt = it;
	if (monsters.size() <= 7) {
		for (MonsterOption* m : monsters) {
			m->setPosition(715.0f, 225.0f + current * 35.0f);
			window.draw(*m);
			current++;
		}
		it = 0;
	}
	else {
		while (current < 7) {
			monsters.at(currentIt)->setPosition(715.0f, 225.0f + current * 35.0f);
			window.draw(*monsters.at(currentIt));
			current++;
			currentIt = (currentIt + 1) % monsters.size();
		}
	}
}