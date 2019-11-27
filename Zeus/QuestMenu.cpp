#include "QuestMenu.h"

QuestMenu::QuestMenu() {
	visible = false;
	listIt = 0;
	activeChar = nullptr;
	
	BGTexture.loadFromFile("Resources/images/questjournal/book/book.png");
	BGSprite.setTexture(BGTexture);
	BGSprite.setPosition(250, 10);
	BGSprite.setScale((float)(850.0f / BGTexture.getSize().x), (float)(600.0f / BGTexture.getSize().y));
}

void QuestMenu::setVisible(bool vis, Character* character) {
	activeChar = character;
	visible = vis;
}

void QuestMenu::update(float deltaTime, sf::Vector2i mousePosition) {
}

void QuestMenu::update(sf::Event event, sf::Vector2i mousePosition) {
}

void QuestMenu::loadQuests() {
	//TODO LOAD FROM ACTIVE CHARACTER
}

void QuestMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
}