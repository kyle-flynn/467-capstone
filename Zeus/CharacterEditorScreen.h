#pragma once

#include "Character.h"
#include "Screen.h"
#include "Game.h"
#include "EditorText.h"
#include "CharacterOption.h"
#include "GameDataManager.h"

#include <filesystem>
#include <sstream>
#include <iomanip>

class CharacterEditorScreen : public Screen {

public:
	CharacterEditorScreen();
	void update(float deltaTime);
	void update(sf::Event event);
	void draw(sf::RenderWindow& window);
	void handleEvent(sf::Event event);
	void addCharacter();
	void removeCharacter();
	void changeActive();

private:

	const float ICON_SIZE = 150, AVATAR_WIDTH = 150, AVATAR_HEIGHT = 250;
	int it;
	sf::Text header, newChar, deleteChar;
	EditorText activeName = EditorText(sf::String("Character Name:")),
		activeType = EditorText(sf::String("Character Type:")),
		activeHP = EditorText(sf::String("Max Health:")),
		activeMana = EditorText(sf::String("Max Mana:")),
		activeStamina = EditorText(sf::String("Max Stamina:")),
		activeDescription = EditorText(sf::String("Description:"));
	sf::Texture BGTexture, defaultIcon, defaultAvatar;
	sf::Sprite BGSprite, activeIcon, activeAvatar;
	sf::Vector2i mousePosition;
	std::vector<CharacterOption*> characters;
	std::vector<sf::Texture> icons, avatars;
	sf::Rect<float> newBounds, deleteBounds, upBounds, downBounds;
	sf::CircleShape listUp, listDown;
	CharacterOption* active;

	void loadIcons();
	void loadAvatars();
	void loadCharacters();
	void saveCharacters();
	void sortCharacters();
	void updateActive();
	void drawActive(sf::RenderWindow& window);

};

