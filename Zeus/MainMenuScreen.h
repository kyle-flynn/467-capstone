#pragma once

#include "Game.h"
#include "Screen.h"

#include "LightningSystem.h"
#include "TextParticleSystem.h"

#include "MainMenuScene.h"
#include "MenuOption.h"

#include "ScreenManager.h"
#include "GameplayScreen.h"

#include "EditorText.h"

#ifndef GAME_MAIN_MENU_SCREEN_H
#define GAME_MAIN_MENU_SCREEN_H

class MainMenuScreen : public Screen {
public:
	MainMenuScreen();
	void update(float deltaTime);
	void update(sf::Event event);
	void handleEvent(sf::Event event);
	void draw(sf::RenderWindow& window);
private:
	LightningSystem lightningSystem;
	TextParticleSystem titleTextSystem;
	sf::Texture zeusTexture;
	sf::Sprite zeusSprite;

	MainMenuScene mainScene;

	sf::Rect<float> combatBounds, movementBounds;
	EditorText characterEditor = EditorText(sf::String("")),
		monsterEditor = EditorText(sf::String("")),
		itemEditor = EditorText(sf::String("")),
		dialogueEditor = EditorText(sf::String(""));
	sf::Vector2i mousePosition;
};

#endif;