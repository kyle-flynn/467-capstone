#pragma once

#include <SFML/Graphics.hpp>

#ifndef GAME_BATTLE_TEXTBOX_H
#define GAME_BATTLE_TEXTBOX_H

enum BattleTextMode {
	SINGLE_ROW,
	DUAL_ROW,
	DUAL_ROW_DUAL_COLUMNS,
	SINGLE_ROW_COMBAT
};

enum BattleMode {
	OPTIONS_CHOOSING,
	ACTIONS_CHOOSING,
	COMBAT_LOG
};

class BattleTextbox : public sf::Drawable, sf::Transformable {
public:
	BattleTextbox();
	void update(float deltaTime);
	void handleEvent(sf::Event event);
	void updateBattleText(const std::string& text);
	void setSelectedOption(int selected);
	void setSelectedAction(int selected);
	int getSelected();
private:
	sf::Texture textboxTexture;

	sf::Text optionOne;
	sf::Text optionTwo;
	sf::Text optionThree;
	sf::Text optionFour;
	sf::Text singleRow;
	std::vector<sf::Text*> dualRows;
	sf::Text descriptionText;

	sf::VertexArray combatTextbox;
	sf::VertexArray combatOptionsBox;
	sf::VertexArray combatActionsBox;
	sf::VertexArray combatDescriptionBox;

	BattleTextMode textMode;
	BattleMode battleMode;

	int selectedOption;
	int selectedAction;

	void checkForNewlines(const std::string& text);
	void setBattleMode(BattleMode newMode);
	void initBattleBoxVertices();
	void initOptionsBoxVertices();
	void initActionsBoxVertices();
	void initDescriptionBoxVertices();
	void executeSelectedOption();

	void renderItems();
	void renderMoveset();

	void drawSquare(sf::VertexArray& vertices, size_t index, float x, float y, float width, float height);
	void assignTexCoords(sf::VertexArray& vertices, size_t index, float x, float y, float width, float height);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif