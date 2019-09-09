#include <SFML/Window.hpp>

#include "MessageBus.h"

int main()
{
	sf::Window window(sf::VideoMode(720, 600), "ZEUS");
	window.setFramerateLimit(60);

	// Getting an instance of the message bus and starting its own thread.
	MessageBus mBus = MessageBus::getInstance();
	// mBus.setUpdatesPerSecond(120); // We can also change the updates per second of the message bus.
	mBus.start();

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

		window.setActive();
		window.display();
	}

	// Free up all of our variables
	mBus.terminate();

	return 0;
}