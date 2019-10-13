#include "Lightning.h"
#include "MathUtils.h"

#include <iostream>

Lightning::Lightning(sf::Vector2f start, sf::Vector2f end) :
	vertices(sf::Quads, 0),
	start(start),
	end(end),
	fadeDuration(1.0f)
{
	this->fadeRate = fadeDuration / 255.0f;
	this->createBolt(6);
	this->timeElapsed = 0;
	if (!this->texture.loadFromFile("Resources/Tiles/tileset_lightning.png")) {
		std::cout << "Error loading texture." << std::endl;
	}
}

Lightning::Lightning(sf::Vector2f start, sf::Vector2f end, float fadeDuration) :
	vertices(sf::Quads, 0),
	start(start),
	end(end),
	fadeDuration(fadeDuration)
{
	this->fadeRate = fadeDuration / 255.0f;
	this->createBolt(6);
	this->timeElapsed = 0;
	if (!this->texture.loadFromFile("Resources/Tiles/tileset_lightning.png")) {
		std::cout << "Error loading texture." << std::endl;
	}
}

void Lightning::update(float deltaTime) {
	this->timeElapsed += deltaTime;
	if (this->timeElapsed <= this->fadeDuration) {
		for (int i = 0; i < this->vertices.getVertexCount(); i++) {
			this->vertices[i].color.a = static_cast<sf::Uint8>(255 - (this->timeElapsed / this->fadeRate));
		}
	}
}

void Lightning::createBolt(float thickness) {
	sf::Vector2f tangent = this->end - this->start;
	sf::Vector2f normal = MathUtils::normalize2f(sf::Vector2f(tangent.y, -tangent.x));
	float length = MathUtils::distance(tangent);
	std::vector<float> positions;

	for (int i = 0; i < length / 4; i++) {
		positions.push_back(static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX));
	}
	std::sort(positions.begin(), positions.end());

	const float sway = 80;
	const float jaggedness = 1 / sway;

	sf::Vector2f prevPoint = this->start;
	float prevDisplacement = 0.0f;

	for (int i = 0; i < positions.size(); i++) {
		float position = positions[i];
		float scale = (length * jaggedness) * (position - positions[(i > 0 ? i : 1) - 1]);
		float envelope = position > 0.95f ? 20 * (1 - position) : 1;
		float displacement = -sway + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (sway + sway)));
		displacement -= (displacement - prevDisplacement) * (1 - scale);
		displacement *= envelope;

		sf::Vector2f point = this->start + (position * tangent) + (displacement * normal);
		/*
		this->vertices.resize(this->vertices.getVertexCount() + 2);
		this->vertices[(i * 2)].position = prevPoint;
		this->vertices[(i * 2)].color = sf::Color(36, 84, 122, 255);
		this->vertices[(i * 2)].texCoords = sf::Vector2f(0.0f, 0.0f);
		this->vertices[(i * 2) + 1].position = point;
		this->vertices[(i * 2) + 1].color = sf::Color(36, 84, 122, 255);
		this->vertices[(i * 2) + 1].texCoords = sf::Vector2f(0.0f, 0.0f);
		*/
		this->createQuad(i, thickness, prevPoint, point);
		prevPoint = point;
		prevDisplacement = displacement;
	}
	/*
	this->vertices.resize(this->vertices.getVertexCount() + 2);
	this->vertices[this->vertices.getVertexCount() - 2].position = prevPoint;
	this->vertices[this->vertices.getVertexCount() - 2].color = sf::Color(36, 84, 122, 255);
	this->vertices[this->vertices.getVertexCount() - 1].position = this->end;
	this->vertices[this->vertices.getVertexCount() - 1].color = sf::Color(36, 84, 122, 255);
	*/
}

void Lightning::createQuad(std::size_t index, float thickness, sf::Vector2f lineStart, sf::Vector2f lineEnd) {
	float transStart = std::cos(3.14f / 180.0f * 45.0f) * (thickness / 2);
	float transEnd = std::sinf(3.14f / 180.0f * 45.0f) * (thickness / 2);

	sf::Vector2f topLeft(lineStart.x - transStart, lineStart.y + transStart);
	sf::Vector2f topRight(lineStart.x + transStart, lineStart.y - transStart);
	sf::Vector2f botRight(lineEnd.x + transEnd, lineEnd.y - transEnd);
	sf::Vector2f botLeft(lineEnd.x - transEnd, lineEnd.y + transEnd);

	this->vertices.resize(this->vertices.getVertexCount() + 4);
	this->createPoint((index * 4), topLeft, 0.0f, 0.0f);
	this->createPoint((index * 4) + 1, topRight, 16.0f, 0.0f);
	this->createPoint((index * 4) + 2, botRight, 16.0f, 16.0f);
	this->createPoint((index * 4) + 3, botLeft, 0.0f, 16.0f);
}

void Lightning::createPoint(std::size_t index, sf::Vector2f point, float tileX, float tileY) {
	this->vertices[index].position = point;
	//this->vertices[index].color = sf::Color(36, 84, 122, 255);
	this->vertices[index].texCoords = sf::Vector2f(tileX, tileY);
}

void Lightning::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = &this->texture;
	target.draw(this->vertices, states);
}

bool Lightning::complete() {
	return this->timeElapsed >= this->fadeDuration;
}

void Lightning::reset(sf::Vector2f start, sf::Vector2f end) {
	this->start = start;
	this->end = end;
	this->vertices.clear();
	this->fadeDuration = 1.0f;
	this->createBolt(8);
	this->timeElapsed = 0;
}

void Lightning::reset(sf::Vector2f start, sf::Vector2f end, float fadeDuration) {
	this->start = start;
	this->end = end;
	this->vertices.clear();
	this->fadeDuration = fadeDuration;
	this->createBolt(8);
	this->timeElapsed = 0;
}