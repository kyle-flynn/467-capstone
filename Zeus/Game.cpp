#include <SFML/Graphics.hpp>
#include "ScreenManager.h"
#include "GameplayScreen.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include "UserInputField.h"
#include "Button.h"
#include "Title.h"
#include "DynamicText.h"
#include "DynamicText2.h"
#include "Game.h"

const float Game::WIDTH = 1280.0f;
const float Game::HEIGHT = 720.0f;


int main() {
	int rVal;
	int cVal;

	int* shptr = 0;
	int* rowVal = &rVal;
	int* colVal = &cVal;
	

	sf::RenderWindow window;

	sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445, (sf::VideoMode::getDesktopMode().height / 2) - 480);

	window.create(sf::VideoMode(900, 900), "SFML Textbox", sf::Style::Titlebar | sf::Style::Close);
	window.setPosition(centerWindow);

	window.setKeyRepeatEnabled(true);

	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
		std::cout << "Font not found!\n";

	Title t1("Enter a Number for Map Size", { 700, 100 }, 30, sf::Color::Yellow, sf::Color::Red);
	t1.setFont(font);
	t1.setPosition({ 100, 100 });
	t1.setBorderSize(2);
	t1.setBackColor(sf::Color::Black);
	

	Textbox text1(20, { 450, 30 }, sf::Color::White, sf::Color::White, true);
	text1.setFont(font);
	text1.setPosition({ 130, 250 });
	text1.setLimit(true, 30);
	text1.setBorderSize(1);
	text1.setBackColor(sf::Color::Black);

	Button btn1("Enter", { 150, 30 }, 20, sf::Color::Green, sf::Color::Black);
	btn1.setFont(font);
	btn1.setPosition({ 610, 250 });

	int enteredNum = 0;

	sf::Clock clock;


	//Main Loop:
	while (window.isOpen()) {

		sf::Event Event;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
			text1.setSelected(true);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			text1.setSelected(false);
		}

		//Event Loop:
		while (window.pollEvent(Event)) {
			switch (Event.type) {

			case sf::Event::Closed:
				window.close();
			case sf::Event::TextEntered:
				text1.typedOn(Event);
			case sf::Event::MouseMoved:
				if (btn1.isMouseOver(window)) {
					btn1.setBackColor(sf::Color::Magenta);
					//t1.setBackColor(sf::Color::Green);
				}
				else {
					btn1.setBackColor(sf::Color::Green);
					//t1.setBackColor(sf::Color::Blue);
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
						window.close();
						//ScreenManager::getInstance().setScreen(new GameplayScreen());
						//sf::RenderWindow window;
						//ScreenManager::getInstance().draw(window);
					}
				}
			}
		}
		window.clear();
		t1.drawTo(window);
		text1.drawTo(window);
		btn1.drawTo(window);
		window.display();
	}

	window.clear();
	//ScreenManager::getInstance().setScreen(new GameplayScreen(*shptr));

	
	
	sf::Texture image1;
	if (!image1.loadFromFile("Resources/images/userTutorial/numberedTileset.jpg"))
		std::cout << "Font not found!\n";

	sf::Sprite sprite1(image1);
	sprite1.setPosition(700, 100);

	window.create(sf::VideoMode(1200, 1000), "Zeus", sf::Style::Titlebar | sf::Style::Close);

	Title t2("Fill in Values", { 500, 100 }, 30, sf::Color::Yellow, sf::Color::Red);
	t2.setFont(font);
	t2.setPosition({ 100, 50 });
	t2.setBorderSize(2);
	t2.setBackColor(sf::Color::Black);

	DynText t3(*shptr, 25, { 100, 50 }, sf::Color::White, sf::Color::Black);
	t3.setFont(font);
	t3.setPosition({ 330, 200 });
	t3.setBackColor(sf::Color::Black);

	*rowVal = 0;
	*colVal = 0;
	DynText2 t4(25, { 250, 50 }, sf::Color::White, sf::Color::Black);
	t4.setFont(font);
	t4.setPosition({ 230, 300 });
	//t4.setString(*rowVal, *colVal);
	t4.setBackColor(sf::Color::Black);

	Textbox text2(20, { 100, 30 }, sf::Color::White, sf::Color::White, true);
	text2.setFont(font);
	text2.setPosition({ 330, 400 });
	text2.setLimit(true, 30);
	text2.setBorderSize(1);
	text2.setBackColor(sf::Color::Black);

	Button btn2("Enter", { 150, 30 }, 20, sf::Color::Green, sf::Color::Black);
	btn2.setFont(font);
	btn2.setPosition({ 330, 500 });

	std::cout << "value is now " << *shptr << "\n";


	const int userInput = *shptr;
	std::cout << "GameplayScreen Value: " << userInput << "\n";

	int** tileVals = new int* [userInput];
	for (int i = 0; i < userInput; i++) {
		tileVals[i] = new int[userInput];
	}

	bool filledAll = false;
	int counter = 0;
	rVal = counter / userInput;
	cVal = counter % userInput;
	t4.setString(*rowVal, *colVal);

	while (window.isOpen()) {
		sf::Event Event;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
			text2.setSelected(true);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			text2.setSelected(false);
		}
		while (window.pollEvent(Event)) {
			switch (Event.type) {

			case sf::Event::Closed:
				window.close();
			case sf::Event::TextEntered:
				text2.typedOn(Event);
			case sf::Event::MouseMoved:
				if (btn2.isMouseOver(window)) {
					btn2.setBackColor(sf::Color::Magenta);
				}
				else {
					btn2.setBackColor(sf::Color::Green);
				}
				break;
			case sf::Event::MouseButtonPressed:
				if (btn2.isMouseOver(window)) {
					std::string t = text2.getText();
					int enteredNum = std::atoi(t.c_str());
					if (enteredNum < 1 || enteredNum > 251) {
						std::cout << "WRONG \n";

					}
					else {
						if (!filledAll) {
							//shptr = &enteredNum;
							std::cout << "Elem # " << counter + 1 << "\n";
							
							counter++;
							rVal = counter / userInput;
							cVal = counter % userInput;
							t4.setString(*rowVal, *colVal);
							counter--;

							rVal = counter / userInput;
							cVal = counter % userInput;
							tileVals[rVal][cVal] = enteredNum;
							counter++;
						

							if (counter == (userInput * userInput)) {
								filledAll = true;
								std::cout << "All done!\n";
								window.close();
							}
						}
						
						
					}
				}
			}
		}
		window.clear();
		t2.drawTo(window);
		t3.drawTo(window);
		if (!filledAll) {
			t4.drawTo(window);
			text2.drawTo(window);
			btn2.drawTo(window);
		}
		window.draw(sprite1);
		//ScreenManager::getInstance().draw(window);
		window.display();
		
	}

	for (int i = 0; i < userInput; i++) {
		for (int j = 0; j < userInput; j++) {
			std::cout << "Element: [" << i << "][" << j << "] has value: " << tileVals[i][j] << "\n";
		}
	}

	window.create(sf::VideoMode(1200, 1000), "Zeus2", sf::Style::Titlebar | sf::Style::Close);

	window.clear();
	ScreenManager::getInstance().setScreen(new GameplayScreen(*shptr, tileVals));

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		window.clear();
		ScreenManager::getInstance().draw(window);
		window.display();

	}

}