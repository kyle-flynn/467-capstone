#include "TextParticleSystem.h"

TextParticleSystem::TextParticleSystem(float minX, float maxX, float minY, float maxY) : 
	minX(minX),
	maxX(maxX),
	minY(minY),
	maxY(maxY)
{
	
}

void TextParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = NULL;
}