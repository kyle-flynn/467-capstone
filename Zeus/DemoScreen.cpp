#include "DemoScreen.h"

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
	registry.assign<PositionComponent>(entt, 500.0f, 500.0f);
}

void DemoScreen::update(float deltaTime) {
	entt::registry& registry = GameDataManager::getInstance().getRegistry();
	auto view = registry.view<PositionComponent>();
	for (auto entity : view) {
		auto& pos = registry.get<PositionComponent>(entity);

	}
}

void DemoScreen::update(sf::Event event) {
	if (event.type == sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Button::Right) {
		entt::registry& reg = GameDataManager::getInstance().getRegistry();
		auto view = reg.view<PositionComponent>();
		for (auto entity : view) {
			auto& pos = reg.get<PositionComponent>(entity);
			pos.x = mousePosition.x;
			pos.y = mousePosition.y;
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
		window.draw(*rend.sprite);
	}
}

void DemoScreen::handleEvent(sf::Event event) {
	update(event);
}

void DemoScreen::drawSprites() {
}
