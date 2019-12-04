#include "QuestEditorScreen.h"
#include "MainMenuScreen.h"

#include "GameDataManager.h"

QuestEditorScreen::QuestEditorScreen() {
	Screen();
	it = 0;
	BGTexture.loadFromFile("Resources/images/questjournal/book/book.png");
	BGSprite.setTexture(BGTexture);
	BGSprite.setScale((float)(Game::WIDTH / BGTexture.getSize().x), (float)(Game::HEIGHT / BGTexture.getSize().y));
	defaultIcon.loadFromFile("Resources/images/questjournal/icons/9.png");
	activeIcon.setTexture(defaultIcon);
	activeIcon.setScale((float)(ICON_SIZE / defaultIcon.getSize().x), (float)(ICON_SIZE / defaultIcon.getSize().y));
	/*header.setFont(FontManager::getInstance().oldStandard);
	activeName.setFont(FontManager::getInstance().oldStandard);
	activeType.setFont(FontManager::getInstance().oldStandard);
	activeStat.setFont(FontManager::getInstance().oldStandard);
	activeDescription.setFont(FontManager::getInstance().oldStandard);*/
	newQuest.setFont(FontManager::getInstance().oldStandard);
	deleteQuest.setFont(FontManager::getInstance().oldStandard);
	header.setCharacterSize(32);
	/*activeName.setCharacterSize(20);
	activeType.setCharacterSize(20);
	activeStat.setCharacterSize(20);
	activeDescription.setCharacterSize(20);*/
	newQuest.setCharacterSize(20);
	deleteQuest.setCharacterSize(20);
	header.setFillColor(sf::Color::Black);
	/*activeName.setFillColor(sf::Color::Black);
	activeType.setFillColor(sf::Color::Black);
	activeStat.setFillColor(sf::Color::Black);
	activeDescription.setFillColor(sf::Color::Black);*/
	newQuest.setFillColor(sf::Color::Black);
	deleteQuest.setFillColor(sf::Color::Black);
	header.setString(sf::String("Quest List"));
	/*activeName.setText(sf::String("Quest name: ___________"));
	activeType.setText(sf::String("Quest type: ___________"));
	activeStat.setText(sf::String("Damage: ___________"));
	activeDescription.setText(sf::String("Description: "));*/
	newQuest.setString(sf::String("New Quest"));
	deleteQuest.setString(sf::String("Delete Quest"));
	header.setPosition(850.0f, 150.0f);
	activeName.setPosition(150.0f, 150.0f);
	activeType.setPosition(150.0f, 225.0f);
	activeStat.setPosition(150.0f, 300.0f);
	activeDescription.setPosition(150.0f, 375.0f);
	activeIcon.setPosition(415.0f, 150.0f);
	newQuest.setPosition(800.0f, 550.0f);
	deleteQuest.setPosition(newQuest.getGlobalBounds().width + 850.0f, 550.0f);
	listUp.setRadius(10);
	listUp.setPointCount(3);
	listUp.setFillColor(sf::Color::Black);
	listUp.setPosition(1100.0f, 200.0f);
	listDown.setRadius(10);
	listDown.setPointCount(3);
	listDown.setRotation(180);
	listDown.setFillColor(sf::Color::Black);
	listDown.setPosition(1120.0f, 500.0f);
	newBounds = sf::Rect<float>(
		800.0f, 550.0f,
		newQuest.getGlobalBounds().width,
		newQuest.getGlobalBounds().height + 20.0f);
	deleteBounds = sf::Rect<float>(
		deleteQuest.getPosition().x, 550.0f,
		deleteQuest.getGlobalBounds().width,
		deleteQuest.getGlobalBounds().height + 20.0f);
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
	activeType.setEditable(false);
	activeStat.setNumeric(true);
	loadIcons();
	loadQuests();
}

void QuestEditorScreen::update(float deltaTime) {
	sortQuests();
	activeName.update(deltaTime, mousePosition);
	activeType.update(deltaTime, mousePosition);
	activeStat.update(deltaTime, mousePosition);
	activeDescription.update(deltaTime, mousePosition);
	for (QuestOption* i : quests) {
		i->update(deltaTime, mousePosition);
	}
	if (newBounds.contains(mousePosition.x, mousePosition.y)) {
		newQuest.setFillColor(sf::Color::Blue);
	}
	else if (deleteBounds.contains(mousePosition.x, mousePosition.y)) {
		deleteQuest.setFillColor(sf::Color::Blue);
	}
	else if (upBounds.contains(mousePosition.x, mousePosition.y)) {
		listUp.setFillColor(sf::Color::Blue);
	}
	else if (downBounds.contains(mousePosition.x, mousePosition.y)) {
		listDown.setFillColor(sf::Color::Blue);
	}
	else {
		newQuest.setFillColor(sf::Color::Black);
		deleteQuest.setFillColor(sf::Color::Black);
		listUp.setFillColor(sf::Color::Black);
		listDown.setFillColor(sf::Color::Black);
	}
}

void QuestEditorScreen::update(sf::Event event) {
	sf::Rect<float> typeBounds(
		activeType.getPosition().x,
		activeType.getPosition().y,
		activeType.getSize().x,
		activeType.getSize().y);
	activeName.update(event, mousePosition);
	activeType.update(event, mousePosition);
	activeStat.update(event, mousePosition);
	activeDescription.update(event, mousePosition);
	if (event.type == sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Button::Left) {
		if (newBounds.contains(mousePosition.x, mousePosition.y)) {
			addQuest();
		}
		else if (deleteBounds.contains(mousePosition.x, mousePosition.y)) {
			removeQuest();
		}
		else if (upBounds.contains(mousePosition.x, mousePosition.y) && !quests.empty()) {
			if (it == 0) {
				it = Quests.size() - 1;
			}
			else {
				it--;
			}
		}
		else if (downBounds.contains(mousePosition.x, mousePosition.y) && !quests.empty()) {
			it = (it + 1) % quests.size();
		}
		else if (typeBounds.contains(mousePosition.x, mousePosition.y)) {
			active->quest.questType = (quest::type)(((int)(active->quest.questType) + 1) % 4);
			updateActiveStats();
		}
		else {
			for (QuestOption* i : quests) {
				if (i->isSelected) {
					changeActive();
				}
			}
		}
	}
	if (active != nullptr) {
		active->quest.name = activeName.getText();
		active->quest.goal = activeName.getText();
		active->quest.reward = activeName.getText();
	}
}

void QuestEditorScreen::draw(sf::RenderWindow& window) {
	mousePosition = sf::Mouse::getPosition(window);
	window.draw(BGSprite);
	window.draw(header);
	window.draw(activeName);
	activeType.setPosition(150.0f, activeName.getPosition().y + activeName.getSize().y + 25.0f);
	activeStat.setPosition(150.0f, activeType.getPosition().y + activeType.getSize().y + 25.0f);
	activeDescription.setPosition(150.0f, activeStat.getPosition().y + activeStat.getSize().y + 25.0f);
	window.draw(activeType);
	window.draw(activeStat);
	window.draw(activeIcon);
	window.draw(activeDescription);
	window.draw(newQuest);
	window.draw(deleteQuest);
	window.draw(listUp);
	window.draw(listDown);
	drawActive(window);
	/*for (int i = 0; i < activeQuests.size(); i++) {
		activeQuests.at(i)->setPosition(715.0f, 225.0f + i * 35.0f);
		window.draw(activeQuests.at(i));
	}*/
}

void QuestEditorScreen::handleEvent(sf::Event event) {
	if (event.type == event.TextEntered &&
		event.text.unicode == 27) {
		ScreenManager::getInstance().setScreen(new MainMenuScreen());
	}
	/*if (event.type == sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Button::Left) {
		std::cout << mousePosition.x << " " << mousePosition.y << std::endl;
		update(event);
	}*/
	if (event.type == sf::Event::TextEntered &&
		event.text.unicode == 27) {
		GameDataManager::getInstance().addQuests(quests);
	}
	update(event);
}

void QuestEditorScreen::addQuest() {
	QuestOption* newQuest = new QuestOption();
	newQuest->quest.icon = defaultIcon;
	quests.push_back(newQuest);
}

void QuestEditorScreen::removeQuest() {
	if (active == nullptr) {
		return;
	}
	else {
		for (int i = 0; i < quests.size(); i++) {
			if (quests.at(i) == active) {
				active = nullptr;
				delete quests[i];
				quests.erase(quests.begin() + i);
			}
		}
	}
	changeActive();
}

void QuestEditorScreen::changeActive() {
	for (QuestOption* i : quests) {
		if (i->isSelected) {
			active = i;
			updateActiveStats();
			/*activeName.setText(sf::String(i->getName()));
			activeType.setText(sf::String( i->getType()));
			if (active->quest.questType == type::Weapon) {
				activeStat.setText(sf::String(std::to_string(active->quest.stat)));
			}
			else if (active->quest.questType == type::Equippable) {
				activeStat.setText(sf::String(std::to_string(active->quest.stat)));
			}
			else if (active->quest.questType == type::Consumable) {
				activeStat.setText(sf::String(std::to_string(active->quest.stat)));
			}
			else {
				activeStat.setText(sf::String(""));
			}
			activeDescription.setText(sf::String(i->getDescription()));
			activeIcon.setTexture(i->quest.icon);*/
			return;
		}
	}
	activeName.setText(sf::String("__________"));
	activeGoal.setText(sf::String("__________"));
	activeReward.setText(sf::String("__________"));
	
}



void QuestEditorScreen::loadQuests() {
	for (Quest i : GameDataManager::getInstance().getQuests()) {
		QuestOption* quest = new QuestOption(i);
		quest->quest.icon = defaultIcon;
		quests.push_back(quest);
	}
}


void QuestEditorScreen::drawActive(sf::RenderWindow& window) {
	for (QuestOption* i : quests) {
		i->setPosition(0, 0);
	}
	int current = 0;
	int currentIt = it;
	if (quests.size() <= 7) {
		for (QuestOption* i : quests) {
			i->setPosition(715.0f, 225.0f + current * 35.0f);
			window.draw(*i);
			current++;
		}
		it = 0;
	}
	else {
		while (current < 7) {
			quests.at(currentIt)->setPosition(715.0f, 225.0f + current * 35.0f);
			window.draw(*quests.at(currentIt));
			current++;
			currentIt = (currentIt + 1) % quests.size();
		}
	}
}