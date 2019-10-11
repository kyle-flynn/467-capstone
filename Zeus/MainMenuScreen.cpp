#include "MainMenuScreen.h"

#include "EntityComponentSystem.h"
#include "Components.h"

MainMenuScreen::MainMenuScreen() : 
	Screen(),
	lightningSystem(0.0f, Game::WIDTH, 0.0f, Game::HEIGHT),
	titleTextSystem(0.0f, Game::WIDTH / 2, 0.0f, Game::HEIGHT, 150.0f, 50.0f, 3.0f, "ZEUS"),
	optionCampaignEditor("Campaign Editor", false),
	optionCreateSession("Create Session", false),
	optionJoinSession("Join Session", false),
	optionOptions("Options", false)
{
	/*
	entt::registry registry;
	auto entity = registry.create();
	registry.assign<ParallaxComponent>(entity, 0.0f, 10.0f);
	*/
	this->zeusTexture.loadFromFile("Resources/Intro/zeus_opaque_landscape.png");
	this->zeusSprite.setTexture(this->zeusTexture);
	this->zeusSprite.setScale(0.6666f, 0.6666f);

	this->optionCampaignEditor.setPosition(150.0f, 225.0f);
	this->optionCreateSession.setPosition(150.0f, 275.0f);
	this->optionJoinSession.setPosition(150.0f, 325.0f);
	this->optionOptions.setPosition(150.0f, 375.0f);
}

void MainMenuScreen::update(float deltaTime) {
	this->lightningSystem.update(deltaTime);
	this->titleTextSystem.update(deltaTime);

	this->optionCampaignEditor.update(deltaTime, sf::Mouse::getPosition());
	//this->optionCreateSession.update(deltaTime, sf::Mouse::getPosition());
	//this->optionJoinSession.update(deltaTime, sf::Mouse::getPosition());
	//this->optionOptions.update(deltaTime, sf::Mouse::getPosition());
}

void MainMenuScreen::draw(sf::RenderWindow& window) {
	window.draw(this->lightningSystem);
	window.draw(this->zeusSprite);
	window.draw(this->titleTextSystem);
	window.draw(this->optionCampaignEditor);
	window.draw(this->optionCreateSession);
	window.draw(this->optionJoinSession);
	window.draw(this->optionOptions);
}