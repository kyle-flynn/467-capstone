#pragma once 

#include "Screen.h"
#include "Game.h"
#include "GameDataManager.h"
#include "Components.h"

class DemoScreen :public Screen {

public:
	DemoScreen();
	void update(float deltaTime);
	void update(sf::Event event);
	void draw(sf::RenderWindow& window);
	void handleEvent(sf::Event event);

private:
	sf::Vector2i mousePosition;
	void drawSprites();
};

