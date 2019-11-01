#pragma once

#include "Game.h"
#include "Screen.h"
#include "DialogueEditorMessageNode.h"
#include "DialogueEditorOptionNode.h"
#include "DialogueEditorPanel.h"
#include <TGUI/TGUI.hpp>

class DialogueEditorScreen : public Screen {

public:

	Dialogue* activeTree;
	Dialogue::msgNode* activeMNode;
	Dialogue::optionNode* activeONode;

	DialogueEditorScreen();
	void update(float deltaTime);
	void update(sf::Event event);
	void draw(sf::RenderWindow& window);
	void handleEvent(sf::Event event);
	void addMessage(sf::Vector2f loc = sf::Vector2f(0, 0));
	void addOption(sf::Vector2f loc = sf::Vector2f(0, 0));
	void deleteNode();
	void editNode(std::string message, int returnCode);
	void clearScreen();
	void loadNodes();
	void changeTrees(Dialogue* tree);
	void newTree();
	void changeActive(Dialogue::msgNode* mNode = nullptr, Dialogue::optionNode * oNode = nullptr);
	tgui::Panel::Ptr getPanel();


private:

	sf::Text header;
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
