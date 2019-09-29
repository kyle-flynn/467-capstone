#pragma once

#include "SFML/Graphics.hpp"

#ifndef GAME_COMPONENTS_H
#define GAME_COMPONENTS_H

struct DrawComponent {
	sf::Texture texture;
	sf::Sprite sprite;
};

struct HealthComponent {
	int hitpoints;
	int maxHitpoints;
};

struct PositionComponent {
	float x;
	float y;
};

#endif