#include "SnowParticleSystem.h"

SnowParticleSystem::SnowParticleSystem(float minX, float maxX, float minY, float maxY) :
	particles(500),
	vertices(sf::Points, 500),
	minX(minX),
	maxX(maxX),
	minY(minY),
	maxY(maxY)
{
	// Initialize all particles with random x and y coordinates.
	for (std::size_t i = 0; i < this->particles.size(); ++i) {
		Particle& p = this->particles[i];
		float speedY = 50.0f + (std::rand() % 5);
		float x = (std::rand() % int(this->maxX));
		float y = (std::rand() % int(this->maxY));
		p.velocity = sf::Vector2f(0, speedY);
		p.lifetime = sf::seconds((this->maxY - y) / p.velocity.y);
		this->vertices[i].position = sf::Vector2f(x, y);
	}
}

void SnowParticleSystem::update(sf::Time elapsed) {
	for (std::size_t i = 0; i < this->particles.size(); ++i) {
		Particle& p = this->particles[i];
		p.lifetime -= elapsed;

		if (p.lifetime <= sf::Time::Zero) {
			this->resetParticle(i);
		}

		this->vertices[i].position += p.velocity * elapsed.asSeconds();
		this->vertices[i].color = sf::Color(218, 228, 255, 127);
	}
}

void SnowParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = NULL;
	target.draw(this->vertices, states);
}

void SnowParticleSystem::resetParticle(std::size_t index) {
	// Setting up the particle to be at an angle of -90deg at a speed of 50f + rand(25)
	Particle& p = this->particles[index];
	float speedY = 50.0f + (std::rand() % 5);
	p.velocity = sf::Vector2f(0, speedY);
	// Since we're using GL_POINTS - setup 2 vertices (a line) for raindrops.
	// Their heights will also be slightly varied.
	float x = (std::rand() % int(this->maxX));
	p.lifetime = sf::seconds(this->maxY / p.velocity.y);
	this->vertices[index].position = sf::Vector2f(x, 0.0f);
}