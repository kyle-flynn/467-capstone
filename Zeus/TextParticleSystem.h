#pragma once

#include <SFML/Graphics.hpp>
#include "Particle.h"

#ifndef GAME_TEXT_PARTICLE_SYSTEM_H
#define GAME_TEXT_PARTICLE_SYSTEM_H

class TextParticleSystem : public sf::Drawable, public sf::Transformable{
public:
	TextParticleSystem(float minX, float maxX, float minY, float maxY);
	void update(sf::Time elapsed);
private:
	std::vector<Particle> particles;
	sf::VertexArray vertices;
	float minX;
	float maxX;
	float minY;
	float maxY;

	virtual void draw(sf::RenderTarget&, sf::RenderStates states) const;
	void reset(std::size_t index);
};

#endif