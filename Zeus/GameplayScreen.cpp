#include "GameplayScreen.h"
#include "ScreenManager.h"
#include "MainMenuScreen.h"


#include <iostream>

GameplayScreen::GameplayScreen() {
	Screen();

	//int* shptr = 0;
	int enteredNum = 0;

	// Stage1 sfml
	t1.setPosition({ 100, 100 });
	t1.setBorderSize(2);
	
	
	text1.setPosition({ 130, 250 });
	text1.setLimit(true, 30);
	text1.setBorderSize(1);
	text1.setBackColor(sf::Color::Black);
	
	btn1.setPosition({ 610, 250 });

	// Stage2 sfml
	if (!image1.loadFromFile("Resources/images/userTutorial/numberedTileset.jpg"))
		std::cout << "Font not found!\n";

	sf::Sprite sprite1(image1);
	sprite1.setPosition(700, 100);
	
	t2.setTitle("Fill in Values");
	t2.setBoxSize({ 500, 100 });
	t2.setPosition({ 100, 50 });
	t2.setBorderSize(2);
	//t2.setBackColor(sf::Color::Black);

	//this->world = new World(std::string("Resources/Tiles/tileset_grass.png"), tiles, 16, 16);
}

void GameplayScreen::specialKeyPressed(int key) {
	switch (key) {
	case 1:	
		text1.setSelected(true);
		break;
	case 2:
		text1.setSelected(false);
		break;
	}
}

void GameplayScreen::eventLogic(sf::Event event, sf::RenderWindow& window) {
	switch (event.type) {
	case sf::Event::Closed:
		window.close();
		std::cout << "closed window\n";
		return;
	case sf::Event::TextEntered:
		text1.typedOn(event);
		std::cout << "text entered!\n";
	case sf::Event::MouseMoved:
		if (btn1.isMouseOver(window)) {
			btn1.setBackColor(sf::Color::Magenta);
		}
		else {
			btn1.setBackColor(sf::Color::Green);
		}
		break;
	case sf::Event::MouseButtonPressed:
		if (btn1.isMouseOver(window)) {
			std::string t = text1.getText();
			int enteredNum = std::atoi(t.c_str());
			if (enteredNum < 1) {
				std::cout << "WRONG \n";
			}
			else {
				shptr = &enteredNum;
				std::cout << "Hello " << enteredNum << "\n";
				//window.close();
				stage2Logic(enteredNum);
			}
		}
		
	}
	window.clear();
	t1.drawTo(window);
	text1.drawTo(window);
	btn1.drawTo(window);
	window.display();

	//std::cout << "value is now " << *shptr << "\n";
}


void GameplayScreen::stage2Logic(int enteredNum) {
	//
	//
	// You were in the middle of figuring out how to change the stageNum var
	// in the game loop upon receiving a correct number. Also changing the screen size
	//
	//
}


void GameplayScreen::draw(sf::RenderWindow& window) {
	//mousePosition = sf::Mouse::getPosition(window);
	window.clear();
	t1.drawTo(window);
	text1.drawTo(window);
	btn1.drawTo(window);
	window.display();
	//drawActive(window);
	//this->world->draw(window);
}