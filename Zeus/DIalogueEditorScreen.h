#pragma once

#include "Game.h"
#include "Screen.h"
#include "DialogueEditorMessageNode.h"
#include "DialogueEditorOptionNode.h"

class DialogueEditorScreen : public Screen {

public:

	DialogueEditorScreen();
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	void clearScreen();
	void loadNodes();
	void changeTrees(Dialogue tree);

private:

	Dialogue activeTree;
	sf::Texture BGTexture;
	sf::Sprite BGSprite;
	sf::Vector2i mousePosition;
	std::vector<DialogueEditorMessageNode> messages;
	std::vector<DialogueEditorOptionNode> options;
	sf::VertexArray links;
	std::vector<Dialogue> dialogueTrees;

	void linkNodes();
	DialogueEditorMessageNode getMsgNode(Dialogue::msgNode* node);
	DialogueEditorOptionNode getOptionNode(Dialogue::optionNode* node);
};
