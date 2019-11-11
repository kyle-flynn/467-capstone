#pragma once

#include "Screen.h"
#include "World.h"

#ifndef GAME_GAMEPLAY_SCREEN_H
#define GAME_GAMEPLAY_SCREEN_H

class GameplayScreen : public Screen {
public:
	GameplayScreen(int &shptr, int **tileVals);
	//void update(float deltaTime);
	void draw(sf::RenderWindow& window);

	World* world;
};

#endif