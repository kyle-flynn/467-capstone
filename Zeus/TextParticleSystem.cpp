#include "TextParticleSystem.h"
#include "FontManager.h"

#include <iostream>

TextParticleSystem::TextParticleSystem(float minX, float maxX, float minY, float maxY, float xOff, float yOff, float time, const std::string& text) : 
	minX(minX),
	maxX(maxX),
	minY(minY),
	maxY(maxY),
	time(time),
	vertices(sf::Points, 0)
{
	this->goalText.setFont(FontManager::getInstance().oldStandard);
	this->goalText.setCharacterSize(128);
	this->goalText.setString(text);
	this->createPixels(xOff, yOff);
}

void TextParticleSystem::createPixels(float xOffset, float yOffset) {
	sf::Vector2f dimensions = sf::Vector2f(this->goalText.getLocalBounds().width, this->goalText.getLocalBounds().height);
	this->textRenderTexture.create(dimensions.x * 1.5, dimensions.y * 1.5);
	this->textRenderTexture.clear();
	this->textRenderTexture.draw(this->goalText);
	this->textRenderTexture.display();
	this->textTexture = this->textRenderTexture.getTexture();
	this->textImage = this->textTexture.copyToImage();
	sf::Vector2u size = this->textImage.getSize();
	int count = 0;
	for (int y = 0; y < size.y; y++) {
		for (int x = 0; x < size.x; x++) {
			if ((int)this->textImage.getPixel(x, y).b > 30) {
				Particle p;
				p.source = sf::Vector2f((std::rand() % (int)maxX), (std::rand() % (int)maxY));
				p.destination = sf::Vector2f(x + xOffset, y + yOffset);
				p.velocity = (p.destination - p.source) / time;
				this->particles.push_back(p);
				this->vertices.resize(this->vertices.getVertexCount() + 1);
				this->vertices[count].position = p.source;
				this->vertices[count].color = sf::Color(13, 64, 192);
				count++;
			}
		}
	}
}

void TextParticleSystem::update(float deltaTime) {
	this->elapsedTime += deltaTime;
	if (this->elapsedTime <= time) {
		for (int i = 0; i < this->vertices.getVertexCount(); i++) {
			this->vertices[i].position += this->particles[i].velocity * deltaTime;
		}
	}
}

void TextParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = NULL;
	//target.draw(this->goalText);
	target.draw(this->vertices, states);
}

bool TextParticleSystem::isComplete() {
	return this->elapsedTime > this->time;
}