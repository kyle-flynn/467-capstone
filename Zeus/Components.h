#pragma once

#include <SFML/Graphics.hpp>

#ifndef GAME_COMPONENTS_H
#define GAME_COMPONENTS_H

struct BaseComponent {
	std::string name;
};

struct RenderComponent {
	sf::Texture texture;
	sf::Sprite sprite;
	int tileSizeX;
	int tileSizeY;
	int tileStartX;
	int tileStartY;
};

struct HealthComponent {
	int hitpoints;
	int maxHitpoints;
};

struct PositionComponent {
	float x;
	float y;
};

struct CombatComponent {
	int speed;
};

#endif