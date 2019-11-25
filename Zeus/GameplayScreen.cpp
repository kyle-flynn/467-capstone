#include "GameplayScreen.h"
#include "ScreenManager.h"
#include "MainMenuScreen.h"


#include <iostream>
//#include "UserInputField.h"
//#include "Button.h"
//#include "Title.h"
//#include "DynamicText.h"
//#include "DynamicText2.h"

GameplayScreen::GameplayScreen() {
	Screen();

	//t1("Enter a Number for Map Size", { 700, 100 }, 30, sf::Color::Yellow, sf::Color::Red);
	//t1.setFont(font);
	
	t1.setPosition({ 100, 100 });
	t1.setBorderSize(2);
	t1.setBackColor(sf::Color::Black);

	//Textbox text1(20, { 450, 30 }, sf::Color::White, sf::Color::White, true);
	// /*
	//text1.setFont(font);
	text1.setPosition({ 130, 250 });
	text1.setLimit(true, 30);
	text1.setBorderSize(1);
	text1.setBackColor(sf::Color::Black);
	// */
	//Button btn1("Enter", { 150, 30 }, 20, sf::Color::Green, sf::Color::Black);
	//btn1.setFont(font);
	//btn1.setPosition({ 610, 250 });
	// */
	

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
		//return;
	}
	//case sf::Event::MouseMoved:
		/*
		if (btn1.isMouseOver(window)) {
			btn1.setBackColor(sf::Color::Magenta);
		}
		else {
			btn1.setBackColor(sf::Color::Green);
		}
		*/
		//break;
	//case sf::Event::MouseButtonPressed:
		/*
		if (btn1.isMouseOver(window)) {
			std::string t = text1.getText();
			int enteredNum = std::atoi(t.c_str());
			if (enteredNum < 1) {
				std::cout << "WRONG \n";
			}
			else {
				//shptr = &enteredNum;
				std::cout << "Hello " << enteredNum << "\n";
				window.close();
			}
		}
		*/
	//}
	window.clear();
	t1.drawTo(window);
	text1.drawTo(window);
	window.display();
}

void GameplayScreen::draw(sf::RenderWindow& window) {
	//mousePosition = sf::Mouse::getPosition(window);
	window.clear();
	t1.drawTo(window);
	text1.drawTo(window);
	window.display();
	//drawActive(window);
	//this->world->draw(window);
}