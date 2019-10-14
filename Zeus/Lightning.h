#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#ifndef GAME_LIGHTNING_H
#define GAME_LIGHTNING_H

class Lightning : public sf::Drawable, public sf::Transformable {
public:
	Lightning(sf::Vector2f start, sf::Vector2f end);
	Lightning(sf::Vector2f start, sf::Vector2f end, float fadeDuration);
	bool complete();
	void update(float deltaTime);
	void reset(sf::Vector2f start, sf::Vector2f end);
	void reset(sf::Vector2f start, sf::Vector2f end, float fadeDuration);
private:
	sf::VertexArray vertices;
	sf::Vector2f start;
	sf::Vector2f end;
	float fadeDuration;
	float fadeRate;
	float timeElapsed;
	sf::Texture texture;

	void createBolt(float thickness);
	void createQuad(std::size_t index, float thickness, sf::Vector2f lineStart, sf::Vector2f lineEnd);
	void createPoint(std::size_t index, sf::Vector2f point, float tileX, float tileY);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif