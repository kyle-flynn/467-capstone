#include "MainMenuScreen.h"

#include "EntityComponentSystem.h"
#include "Components.h"

#include "CharacterEditorScreen.h"
#include "ItemEditorScreen.h"
#include "DIalogueEditorScreen.h"
#include "DemoScreen.h"
#include "CombatScreen.h"

MainMenuScreen::MainMenuScreen() : 
	Screen(),
	lightningSystem(0.0f, Game::WIDTH, 0.0f, Game::HEIGHT),
	titleTextSystem(0.0f, Game::WIDTH / 2, 0.0f, Game::HEIGHT, 150.0f, 50.0f, 3.0f, "ZEUS"),
	mainScene()
{
	/*
	entt::registry registry;
	auto entity = registry.create();
	registry.assign<ParallaxComponent>(entity, 0.0f, 10.0f);
	*/
	this->zeusTexture.loadFromFile("Resources/Intro/zeus_opaque_landscape.png");
	this->zeusSprite.setTexture(this->zeusTexture);
	this->zeusSprite.setScale(0.6666f, 0.6666f);


	combatBounds = sf::Rect<float>(
		0, 600.0f, 120.0f, 720.0f);
	movementBounds = sf::Rect<float>(
		1160.0f, 600.0f, 1280.0f, 720.0f);
	characterEditor.setPosition(350.0f, 225.0f);
	characterEditor.setColor(sf::Color::White);
	characterEditor.setEditable(false);
	characterEditor.setText("Character Editor");
	monsterEditor.setPosition(350.0f, 275.0f);
	monsterEditor.setColor(sf::Color::White);
	monsterEditor.setEditable(false);
	monsterEditor.setText("Monster Editor");
	itemEditor.setPosition(350.0f, 325.0f);
	itemEditor.setColor(sf::Color::White);
	itemEditor.setEditable(false);
	itemEditor.setText("Item Editor");
	dialogueEditor.setPosition(350.0f, 375.0f);
	dialogueEditor.setColor(sf::Color::White);
	dialogueEditor.setEditable(false);
	dialogueEditor.setText("Dialogue Editor");
}

void MainMenuScreen::update(float deltaTime) {
	this->lightningSystem.update(deltaTime);
	this->titleTextSystem.update(deltaTime);

	this->mainScene.update(deltaTime);
	/*if (this->mainScene.hasSelected) {
		if (this->mainScene.selectedId == 0) {
			ScreenManager::getInstance().setScreen(new GameplayScreen());
		}
	}*/

	characterEditor.update(deltaTime, mousePosition);
	monsterEditor.update(deltaTime, mousePosition);
	itemEditor.update(deltaTime, mousePosition);
	dialogueEditor.update(deltaTime, mousePosition);
}

void MainMenuScreen::update(sf::Event event) {
	if (event.type == sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Button::Left) {
		if (characterEditor.isSelected) {
			ScreenManager::getInstance().setScreen(new CharacterEditorScreen());
		}
		else if (itemEditor.isSelected) {
			ScreenManager::getInstance().setScreen(new ItemEditorScreen());
		}
		else if (dialogueEditor.isSelected) {
			ScreenManager::getInstance().setScreen(new DialogueEditorScreen());
		}
		else if (movementBounds.contains(mousePosition.x, mousePosition.y)) {
			ScreenManager::getInstance().setScreen(new DemoScreen());
		}
		else if (combatBounds.contains(mousePosition.x, mousePosition.y)) {
			ScreenManager::getInstance().setScreen(new CombatScreen());
		}
		else if (mainScene.hasSelected) {
			characterEditor.setColor(sf::Color::White);
			itemEditor.setColor(sf::Color::White);
			monsterEditor.setColor(sf::Color::White);
			dialogueEditor.setColor(sf::Color::White);
		}
		else {
			characterEditor.setColor(sf::Color::Transparent);
			itemEditor.setColor(sf::Color::Transparent);
			monsterEditor.setColor(sf::Color::Transparent);
			dialogueEditor.setColor(sf::Color::Transparent);
		}
	}
}

void MainMenuScreen::handleEvent(sf::Event event) {
	update(event);
}

void MainMenuScreen::draw(sf::RenderWindow& window) {
	mousePosition = sf::Mouse::getPosition(window);
	window.draw(this->lightningSystem);
	window.draw(this->zeusSprite);
	window.draw(this->titleTextSystem);

	this->mainScene.draw(window);

	window.draw(characterEditor);
	window.draw(monsterEditor);
	window.draw(itemEditor);
	window.draw(characterEditor);
}