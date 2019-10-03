#include "LightningSystem.h"

LightningSystem::LightningSystem(float minX, float maxX, float minY, float maxY) :
	particles(50),
	vertices(sf::Lines, 2), // Starting size. This can be resized later.
	minX(minX),
	maxX(maxX),
	minY(minY),
	maxY(maxY)
{
	
}

void LightningSystem::update(sf::Time elapsed) {}

void LightningSystem::draw(sf::RenderTarget&, sf::RenderStates states) const {}

void LightningSystem::resetParticle(std::size_t index) {}