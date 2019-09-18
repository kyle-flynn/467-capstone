#include <SFML/Graphics.hpp>

#include "MessageBus.h"
#include "TestSystem.h"

#include "TestMessage.h"

#include "World.h"
#include "Entity.h"
#include "Component.h"
#include "HealthComponent.h"

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
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0}
	};

	World world(std::string("Resources/Tiles/tileset_grass.png"), tiles, 16, 16);

	Entity player;
	HealthComponent health(4, 4);
	player.addComponent(health);
	
	HealthComponent* c = (HealthComponent*) player.getComponent(1);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear(sf::Color::Black);
		world.draw(window);
		window.display();
	}

	// Free up all of our variables
	mBus.terminate();

	return 0;
}