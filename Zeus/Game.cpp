#include <SFML/Graphics.hpp>

#include "ScreenManager.h"
#include "GameplayScreen.h"
#include "MainMenuScreen.h"

#include "MessageBus.h"
#include "TestSystem.h"

#include "TestMessage.h"

#include "World.h"

#include "EntityComponentSystem.h"
#include "Components.h"

#include "SnowParticleSystem.h"

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

	ScreenManager::getInstance().setScreen(new MainMenuScreen());
	// ScreenManager::getInstance().setScreen(new GameplayScreen());

	SnowParticleSystem particles(0, 720.0f, 0, 600.0f);
	sf::Clock clock;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		sf::Time elapsed = clock.restart();
		particles.update(elapsed);

		window.clear(sf::Color::Black);
		ScreenManager::getInstance().draw(window);

		auto view = registry.view<DrawComponent, PositionComponent>();
		for (auto entity : view) {
			auto& drawComponent = view.get<DrawComponent>(entity);
			auto& positionComponent = view.get<PositionComponent>(entity);
			drawComponent.sprite.setPosition(positionComponent.x, positionComponent.y);
			window.draw(drawComponent.sprite);
		}
		window.draw(particles);
		window.display();
	}

	// Free up all of our variables
	mBus.terminate();

	return 0;
}