#include "MainMenuScene.h"

MainMenuScene::MainMenuScene() : 
	Scene(),
	optionCampaignEditor("Campaign Editor", false),
	optionCreateSession("Create Session", false),
	optionJoinSession("Join Session", false),
	optionOptions("Options", false)
{
	this->optionCampaignEditor.setPosition(100.0f, 225.0f);
	this->optionCreateSession.setPosition(100.0f, 275.0f);
	this->optionJoinSession.setPosition(100.0f, 325.0f);
	this->optionOptions.setPosition(100.0f, 375.0f);
}

void MainMenuScene::update(float deltaTime) {
	this->optionCampaignEditor.update(deltaTime, this->mousePosition);
	this->optionCreateSession.update(deltaTime, this->mousePosition);
	this->optionJoinSession.update(deltaTime, this->mousePosition);
	this->optionOptions.update(deltaTime, this->mousePosition);

	if (this->optionCampaignEditor.isSelected) {
		this->selectedId = 0;
	} else if (this->optionCreateSession.isSelected) {
		this->selectedId = 1;
	} else if (this->optionJoinSession.isSelected) {
		this->selectedId = 2;
	} else if (this->optionOptions.isSelected) {
		this->selectedId = 3;
	} else {
		this->selectedId = -1;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		this->hasSelected = true;
	} else {
		this->hasSelected = false;
	}
}

void MainMenuScene::draw(sf::RenderWindow& window) {
	this->mousePosition = sf::Mouse::getPosition(window);

	window.draw(this->optionCampaignEditor);
	window.draw(this->optionCreateSession);
	window.draw(this->optionJoinSession);
	window.draw(this->optionOptions);
}