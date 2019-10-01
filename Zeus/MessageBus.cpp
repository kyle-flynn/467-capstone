#include "MessageBus.h"

MessageBus::MessageBus() {
	this->running = false;
	this->messages = {};
	this->systems = {};
	this->ups = 60;
}

MessageBus& MessageBus::getInstance() {
	static MessageBus instance;
	return instance;
}

void MessageBus::start() {
	MessageBus::getInstance().running = true;
	std::thread messageThread([=]() {
		MessageBus::getInstance().poll();
	});
	messageThread.detach();
}

void MessageBus::terminate() {
	MessageBus::getInstance().running = false;
}

void MessageBus::setUpdatesPerSecond(double updates) {
	MessageBus::getInstance().ups = updates;
}

void MessageBus::sendMessage(Message* message) {
	MessageBus::getInstance().messages.push(message);
}

void MessageBus::addSystem(System* system) {
	MessageBus::getInstance().systems.push_back(system);
}

void MessageBus::poll() {
	//std::cout << "MessageBus now polling." << std::endl;
	sf::Clock clock;

	float accumulator = 0.0;
	float currTime = 0.0;
	float totalTime = 0.0;
	float lastTime = 0.0;

	int updates = 0;

	while (MessageBus::running) {
		lastTime = currTime;
		currTime = clock.getElapsedTime().asSeconds();
		float timeElapsed = currTime - lastTime;

		if (timeElapsed > 0.25) {
			timeElapsed = 0.25;
		}

		accumulator += timeElapsed;

		// std::this_thread::sleep_for(std::chrono::milliseconds(5));

		while (accumulator >= (1 / MessageBus::getInstance().ups)) {
			while (!MessageBus::getInstance().messages.empty()) {
				int count = 0;
				for (System* system : MessageBus::getInstance().systems) {
					system->receiveMessage(MessageBus::getInstance().messages.front());
				}
				MessageBus::getInstance().messages.pop();
			}
			totalTime += (1 / MessageBus::getInstance().ups);
			accumulator -= (1 / MessageBus::getInstance().ups);
			updates++;
		}
		
		if (totalTime >= 1.0f) {	
			// std::cout << updates << " updates" << std::endl;
			totalTime = 0.0f;
			updates = 0;
		}
	}
}