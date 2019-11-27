#pragma once

#include "Screen.h"
#include "Game.h"
#include "Player.h"

class DemoScreen :public Screen {

public :
	DemoScreen();
	void update(float deltaTime);
	void update(sf::Event event);
	void draw(sf::RenderWindow& window);
	void handleEvent(sf::Event event);
	sf::Vector2i mousePosition;
};

