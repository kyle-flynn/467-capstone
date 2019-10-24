#include <SFML/Graphics.hpp>

#include "Game.h"

#include "FontManager.h"

#include "ScreenManager.h"
#include "GameplayScreen.h"
#include "MainMenuScreen.h"
#include "DIalogueEditorScreen.h"

#include "MessageBus.h"
#include "LoggingSystem.h"

#include <TGUI/TGUI.hpp>
#include "DialogueEditorPanel.h"

const float Game::WIDTH = 1280.0f;
const float Game::HEIGHT = 720.0f;

int main() {
	FontManager::getInstance().loadFonts();

	sf::RenderWindow window(sf::VideoMode(1280, 720), "ZEUS");
	window.setFramerateLimit(60);
	window.setActive();

	tgui::Gui gui(window);

	/*tgui::Panel::Ptr dialogueEditorPanel = tgui::Panel::create();
	dialogueEditorPanel->setPosition(40, 25);
	dialogueEditorPanel->setSize(200, 300);
	tgui::EditBox::Ptr headerBox = tgui::EditBox::create();
	headerBox->setSize(200, 20);
	headerBox->setPosition(0, 0);
	headerBox->setDefaultText("Message:");
	headerBox->setReadOnly(true);
	tgui::TextBox::Ptr messageBox = tgui::TextBox::create();
	messageBox->setSize(200, 160);
	messageBox->setPosition(0, 20);
	messageBox->setText("Insert message text");
	tgui::EditBox::Ptr returnBox = tgui::EditBox::create();
	returnBox->setSize(100, 20);
	returnBox->setPosition(0, 180);
	returnBox->setDefaultText("Return Code:");
	returnBox->setReadOnly(true);
	tgui::TextBox::Ptr returnCodeBox = tgui::TextBox::create();
	returnCodeBox->setSize(100, 20);
	returnCodeBox->setPosition(100, 180);
	returnCodeBox->setText("0");
	tgui::Button::Ptr messageButton = tgui::Button::create();
	messageButton->setSize(80, 30);
	messageButton->setPosition(10, 210);
	messageButton->setTextSize(10);
	messageButton->setText("New Message");
	tgui::Button::Ptr optionButton = tgui::Button::create();
	optionButton->setSize(80, 30);
	optionButton->setPosition(110, 210);
	optionButton->setTextSize(10);
	optionButton->setText("New Option");
	tgui::Button::Ptr deleteButton = tgui::Button::create();
	deleteButton->setSize(80, 30);
	deleteButton->setPosition(60, 260);
	deleteButton->setTextSize(10);
	deleteButton->setText("Delete");
	dialogueEditorPanel->add(headerBox);
	dialogueEditorPanel->add(messageBox);
	dialogueEditorPanel->add(returnBox);
	dialogueEditorPanel->add(returnCodeBox);
	dialogueEditorPanel->add(messageButton);
	dialogueEditorPanel->add(optionButton);
	dialogueEditorPanel->add(deleteButton);*/
	ScreenManager::getInstance().setScreen(new DialogueEditorScreen());
	DialogueEditorPanel DPanel = DialogueEditorPanel::getInstance(ScreenManager::getInstance().getScreen());
	gui.add(DPanel.getPanel());

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

	/*ScreenManager::getInstance().setScreen(new MainMenuScreen());*/
	//ScreenManager::getInstance().setScreen(new GameplayScreen());
	//ScreenManager::getInstance().setScreen(new DialogueEditorScreen());

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
			gui.handleEvent(event);
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
		gui.draw();
		window.display();
	}

	// Free up all of our variables
	mBus.terminate();

	return 0;
}