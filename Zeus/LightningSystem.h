#pragma once

#include <SFML/Graphics.hpp>
#include "Lightning.h"

#ifndef GAME_LIGHTNING_SYSTEM_H
#define GAME_LIGHTNING_SYSTEM_H

class LightningSystem : public sf::Drawable, public sf::Transformable {
public:
	LightningSystem(float minX, float maxX, float minY, float maxY);
	void update(float deltaTime);
private:
	std::vector<Lightning> lightningBolts;
	float minX;
	float maxX;
	float minY;
	float maxY;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void resetLightningBolt(std::size_t index);
};

#endif