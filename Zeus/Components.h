#pragma once

#include <SFML/Graphics.hpp>

#ifndef GAME_COMPONENTS_H
#define GAME_COMPONENTS_H

struct BaseComponent {
	std::string name;
	int entityType;
};

struct RenderComponent {
	sf::Texture* texture;
	sf::Sprite* sprite;
	sf::Vector2i tileSize;
	sf::Vector2i tileStart;
	float scale;
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