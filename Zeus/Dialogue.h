#pragma once

#include <memory>
#include <vector>
#include <fstream>
#include <SFML/System.hpp>

class Dialogue {

	struct msgNode;
	struct optionNode;

public:
	Dialogue();
	Dialogue(std::string name);
	Dialogue::msgNode* addDialogueNode(sf::Vector2f loc = sf::Vector2f(0,0));
	void editDialoguenode(Dialogue::msgNode* node, std::string message = NULL, sf::Vector2f loc = sf::Vector2f(-1, -1));
	Dialogue::optionNode* addOptionNode(sf::Vector2f loc = sf::Vector2f(0, 0));
	void editOptionNode(Dialogue::optionNode* node, std::string message= NULL, int returnCode = NULL, sf::Vector2f loc = sf::Vector2f(-1, -1), Dialogue::msgNode* next = nullptr);
	void linkDialogue(Dialogue::msgNode* node1, Dialogue::msgNode* node2);
	void linkDialogueToOption(Dialogue::msgNode* dNode, Dialogue::optionNode* optNode);
	int getReturnCode(Dialogue::optionNode* node);
	std::string getMessage(Dialogue::msgNode *node);
	std::vector<std::string> getOptions(Dialogue::msgNode* node);
	sf::Vector2f getDialoguePos(Dialogue::msgNode* node);
	sf::Vector2f getOptionPos(Dialogue::optionNode* node);
	void deleteDialogueNode(Dialogue::msgNode* node);
	void deleteOptionNode(Dialogue::optionNode* node);
	std::vector<Dialogue::msgNode*> getMessageNodes();
	std::vector<Dialogue::optionNode*> getOptionNodes();
	std::string getTreeName();

	struct msgNode {
		std::string message;
		std::vector<Dialogue::optionNode *> options;
		std::vector<int> optionIDs;
		int nodeID, previousID = NULL;
		sf::Vector2f loc;
	};

	struct optionNode {
		std::string optionMsg;
		Dialogue::msgNode* next;
		int returnCode, nodeID, nextID, previousID;
		sf::Vector2f loc;
	};

private:
	std::string entityName;
	std::vector<Dialogue::msgNode *> nodes;
	std::vector<Dialogue::optionNode *> optionNodes;

	/*struct msgNode {
		std::string message;
		std::vector<Dialogue::optionNode*> options;
	};

	struct optionNode {
		std::string optionMsg;
		Dialogue::msgNode* next;
		int returnCode;
	};*/
};