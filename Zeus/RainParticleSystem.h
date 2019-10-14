#pragma once

#include <SFML/Graphics.hpp>
#include "Particle.h"

#ifndef GAME_RAIN_PARTICLE_SYSTEM_H
#define GAME_RAIN_PARTICLE_SYSTEM_H

class RainParticleSystem : public sf::Drawable, public sf::Transformable {
public:
	RainParticleSystem(float minX, float maxX, float minY, float maxY);
	void update(float deltaTime);
private:
	std::vector<Particle> particles;
	sf::VertexArray vertices;
	float minX;
	float maxX;
	float minY;
	float maxY;

	virtual void draw(sf::RenderTarget&, sf::RenderStates states) const;
	void resetParticle(std::size_t index);
};

#endif