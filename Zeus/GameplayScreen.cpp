#include "GameplayScreen.h"
#include <iostream>

GameplayScreen::GameplayScreen(int &shptr) : Screen() {
	// Texture Sheet dimensions are 12x21 (value range: 0-251)

	// Empty Values for texture sheet: 
	// 8, 67, 80, 92, 
	// 104-106, 116, 190, 196, 
	// 202, 208-214, 220-227, 231-239, 243-251
	/*
	int tiles[3][3] = {
		{1,1,1},
		{22,22,22},
		{50,50,50}
	};

	int tiles[4][4] = {
		{54,55,56,20},
		{66,198,68,44},
		{78,79,80,228},
		{48,49,50,240}
	};

	int tiles[5][5] = {
		{54,55,56,20, 1},
		{66,198,68,44, 2},
		{78,79,80,228, 3},
		{48,49,50,240, 44},
		{1,2,3,44, 5}
	};
	
	std::cout << "GameplayScreen Value: " << shptr << "\n";

	int tiles[1][1] = {
		{50}
	};

	int tiles[2][2] = {
		{1,1},
		{50,50}
	};
	*/


	const int userInput = shptr;
	std::cout << "GameplayScreen Value: " << userInput << "\n";
	
	int** tiles = new int* [userInput];
	for (int i = 0; i < userInput; i++) {
		tiles[i] = new int[userInput];
	}

	

	/*

	int tiles[4][4] = {
		{1,1,1,1},
		{22,22,22,22},
		{50,50,50,50},
		{50,50,50,50}
	};

	int tiles[3][3] = {
		{1,1,1},
		{22,22,22},
		{50,50,50}
	};
	
	const int x = 3;
	int row;
	//*row = x;

	const int y = 3;
	int col;
	//*col = x;

	int** tileArray = new int* [row];
	for (int i = 0; i < row; i++) {
		tileArray[i] = new int[col];
	}

	int** tileVals =;

	int tile = tileArray[row][col] = {
		{1,1,1},
		{22,22,22},
		{50,50,50}
	};
	*/
	this->world = new World(std::string("Resources/Tiles/tileset_grass.png"), tiles, userInput, 16, 16);
}

void GameplayScreen::draw(sf::RenderWindow& window) {
	this->world->draw(window);
}