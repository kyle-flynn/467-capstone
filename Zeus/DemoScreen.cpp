#include "DemoScreen.h"
#include "MainMenuScreen.h"

#include <iostream>

DemoScreen::DemoScreen() {
	Screen();
	entt::registry& registry = GameDataManager::getInstance().getRegistry();
	sf::Texture* texture = new sf::Texture();
	texture->loadFromFile("Resources/Sprites/spritesheet_link.png");
	sf::Sprite* sprite = new sf::Sprite();
	sprite->setTexture(*texture);
	sprite->setTextureRect(sf::IntRect(0, 96, 24, 32));
	auto entt = registry.create();
	registry.assign<RenderComponent>(entt, texture, sprite);
	registry.assign<PositionComponent>(entt, 500.0f, 500.0f, 5.0f, 500.0f, 500.0f);
}

void DemoScreen::update(float deltaTime) {
	entt::registry& registry = GameDataManager::getInstance().getRegistry();
	auto view = registry.view<PositionComponent>();
	for (auto entity : view) {
		auto& pos = registry.get<PositionComponent>(entity);
		std::cout << pos.x << " " << pos.y << std::endl;
		std::cout << pos.destX << " " << pos.destY << std::endl;
		if (pos.x != pos.destX) {
			if (pos.x < pos.destX) {
				if (pos.x + pos.speed < pos.destX) {
					pos.x += pos.speed;
				}
				else {
					pos.x = pos.destX;
				}
			}
			else {
				if (pos.x - pos.speed > pos.destX) {
					pos.x -= pos.speed;
				}
				else {
					pos.x = pos.destX;
				}
			}
		}
		if (pos.y != pos.destY) {
			if (pos.y < pos.destY) {
				if (pos.y + pos.speed < pos.destY) {
					pos.y += pos.speed;
				}
				else {
					pos.y = pos.destY;
				}
			}
			else {
				if (pos.y - pos.speed > pos.destY) {
					pos.y -= pos.speed;
				}
				else {
					pos.y = pos.destY;
				}
			}
		}
	}
}

void DemoScreen::update(sf::Event event) {
	if (event.type == sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Button::Right) {
		entt::registry& reg = GameDataManager::getInstance().getRegistry();
		auto view = reg.view<PositionComponent>();
		for (auto entity : view) {
			auto& pos = reg.get<PositionComponent>(entity);
			pos.destX = mousePosition.x;
			pos.destY = mousePosition.y;
		}
	}
	if (event.type == sf::Event::KeyPressed) {
		entt::registry& reg = GameDataManager::getInstance().getRegistry();
		auto view = reg.view<PositionComponent>();
		for (auto entity : view) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
				auto& pos = reg.get<PositionComponent>(entity);
				pos.speed += 1.0f;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
				auto& pos = reg.get<PositionComponent>(entity);
				if (pos.speed > 1.0) {
					pos.speed -= 1.0f;
				}
			}
		}
	}
}

void DemoScreen::draw(sf::RenderWindow& window) {
	mousePosition = sf::Mouse::getPosition(window);
	entt::registry& reg = GameDataManager::getInstance().getRegistry();
	auto view = reg.view<RenderComponent>();
	for (auto entity : view) {
		auto& rend = reg.get<RenderComponent>(entity);
		auto& pos = reg.get<PositionComponent>(entity);
		rend.sprite->setPosition(pos.x, pos.y);
		rend.sprite->setScale(3.0f, 3.0f);
		window.draw(*rend.sprite);
	}
}

void DemoScreen::handleEvent(sf::Event event) {
	if (event.type == event.TextEntered &&
		event.text.unicode == 27) {
		ScreenManager::getInstance().setScreen(new MainMenuScreen());
	}
	update(event);
}

void DemoScreen::drawSprites() {
}
