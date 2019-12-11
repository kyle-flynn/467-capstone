#include "MainMenuScreen.h"

#include "EntityComponentSystem.h"
#include "Components.h"

#include "CharacterEditorScreen.h"
#include "ItemEditorScreen.h"
//#include "QuestEditorScreen.h"
#include "DIalogueEditorScreen.h"
#include "GameplayScreen.h"
#include "DemoScreen.h"
#include "DialogueEditorPanel.h"
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
	worldGeneration.setPosition(350.0f, 425.0f);
	worldGeneration.setColor(sf::Color::White);
	worldGeneration.setEditable(false);
	worldGeneration.setText("World Generation");
	questEditor.setPosition(350.0f, 475.0f);
	questEditor.setColor(sf::Color::White);
	questEditor.setEditable(false);
	questEditor.setText("Quest Editor");
}

void MainMenuScreen::update(float deltaTime) {
	characterEditor.update(deltaTime, mousePosition);
	monsterEditor.update(deltaTime, mousePosition);
	itemEditor.update(deltaTime, mousePosition);
	dialogueEditor.update(deltaTime, mousePosition);
	questEditor.update(deltaTime, mousePosition);
	worldGeneration.update(deltaTime, mousePosition);
	this->lightningSystem.update(deltaTime);
	this->titleTextSystem.update(deltaTime);

	this->mainScene.update(deltaTime);
	/*if (this->mainScene.hasSelected) {
		if (this->mainScene.selectedId == 0) {
			ScreenManager::getInstance().setScreen(new GameplayScreen());
		}
	}*/
}

void MainMenuScreen::update(sf::Event event) {
	sf::Rect<float> cBounds(
		characterEditor.getPosition().x,
		characterEditor.getPosition().y,
		characterEditor.getSize().x,
		characterEditor.getSize().y + 7);
	sf::Rect<float> iBounds(
		itemEditor.getPosition().x,
		itemEditor.getPosition().y,
		itemEditor.getSize().x,
		itemEditor.getSize().y + 7);
	sf::Rect<float> dBounds(
		dialogueEditor.getPosition().x,
		dialogueEditor.getPosition().y,
		dialogueEditor.getSize().x,
		dialogueEditor.getSize().y + 7);
	sf::Rect<float> wBounds(
		worldGeneration.getPosition().x,
		worldGeneration.getPosition().y,
		worldGeneration.getSize().x,
		worldGeneration.getSize().y + 7);
	sf::Rect<float> qBounds(
		questEditor.getPosition().x,
		questEditor.getPosition().y,
		questEditor.getSize().x,
		questEditor.getSize().y + 7);

	if (event.type == sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Button::Left) {
		if (cBounds.contains(mousePosition.x, mousePosition.y)) {
			ScreenManager::getInstance().setScreen(new CharacterEditorScreen());
		}
		else if (iBounds.contains(mousePosition.x, mousePosition.y)) {
			ScreenManager::getInstance().setScreen(new ItemEditorScreen());
		}
		else if (qBounds.contains(mousePosition.x, mousePosition.y)) {
			ScreenManager::getInstance().setScreen(new QuestEditorScreen());
		}
		else if (dBounds.contains(mousePosition.x, mousePosition.y)) {
			//Game::gui.add(DialogueEditorPanel::getInstance().getPanel(), "DialogueEditorPanel");
			ScreenManager::getInstance().setScreen(new DialogueEditorScreen());
		}
		else if (wBounds.contains(mousePosition.x, mousePosition.y)) {
			ScreenManager::getInstance().setScreen(new GameplayScreen());
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
			questEditor.setColor(sf::Color::White);
			monsterEditor.setColor(sf::Color::White);
			dialogueEditor.setColor(sf::Color::White);
			worldGeneration.setColor(sf::Color::White);
		}
		else {
			characterEditor.setColor(sf::Color::Transparent);
			itemEditor.setColor(sf::Color::Transparent);
			questEditor.setColor(sf::Color::Transparent);
			monsterEditor.setColor(sf::Color::Transparent);
			dialogueEditor.setColor(sf::Color::Transparent);
			worldGeneration.setColor(sf::Color::Transparent);
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
	window.draw(questEditor);
	window.draw(characterEditor);
	window.draw(dialogueEditor);
	window.draw(worldGeneration);
}