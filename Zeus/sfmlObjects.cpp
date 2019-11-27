#include "sfmlObjects.h"

SFML_Objects::SFML_Objects() {
	t1.setPosition({ 100, 100 });
	t1.setBorderSize(2);

	text1.setPosition({ 130, 250 });
	text1.setLimit(true, 4);
	text1.setBorderSize(1);

	btn1.setPosition({ 610, 250 });
}

void SFML_Objects::changeWindow(int stageNum, sf::RenderWindow& window) {
	window.create(sf::VideoMode(1200, 1000), "World Generation", sf::Style::Titlebar | sf::Style::Close);
}


int* SFML_Objects::createArray(int** tileVals, int** temp) {
	tileVals = new int* [** temp];
	for (int i = 0; i < **temp; i++) {
		tileVals[i] = new int[**temp];
	}
	return *tileVals;
}


int SFML_Objects::s1EventLogic(sf::Event event, sf::RenderWindow& window, int** tileVals, int** temp) {
	int stageNum = 1;
	switch (event.type) {
	case sf::Event::Closed:
		window.close();
		std::cout << "closed window\n";
		break;
	case sf::Event::TextEntered:
		text1.typedOn(event);
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
			enteredNum = std::atoi(t.c_str());
			if (enteredNum < 1) {
				std::cout << "WRONG \n";
			}
			else {
				*temp = &enteredNum;
				std::cout << "Hello " << enteredNum << "\n";
				stageNum = 2;
				changeWindow(stageNum, window);
				//tileVals = new int* [**temp];
				//for (int i = 0; i < **temp; i++) {
					//tileVals[i] = new int[**temp];
				//}
			}
		}
	}
	drawTo(stageNum, window);
	return stageNum;
}

void SFML_Objects::readyToType(int stageNum) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		text1.setSelected(true);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		text1.setSelected(false);
	}
}

void SFML_Objects::drawTo(int stageNum, sf::RenderWindow& window) {
	window.clear();
	switch (stageNum) {
	case 1:
		t1.drawTo(window);
		text1.drawTo(window);
		btn1.drawTo(window);
		break;
	case 2:
		break;
	}
	window.display();
}