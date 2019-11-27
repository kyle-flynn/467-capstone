#include "sfmlObjects3.h"

SFML_Objects3::SFML_Objects3() {
	//int dummy1 = 1;
	//help
	//*def2 = 1;
	this->world = new World(std::string("Resources/Tiles/tileset_grass.png"), def1, def2, 16, 16);
}

SFML_Objects3::SFML_Objects3(int** tileVals, int* enteredNum) {
	this->world = new World(std::string("Resources/Tiles/tileset_grass.png"), tileVals, enteredNum, 16, 16);
}


int SFML_Objects3::s3EventLogic(sf::Event event, sf::RenderWindow& window, int** tileVals, int enteredNum) {
	int stageNum = 3;
	switch (event.type) {
	case sf::Event::Closed:
		window.close();
		std::cout << "closed window\n";
		for (int i = 0; i < enteredNum; i++) {
			for (int j = 0; j < enteredNum; j++) {
				std::cout << "Element: [" << i << "][" << j << "] has value: " << tileVals[i][j] << "\n";
			}
		}
		break;
	}
	drawTo(stageNum, window);
	return stageNum;
}

void SFML_Objects3::drawTo(int stageNum, sf::RenderWindow& window) {
	window.clear();
	this->world->draw(window);
	window.display();
}