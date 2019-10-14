#pragma once

#include "Game.h"
#include "Screen.h"

#include "LightningSystem.h"
#include "TextParticleSystem.h"

#include "MainMenuScene.h"
#include "MenuOption.h"

#include "ScreenManager.h"
#include "GameplayScreen.h"

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

	MainMenuScene mainScene;
};

#endif;