#include "MainMenuScreen.h"

#include "EntityComponentSystem.h"
#include "Components.h"

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
	
}

void MainMenuScreen::update(float deltaTime) {
	int* shptr = 0;
	int** tileVals = 0;
	this->lightningSystem.update(deltaTime);
	this->titleTextSystem.update(deltaTime);

	this->mainScene.update(deltaTime);
	if (this->mainScene.hasSelected) {
		if (this->mainScene.selectedId == 0) {
			ScreenManager::getInstance().setScreen(new GameplayScreen(*shptr, tileVals));
		}
	}
}

void MainMenuScreen::draw(sf::RenderWindow& window) {
	window.draw(this->lightningSystem);
	window.draw(this->zeusSprite);
	window.draw(this->titleTextSystem);

	this->mainScene.draw(window);
}