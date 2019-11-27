#pragma once

#include "QuestOption.h"
#include "Screen.h"
#include "Game.h"
#include "MenuOption.h"
#include "EditorText.h"

#include <filesystem>

class QuestEditorScreen : public Screen {

public:

	QuestEditorScreen();
	void update(float deltaTime);
	void update(sf::Event event);
	void draw(sf::RenderWindow& window);
	void handleEvent(sf::Event event);
	void addQuest();
	void removeQuest();
	void changeActive();

private:

	const float ICON_SIZE = 200;
	int it;
	sf::Text header, newQuest, deleteQuest;
	EditorText activeName = EditorText(sf::String("Quest Name:")), 
	EditorText activeGoal = EditorText(sf::String("Quest Goal:")),
	EditorText activeReward = EditorText(sf::String("Quest Reward:")),
		
	//sf::Text activeName, activeType, activeStat, activeDescription;
	sf::Texture BGTexture, defaultIcon;
	sf::Sprite BGSprite, activeIcon;
	sf::Vector2i mousePosition;
	std::vector<QuestOption*> quests;
	std::vector<sf::Texture> icons;
	sf::Rect<float> newBounds, deleteBounds, upBounds, downBounds;
	sf::CircleShape listUp, listDown;
	QuestOption* active;

	void loadIcons();
	void loadQuests();
	void sortQuests();
	void updateActiveStats();
	void drawActive(sf::RenderWindow& window);

};

//415