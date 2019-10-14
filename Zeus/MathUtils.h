#pragma once

#include <SFML/Graphics.hpp>

#ifndef ZEUS_MATH_UTILS_H
#define ZEUS_MATH_UTILS_H

class MathUtils {
public:
	static sf::Vector2f normalize2f(sf::Vector2f v) {
		float distance = std::sqrtf(std::powf(v.x, 2.0f) + std::powf(v.y, 2.0f));
		return sf::Vector2f(v.x / distance, v.y / distance);
	};

	static float distance(sf::Vector2f v) {
		return std::sqrtf(std::powf(v.x, 2.0f) + std::powf(v.y, 2.0f));
	};
};

#endif