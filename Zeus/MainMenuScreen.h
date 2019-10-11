#pragma once

#include "Game.h"
#include "Screen.h"

#include "LightningSystem.h"
#include "TextParticleSystem.h"

#include "MenuOption.h"

#ifndef GAME_MAIN_MENU_SCREEN_H
#define GAME_MAIN_MENU_SCREEN_H

class MainMenuScreen : public Screen {
public:
	MainMenuScreen();
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
private:
	LightningSystem lightningSystem;
	TextParticleSystem titleTextSystem;
	sf::Texture zeusTexture;
	sf::Sprite zeusSprite;

	MenuOption optionCampaignEditor;
	MenuOption optionCreateSession;
	MenuOption optionJoinSession;
	MenuOption optionOptions;
};

#endif;