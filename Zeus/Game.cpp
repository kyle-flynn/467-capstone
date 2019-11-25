#include <SFML/Graphics.hpp>

#include "Game.h"

#include "FontManager.h"

#include "ScreenManager.h"
#include "GameplayScreen.h"
#include "MainMenuScreen.h"
#include "CombatScreen.h"
#include "DialogueEditorScreen.h"
#include "ItemEditorScreen.h"
#include "CharacterEditorScreen.h"
#include "DemoScreen.h"

#include "MessageBus.h"
#include "LoggingSystem.h"

#include <TGUI/TGUI.hpp>
// Seans additions
/*
#include <iostream>
#include "UserInputField.h"
#include "Button.h"
#include "Title.h"
#include "DynamicText.h"
#include "DynamicText2.h"
*/

const float Game::WIDTH = 1280.0f;
const float Game::HEIGHT = 720.0f;
static tgui::Gui gui;

int main() {
	FontManager::getInstance().loadFonts();
	GameDataManager::getInstance();

	sf::RenderWindow window(sf::VideoMode(1280, 720), "ZEUS");
	window.setFramerateLimit(60);
	window.setActive();
	
	gui.setTarget(window);

	//ScreenManager::getInstance().setScreen(new DialogueEditorScreen());
	//gui.add(DialogueEditorPanel::getInstance().getPanel(), "DialogueEditorPanel");
	// Getting an instance of the message bus and starting its own thread.
	MessageBus mBus = MessageBus::getInstance();
	// mBus.setUpdatesPerSecond(120); // We can also change the updates per second of the message bus.
	mBus.start();

	LoggingSystem* logger = new LoggingSystem();

	mBus.addSystem(logger);

	window.setKeyRepeatEnabled(true);
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

	//ScreenManager::getInstance().setScreen(new DemoScreen());
	//ScreenManager::getInstance().setScreen(new CharacterEditorScreen());
	//ScreenManager::getInstance().setScreen(new ItemEditorScreen());
	ScreenManager::getInstance().setScreen(new MainMenuScreen());
	//ScreenManager::getInstance().setScreen(new GameplayScreen());
	//ScreenManager::getInstance().setScreen(new CombatScreen());
	//ScreenManager::getInstance().setScreen(new DialogueEditorScreen());

	//LogData* logData = new LogData();
	//logData->level = LogLevel::INFO;
	//logData->msg = std::string("Hello World!");
	//LogMessage* log = new LogMessage(logData);
	//mBus.sendMessage(log);

	sf::Clock clock;
	bool gameplayScreenActive = false;
	GameplayScreen gp = GameplayScreen::GameplayScreen();

	while (window.isOpen()) {
		sf::Event event;
		int key = 0;
		if (typeid(ScreenManager::getInstance().getScreen()) == typeid(GameplayScreen)) {
			gameplayScreenActive = true;
			//gp = ScreenManager::getInstance().getScreen();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
				key = 1;
				gp.specialKeyPressed(key);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				key = 2;
				gp.specialKeyPressed(key);
			}
			//std::cout << "Gameplay screen active\n";
		}
		else {
			gameplayScreenActive = false;
		}
		
		while (window.pollEvent(event)) {
			if (gameplayScreenActive == false) {
				switch (event.type) {
				case sf::Event::Closed:
					window.close();
				}
				gui.handleEvent(event);
				ScreenManager::getInstance().handleEvent(event);
			}
			else {
				GameplayScreen g1;
				g1.eventLogic(event, window);
			}

		}
		if (gameplayScreenActive == false) {
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
			if (typeid(ScreenManager::getInstance().getScreen()) == typeid(DialogueEditorScreen)) {
				if (gui.get("DialogueEditorPanel") == nullptr) {
					gui.add(DialogueEditorPanel::getInstance().getPanel(), "DialogueEditorPanel");
				}
			}
			else {
				gui.removeAllWidgets();
			}
			gui.draw();
			window.display();
		}
	}

	// Free up all of our variables
	mBus.terminate();

	return 0;
}
