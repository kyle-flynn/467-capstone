#pragma once

#include <SFML/Graphics.hpp>
#include "Particle.h"

#ifndef GAME_TEXT_PARTICLE_SYSTEM_H
#define GAME_TEXT_PARTICLE_SYSTEM_H

class TextParticleSystem : public sf::Drawable, public sf::Transformable{
public:
	TextParticleSystem(float minX, float maxX, float minY, float maxY, float xOff, float yOff, float time, const std::string& text);
	void update(float deltaTime);
	bool isComplete();
private:
	std::vector<Particle> particles;
	sf::VertexArray vertices;
	float minX;
	float maxX;
	float minY;
	float maxY;
	float time;
	float elapsedTime;

	sf::Text goalText;
	sf::RenderTexture textRenderTexture;
	sf::Texture textTexture;
	sf::Image textImage;

	virtual void draw(sf::RenderTarget&, sf::RenderStates states) const;
	void createPixels(float xOffset, float yOffset);
	void reset(std::size_t index);
};

#endif