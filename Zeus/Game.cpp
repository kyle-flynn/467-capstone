#include <SFML/Window.hpp>

#include "MessageBus.h"
#include "TestSystem.h"

#include "TestMessage.h"

int main()
{
	sf::Window window(sf::VideoMode(720, 600), "ZEUS");
	window.setFramerateLimit(60);

	// Getting an instance of the message bus and starting its own thread.
	MessageBus mBus = MessageBus::getInstance();
	// mBus.setUpdatesPerSecond(120); // We can also change the updates per second of the message bus.
	mBus.start();

	std::shared_ptr<TestSystem> testSystem = std::make_shared<TestSystem>();

	mBus.addSystem(testSystem);

	sf::Clock clock;
	double timeElapsed = 0;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		timeElapsed = clock.getElapsedTime().asSeconds();
		if (timeElapsed >= 1.0) {
			std::shared_ptr<TestMessage> msg = std::make_shared<TestMessage>("Hello, World!");
			mBus.sendMessage(msg);
			clock.restart();
		}

		window.setActive();
		window.display();
	}

	// Free up all of our variables
	mBus.terminate();

	return 0;
}