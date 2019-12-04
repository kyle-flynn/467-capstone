#pragma once

#include "Screen.h"
#include "Game.h"
#include "Monster.h"
#include "EditorText.h"
#include "GameDataManager.h"
#include "MonsterOption.h"

#include <filesystem>

class MonsterEditorScreen : public Screen {

public :

	MonsterEditorScreen();
	void update(float deltaTime);
	void update(sf::Event event);
	void draw(sf::RenderWindow& window);
	void handleEvent(sf::Event event);
	void addMonster();
	void removeMonster();
	void changeActive();

private:

	const float ICON_SIZE = 150, AVATAR_WIDTH = 150, AVATAR_HEIGHT = 250;
	int it;
	sf::Text header, newMonster, deleteMonster;
	EditorText activeName = EditorText(sf::String("Monster Name:")),
		activeType = EditorText(sf::String("Monster Type:")),
		activeHP = EditorText(sf::String("Max Health:")),
		activeDescription = EditorText(sf::String("Description:"));
	sf::Texture BGTexture, defaultIcon, defaultAvatar;
	sf::Sprite BGSprite, activeIcon, activeAvatar;
	sf::Vector2i mousePosition;
	std::vector<MonsterOption*> monsters;
	std::vector<sf::Texture> icons, avatars;
	sf::Rect<float> newBounds, deleteBounds, upBounds, downBounds;
	sf::CircleShape listUp, listDown;
	MonsterOption* active;

	void loadIcons();
	void loadAvatars();
	void loadMonsters();
	void saveMonsters();
	void sortMonsters();
	void updateActive();
	void(drawActive(sf::RenderWindow& window));

};
