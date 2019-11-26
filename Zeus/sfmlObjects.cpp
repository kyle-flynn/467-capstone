#include "sfmlObjects.h"

SFML_Objects::SFML_Objects() {
	//this->shptr = &enteredNum;

	t1.setPosition({ 100, 100 });
	t1.setBorderSize(2);

	text1.setPosition({ 130, 250 });
	text1.setLimit(true, 4);
	text1.setBorderSize(1);

	btn1.setPosition({ 610, 250 });
}

void SFML_Objects::stage2Objects(int enteredNum) {
	if (!image1.loadFromFile("Resources/images/userTutorial/numberedTileset.jpg"))
		std::cout << "Font not found!\n";

	sprite1.setTexture(image1);
	sprite1.setPosition(700, 100);

	t2.setTitle("Fill in Values");
	t2.setBoxSize({ 500, 100 });
	t2.setPosition({ 100, 50 });
	t2.setBorderSize(2);

	d1.setTextNum(enteredNum);
	d1.setPosition({ 300, 200 });

	d2.setTextNums(*rowVal, *colVal);
	d2.setBoxSize({ 250, 50 });
	d2.setPosition({ 215, 300 });

	text2.setBoxSize({ 100, 30 });
	text2.setPosition({ 300, 400 });
	text2.setLimit(true, 4);
	text2.setBorderSize(1);

	btn2.setPosition({ 330, 500 });
}

void SFML_Objects::stage2ObjectsInLoop(int enteredNum) {
	d2.setTextNums(*rowVal, *colVal);
}

void SFML_Objects::changeWindow(int stageNum, sf::RenderWindow& window) {
	window.create(sf::VideoMode(1200, 1000), "World Generation", sf::Style::Titlebar | sf::Style::Close);
}

void SFML_Objects::createArray(int enteredNum) {
	rVal = *counter / *shptr;
	cVal = *counter % *shptr;

	tileVals = new int* [enteredNum];
	for (int i = 0; i < enteredNum; i++) {
		tileVals[i] = new int[enteredNum];
	}
}

int SFML_Objects::s1EventLogic(sf::Event event, sf::RenderWindow& window) {
	int stageNum = 1;
	switch (event.type) {
	case sf::Event::Closed:
		window.close();
		std::cout << "closed window\n";
		break;
	case sf::Event::TextEntered:
		text1.typedOn(event);
		//std::cout << "text entered!\n";
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
				std::cout << "Hello " << enteredNum << "\n";
				stageNum = 2;
				createArray(*shptr);
				changeWindow(stageNum, window);
				stage2Objects(*shptr);
			}
		}
	}
	drawTo(stageNum, window);
	return stageNum;
}

int SFML_Objects::s2EventLogic(sf::Event event, sf::RenderWindow& window) {
	int stageNum = 2;
	switch (event.type) {
	case sf::Event::Closed:
		window.close();
		std::cout << "closed window\n";
		break;
	case sf::Event::TextEntered:
		text2.typedOn(event);
		//std::cout << "text entered!\n";
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
			enteredNum2 = std::atoi(t.c_str());
			if (enteredNum2 < 1 || enteredNum2 > 251) {
				std::cout << "WRONG \n";
			}
			else {
				if (*counter < (*shptr * *shptr)) {
					std::cout << "Elem # " << *counter + 1 << "\n";

					*counter = *counter + 1;
					rVal = *counter / *shptr;
					cVal = *counter % *shptr;
					d2.setTextNums(*rowVal, *colVal);
					*counter = *counter - 1;

					rVal = *counter / *shptr;
					cVal = *counter % *shptr;
					tileVals[rVal][cVal] = enteredNum2;
					*counter = *counter + 1;

					if (*counter == (*shptr * *shptr)) {
						std::cout << "All done!\n";
						stageNum = 3;
					}
				}
			}
		}
	}
	drawTo(stageNum, window);
	return stageNum;
}

int SFML_Objects::s3EventLogic(sf::Event event, sf::RenderWindow& window) {
	int stageNum = 3;
	switch (event.type) {
	case sf::Event::Closed:
		window.close();
		std::cout << "closed window\n";
		for (int i = 0; i < *shptr; i++) {
			for (int j = 0; j < *shptr; j++) {
				std::cout << "Element: [" << i << "][" << j << "] has value: " << tileVals[i][j] << "\n";
			}
		}
		break;
	}
	return stageNum;
}

void SFML_Objects::readyToType(int stageNum) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		switch (stageNum) {
		case 1:
			text1.setSelected(true);
			break;
		case 2:
			text2.setSelected(true);
			break;
		}
	}else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		switch (stageNum) {
		case 1:
			text1.setSelected(false);
			break;
		case 2:
			text2.setSelected(false);
			break;
		}
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
		t2.drawTo(window);
		d1.drawTo(window);
		d2.drawTo(window);
		text2.drawTo(window);
		btn2.drawTo(window);
		window.draw(sprite1);
	case 3:
		t2.drawTo(window);
		d1.drawTo(window);
		window.draw(sprite1);
	}
	window.display();

	//this->world->draw(window);
}