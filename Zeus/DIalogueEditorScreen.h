#pragma once

#include "Game.h"
#include "Screen.h"
#include "DialogueEditorMessageNode.h"
#include "DialogueEditorOptionNode.h"
#include <TGUI/TGUI.hpp>

class DialogueEditorScreen : public Screen {

public:

	Dialogue* activeTree;

	DialogueEditorScreen();
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	void clearScreen();
	void loadNodes();
	void changeTrees(Dialogue* tree);
	void changeActive(Dialogue::msgNode* mNode = nullptr, Dialogue::optionNode * oNode = nullptr);

private:

	Dialogue::msgNode* activeMNode;
	Dialogue::optionNode* activeONode;
	sf::Texture BGTexture;
	sf::Sprite BGSprite;
	sf::Vector2i mousePosition;
	std::vector<DialogueEditorMessageNode> messages;
	std::vector<DialogueEditorOptionNode> options;
	sf::VertexArray links;
	std::vector<Dialogue*> dialogueTrees;

	void linkNodes();
	void loadTrees();
	DialogueEditorMessageNode getMsgNode(Dialogue::msgNode* node);
	DialogueEditorOptionNode getOptionNode(Dialogue::optionNode* node);
};
