#include "GameplayScreen.h"
#include "ScreenManager.h"
#include "MainMenuScreen.h"


#include <iostream>

GameplayScreen::GameplayScreen() {
	Screen();

	//int* shptr = 0;
	int enteredNum = 0;
	this->stageNum = &defaultStage;

	// Stage1 sfml
	t1.setPosition({ 100, 100 });
	t1.setBorderSize(2);
	
	
	text1.setPosition({ 130, 250 });
	text1.setLimit(true, 30);
	text1.setBorderSize(1);
	text1.setBackColor(sf::Color::Black);
	
	btn1.setPosition({ 610, 250 });

	// Stage2 sfml
	t2.setTitle("Fill in Values");
	t2.setBoxSize({ 500, 100 });
	t2.setPosition({ 100, 50 });
	t2.setBorderSize(2);
	
	d1.setPosition({ 300, 200 });

	if (!image1.loadFromFile("Resources/images/userTutorial/numberedTileset.jpg"))
		std::cout << "Font not found!\n";

	sprite1.setTexture(image1);
	sprite1.setPosition(700, 100);

	//this->world = new World(std::string("Resources/Tiles/tileset_grass.png"), tiles, 16, 16);
}

void GameplayScreen::changeWindow(int stageNum, sf::RenderWindow& window) {
	/*
	s2Window = { 1200, 1000 };
	centerPoint = { (sf::VideoMode::getDesktopMode().width / 2), (sf::VideoMode::getDesktopMode().height / 2) };
	int cpx = centerPoint.x - 600;
	int cpy = centerPoint.y - 500;
	newCenter = { cpx, cpy };

	if (stageNum == 2) {
		window.setSize(s2Window);
		window.setPosition(newCenter);
	}
	*/
	//window.create(sf::VideoMode(900, 900), "SFML Textbox", sf::Style::Titlebar | sf::Style::Close);
	window.create(sf::VideoMode(1200, 1000), "World Generation", sf::Style::Titlebar | sf::Style::Close);
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

void GameplayScreen::stage1Logic(sf::Event event, sf::RenderWindow& window) {
	
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
				*stageNum = 2;
				changeWindow(*stageNum, window);
				stage2Logic(enteredNum);
			}
		}
		
	}
	draw(*stageNum, window);
}


void GameplayScreen::stage2Logic(int enteredNum) {
	
	d1.setTextNum(enteredNum);
	
	std::cout << "2nd stage value: " << enteredNum << "\n";
	
}


void GameplayScreen::draw(int stageNum, sf::RenderWindow& window) {
	window.clear();
	switch (stageNum) {
	case 1:
		t1.drawTo(window);
		text1.drawTo(window);
		btn1.drawTo(window);
		break;
	case 2:
		t2.drawTo(window);
		d1.drawTo(window);
		//sprite1.drawTo(window);
		window.draw(sprite1);
	}
	window.display();
	
	//this->world->draw(window);
}