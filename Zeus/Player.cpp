#include "Player.h"

Player::Player() {
	name = "PLAYER_NAME";
	entt::registry& registry = GameDataManager::getInstance().getRegistry();
	auto view = registry.view<PlayerComponent, CharacterComponent>();
	for (auto entity : view) {
		auto& ettCharacter = registry.get<CharacterComponent>(entity);
		characters.push_back(&ettCharacter.character);
	}
	pID = 0;
	for (Character* c : characters) {
		pMenu.addCharacter(c);
	}
	pMenu.setVisible(true);
	//TODO SET INVENTORY MENU SIZE
	inventoryMenu.setVisible(true, activeCharacter);
	//TODO SET QUEST JOURNAL SIZE
	questJournal.setVisible(false, activeCharacter);
}

Player& Player::getInstance() {
	static Player instance;
	return instance;
}

void Player::update(float deltaTime, sf::Vector2i mousePosition) {
	pMenu.update(deltaTime, mousePosition);
	inventoryMenu.update(deltaTime, mousePosition);
	questJournal.update(deltaTime, mousePosition);
}

void Player::update(sf::Event event, sf::Vector2i mousePosition) {
	pMenu.update(event, mousePosition);
	inventoryMenu.update(event, mousePosition);
	questJournal.update(event, mousePosition);
}

void Player::draw(sf::RenderWindow& window) {
	window.draw(pMenu);
	window.draw(inventoryMenu);
	window.draw(questJournal);
}