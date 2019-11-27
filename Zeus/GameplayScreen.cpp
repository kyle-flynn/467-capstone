#include "GameplayScreen.h"

GameplayScreen::GameplayScreen() {
	Screen();
	this->stageNum = &defaultStage;
	//int defaultInput = 1;
	//int defaultTile = 0;
	//*temp = &defaultInput;
	//*tileVals = &defaultTile;
}

int**  GameplayScreen::createArray(int** tileVals, int* temp) {
	const int userInput = *temp;
	//sfmlObj.createArray(tileVals, temp);
	tileVals = new int* [userInput];
	for (int i = 0; i < userInput; i++) {
		tileVals[i] = new int[userInput];
	}
	return &tileVals[0];
}

int GameplayScreen::eventLogic(sf::Event event, sf::RenderWindow& window) {
	switch (*stageNum) {
	case 1:
		sfmlObj.readyToType(*stageNum);
		*stageNum = sfmlObj.s1EventLogic(event, window, tileVals, temp);
		p2a = createArray(tileVals, *temp);
		//if (temp > 0) { *stageNum = 2; };
		break;
	case 2:
		//*tileVals = createArray(tileVals, temp);
		sfmlObj2.readyToType(*stageNum);
		sfmlObj2.stage2Objects(*temp);
		*stageNum = sfmlObj2.s2EventLogic(event, window, p2a, *temp);
		//if (*stageNum == 3) { 
			//SFML_Objects3 sfmlObj3(tileVals, temp);
			//sfmlObj3.setWorldData(tileVals, temp); 
		//};
		break;
	case 3:
		//sfmlObj3.setWorldData(tileVals, *temp);
		SFML_Objects3 sfmlObj3(p2a, *temp);
		*stageNum = sfmlObj3.s3EventLogic(event, window, p2a, **temp);
		break;
	}

	return *stageNum;
}

void GameplayScreen::draw(int stageNum, sf::RenderWindow& window) {
	window.clear();
	switch (stageNum) {
	case 1:
		sfmlObj.drawTo(stageNum, window);
		break;
	case 2:
		sfmlObj2.drawTo(stageNum, window);
		break;
	case 3:
		sfmlObj3.drawTo(stageNum, window);
		break;
	}
	window.display();
}