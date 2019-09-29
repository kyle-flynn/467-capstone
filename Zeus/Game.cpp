#include <SFML/Graphics.hpp>

#include "MessageBus.h"
#include "TestSystem.h"

#include "TestMessage.h"

#include "World.h"

#include "EntityComponentSystem.h"
#include "Components.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(720, 600), "ZEUS");
	window.setFramerateLimit(60);
	window.setActive();

	// Getting an instance of the message bus and starting its own thread.
	MessageBus mBus = MessageBus::getInstance();
	// mBus.setUpdatesPerSecond(120); // We can also change the updates per second of the message bus.
	mBus.start();

	std::shared_ptr<TestSystem> testSystem = std::make_shared<TestSystem>();

	mBus.addSystem(testSystem);

	std::string test;
	int tiles[4][4] = {
		{6,6,6,6},
		{10,0,0,0},
		{10,0,0,0},
		{10,0,0,0}
	};

	World world(std::string("Resources/Tiles/tileset_grass.png"), tiles, 16, 16);

	sf::Texture playerTexture;
	sf::Sprite playerSprite;
	playerTexture.loadFromFile("Resources/Sprites/spritesheet_link.png");
	playerSprite.setTexture(playerTexture);
	playerSprite.setTextureRect(sf::IntRect(0, 96, 24, 32));

	entt::registry registry;
	auto entity = registry.create();
	registry.assign<HealthComponent>(entity, 10, 10);
	registry.assign<DrawComponent>(entity, playerTexture, playerSprite);
	registry.assign<PositionComponent>(entity, 100.0f, 100.0f);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear(sf::Color::Black);
		world.draw(window);

		auto view = registry.view<DrawComponent, PositionComponent>();
		for (auto entity : view) {
			auto& drawComponent = view.get<DrawComponent>(entity);
			auto& positionComponent = view.get<PositionComponent>(entity);
			drawComponent.sprite.setPosition(positionComponent.x, positionComponent.y);
			window.draw(drawComponent.sprite);
		}

		window.display();
	}

	// Free up all of our variables
	mBus.terminate();

	return 0;
}