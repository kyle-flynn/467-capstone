#pragma once

#include <SFML/Graphics.hpp>
#include "Screen.h"

#ifndef GAME_SCENE_H
#define GAME_SCENE_H

class Scene {
public:
	Scene();
	virtual void update(float deltaTime);
	virtual void draw(sf::RenderWindow& window);
};

#endif