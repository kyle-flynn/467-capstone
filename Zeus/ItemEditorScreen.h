#pragma once

#include "ItemOption.h"
#include "Screen.h"
#include "Game.h"
#include "MenuOption.h"

#include <filesystem>

class ItemEditorScreen : public Screen {

public:

	ItemEditorScreen();
	void update(float deltaTime);
	void update(sf::Event event);
	void draw(sf::RenderWindow& window);
	void handleEvent(sf::Event event);
	void addItem();
	void removeItem();
	void changeActive();

private:

	const float ICON_SIZE = 200;
	int it;
	sf::Text header, newItem, deleteItem;
	sf::Text activeName, activeType, activeStat, activeDescription;
	sf::Texture BGTexture, defaultIcon;
	sf::Sprite BGSprite, activeIcon;
	sf::Vector2i mousePosition;
	std::vector<ItemOption> items;
	std::vector<sf::Texture> icons;
	sf::Rect<float> newBounds, deleteBounds, upBounds, downBounds;
	sf::CircleShape listUp, listDown;
	ItemOption* active;

	void loadIcons();
	void loadItems();
	void sortItems();
	void drawActive(sf::RenderWindow& window);

};

//415