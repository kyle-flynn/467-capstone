#pragma once

#include <SFML/Graphics.hpp>

#include "EntityComponentSystem.h"
#include "Character.h"
#include "Monster.h"

#ifndef GAME_COMPONENTS_H
#define GAME_COMPONENTS_H

// Classes For Certain Components
struct Move {
	std::string name;
	std::string description;
	int damage;
};

struct Action {
	int order;
	Move move;
	entt::entity entity;
};

// Components
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

struct MovesetComponent {
	std::vector<Move> moves;
};

struct PlayerComponent {
	std::string playerName;
};

struct CharacterComponent {
	Character character;
};

struct MonsterComponent {
	Monster monster;
};

#endif