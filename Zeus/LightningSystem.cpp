#include <random>
#include "LightningSystem.h"

LightningSystem::LightningSystem(float minX, float maxX, float minY, float maxY) :
	minX(minX),
	maxX(maxX),
	minY(minY),
	maxY(maxY)
{
	for (int i = 0; i < 10; i++) {
		float startX = (std::rand() % int(this->maxX));
		float startY = minY;
		std::random_device rand;
		std::mt19937 engine(rand());
		std::uniform_int_distribution<> distributionX(startX - 15, startX + 15);
		std::uniform_int_distribution<> distributionY(startY + 300, startY + 600);
		std::uniform_int_distribution<> distributionDur(10, 20);
		float endX = float(distributionX(engine));
		float endY = float(distributionY(engine));
		float duration = distributionDur(engine) / 10.0f;
		this->lightningBolts.push_back(Lightning(sf::Vector2f(startX, startY), sf::Vector2f(endX, endY), duration));
	}
}

void LightningSystem::update(float deltaTime) {
	for (int i = 0; i < this->lightningBolts.size(); i++) {
		this->lightningBolts[i].update(deltaTime);
		if (this->lightningBolts[i].complete()) {
			this->resetLightningBolt(i);
		}
	}
}

void LightningSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = NULL;
	for (auto lightningBolt : this->lightningBolts) {
		target.draw(lightningBolt, states);
	}
}

void LightningSystem::resetLightningBolt(std::size_t index) {
	float startX = (std::rand() % int(this->maxX));
	float startY = minY;
	std::random_device rand;
	std::mt19937 engine(rand());
	std::uniform_int_distribution<> distributionX(startX - 15, startX + 15);
	std::uniform_int_distribution<> distributionY(startY + 300, startY + 600);
	std::uniform_int_distribution<> distributionDur(10, 20);
	float endX = float(distributionX(engine));
	float endY = float(distributionY(engine));
	float duration = distributionDur(engine) / 10.0f;
	this->lightningBolts[index].reset(sf::Vector2f(startX, startY), sf::Vector2f(endX, endY), duration);
}