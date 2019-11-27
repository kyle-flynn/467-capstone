#include "sfmlObjects2.h"

SFML_Objects2::SFML_Objects2() {
	if (!image1.loadFromFile("Resources/images/userTutorial/numberedTileset.jpg"))
		std::cout << "Font not found!\n";

	sprite1.setTexture(image1);
	sprite1.setPosition(700, 100);

	//Title t2;
	t2.setTitle("Fill in Values");
	t2.setBoxSize({ 500, 100 });
	t2.setPosition({ 100, 50 });
	t2.setBorderSize(2);

	//Textbox text2;
	text2.setBoxSize({ 100, 30 });
	text2.setPosition({ 300, 400 });
	text2.setLimit(true, 4);
	text2.setBorderSize(1);

	//Button btn2;
	btn2.setPosition({ 330, 500 });
}

void SFML_Objects2::stage2Objects(int* enteredNum) {
	rVal = *counter / *enteredNum;
	cVal = *counter % *enteredNum;

	//DynText d1;
	d1.setTextNum(*enteredNum);
	d1.setPosition({ 300, 200 });

	//DynText d2;
	d2.setTextNums(*rowVal, *colVal);
	d2.setBoxSize({ 250, 50 });
	d2.setPosition({ 215, 300 });
}


int SFML_Objects2::s2EventLogic(sf::Event event, sf::RenderWindow& window, int** tileVals, int* enteredNum) {
	int stageNum = 2;
	switch (event.type) {
	case sf::Event::Closed:
		window.close();
		std::cout << "closed window\n";
		break;
	case sf::Event::TextEntered:
		text2.typedOn(event);
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
				int *shptr2 = &enteredNum2;
				if (*counter < (*enteredNum * *enteredNum)) {
					std::cout << "Elem # " << *counter + 1 << "\n";

					*counter = *counter + 1;
					rVal = *counter / *enteredNum;
					cVal = *counter % *enteredNum;
					d2.setTextNums(*rowVal, *colVal);
					*counter = *counter - 1;

					rVal = *counter / *enteredNum;
					cVal = *counter % *enteredNum;
					tileVals[rVal][cVal] = enteredNum2;
					*counter = *counter + 1;

					if (*counter == (*enteredNum * *enteredNum)) {
						std::cout << "All done!\n";
						stageNum = 3;
						//stage3Objects(tileVals);
					}
				}
			}
		}
	}
	drawTo(stageNum, window);
	return stageNum;
}

void SFML_Objects2::readyToType(int stageNum) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		text2.setSelected(true);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		text2.setSelected(false);
	}
}

void SFML_Objects2::drawTo(int stageNum, sf::RenderWindow& window) {
	window.clear();
	switch (stageNum) {
	case 2:
		t2.drawTo(window);
		d1.drawTo(window);
		d2.drawTo(window);
		text2.drawTo(window);
		btn2.drawTo(window);
		window.draw(sprite1);
		break;
	case 3:
		break;
	}
	window.display();
}