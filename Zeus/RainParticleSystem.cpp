#include "RainParticleSystem.h"

RainParticleSystem::RainParticleSystem(float minX, float maxX, float minY, float maxY) :
	particles(50),
	vertices(sf::Lines, 50 * 2),
	minX(minX),
	maxX(maxX),
	minY(minY),
	maxY(maxY)
{
	// Initialize all particles with random x and y coordinates.
	for (std::size_t i = 0; i < this->particles.size(); ++i) {
		Particle& p = this->particles[i];
		float speedY = 600.0f + (std::rand() % 25);
		float speedX = 100.0f + (std::rand() % 25);
		float angle = 3.14f / 180.0f * (-250.0f + (std::rand() % 10));
		float x = (std::rand() % int(this->maxX));
		float y = (std::rand() % int(this->maxY));
		p.velocity = sf::Vector2f(std::cos(angle) * speedX, speedY);
		p.lifetime = sf::seconds((this->maxY - y) / p.velocity.y);
		this->vertices[i * 2].position = sf::Vector2f(x, y);
		this->vertices[(i * 2) + 1].position = sf::Vector2f(x - (std::rand() % 5) - 5.0f, y + (std::rand() % 8) + 100.0f);
	}
}

void RainParticleSystem::update(float deltaTime) {
	for (std::size_t i = 0; i < this->particles.size(); ++i) {
		Particle& p = this->particles[i];
		p.lifetime -= sf::seconds(deltaTime);

		if (p.lifetime <= sf::Time::Zero) {
			this->resetParticle(i);
		}

		this->vertices[i * 2].position += p.velocity * deltaTime;
		this->vertices[i * 2].color = sf::Color(218, 228, 255, 127);
		this->vertices[(i * 2) + 1].position += p.velocity * deltaTime;
		this->vertices[(i * 2) + 1].color = sf::Color(218, 228, 255, 127);
	}
}

void RainParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = NULL;
	target.draw(this->vertices, states);
}

void RainParticleSystem::resetParticle(std::size_t index) {
	// Setting up the particle to be at an angle of -90deg at a speed of 50f + rand(25)
	Particle& p = this->particles[index];
	float speedY = 600.0f + (std::rand() % 25);
	float speedX = 100.0f + (std::rand() % 25);
	float angle = 3.14f / 180.0f * (-250.0f + (std::rand() % 10));
	p.velocity = sf::Vector2f(std::cos(angle) * speedX, speedY);
	// Since we're using GL_POINTS - setup 2 vertices (a line) for raindrops.
	// Their heights will also be slightly varied.
	float x = (std::rand() % int(this->maxX));
	p.lifetime = sf::seconds(this->maxY / p.velocity.y);
	this->vertices[index * 2].position = sf::Vector2f(x, 0.0f);
	this->vertices[(index * 2) + 1].position = sf::Vector2f(x - (std::rand() % 5) - 5.0f, (std::rand() % 8) + 100.0f);
}