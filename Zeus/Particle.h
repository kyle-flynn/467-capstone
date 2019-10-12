#pragma once

#include <SFML/Graphics.hpp>

#ifndef GAME_PARTICLE_H
#define GAME_PARTICLE_H

struct Particle {
	sf::Vector2f velocity;
	sf::Time lifetime;
	sf::Vector2f source;
	sf::Vector2f destination;
};

#endif