#include "MainMenuScreen.h"

#include "EntityComponentSystem.h"
#include "Components.h"

MainMenuScreen::MainMenuScreen() : 
	Screen(),
	lightningSystem(0.0f, Game::WIDTH, 0.0f, Game::HEIGHT)
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
	this->lightningSystem.update(deltaTime);
}

void MainMenuScreen::draw(sf::RenderWindow& window) {
	window.draw(this->lightningSystem);
	window.draw(this->zeusSprite);
}