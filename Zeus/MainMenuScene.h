#pragma once

#include "Scene.h"
#include "MenuOption.h"

#ifndef GAME_MAIN_MENU_SCENE_H
#define GAME_MAIN_MENU_SCENE_H

class MainMenuScene : public Scene {
public:
	MainMenuScene();
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);

	bool hasSelected;
	unsigned int selectedId;
private:
	sf::Vector2i mousePosition;

	MenuOption optionCampaignEditor;
	MenuOption optionCreateSession;
	MenuOption optionJoinSession;
	MenuOption optionOptions;
};

#endif