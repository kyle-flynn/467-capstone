#include <SFML/Graphics.hpp>

#include "Game.h"

#include "ScreenManager.h"
#include "GameplayScreen.h"
#include "MainMenuScreen.h"

#include "MessageBus.h"
#include "LoggingSystem.h"

const float Game::WIDTH = 1280.0f;
const float Game::HEIGHT = 720.0f;

int main() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "ZEUS");
	window.setFramerateLimit(60);
	window.setActive();

	// Getting an instance of the message bus and starting its own thread.
	MessageBus mBus = MessageBus::getInstance();
	// mBus.setUpdatesPerSecond(120); // We can also change the updates per second of the message bus.
	mBus.start();

	LoggingSystem* logger = new LoggingSystem();

	mBus.addSystem(logger);

	/*
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
	*/

	//ScreenManager::getInstance().setScreen(new MainMenuScreen());
	ScreenManager::getInstance().setScreen(new GameplayScreen());

	LogData* logData = new LogData();
	logData->level = LogLevel::INFO;
	logData->msg = std::string("Hello World!");
	LogMessage* log = new LogMessage(logData);
	mBus.sendMessage(log);

	sf::Clock clock;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		float deltaTime = clock.restart().asSeconds();
		ScreenManager::getInstance().update(deltaTime);

		window.clear(sf::Color::Black);
		ScreenManager::getInstance().draw(window);
		/*
		auto view = registry.view<DrawComponent, PositionComponent>();
		for (auto entity : view) {
			auto& drawComponent = view.get<DrawComponent>(entity);
			auto& positionComponent = view.get<PositionComponent>(entity);
			drawComponent.sprite.setPosition(positionComponent.x, positionComponent.y);
			window.draw(drawComponent.sprite);
		}
		*/
		window.display();
	}

	// Free up all of our variables
	mBus.terminate();

	return 0;
}