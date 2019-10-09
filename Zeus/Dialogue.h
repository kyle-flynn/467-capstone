#pragma once

#include <memory>
#include <vector>
#include <fstream>
#include <json.hpp>

class Dialogue {

	struct msgNode;
	struct optionNode;

public:
	Dialogue();
	Dialogue(std::string name);
	Dialogue::msgNode* addDialogueNode(int xPos, int yPos);
	void editDialoguenode(Dialogue::msgNode* node, std::string message, int xPos, int yPos);
	Dialogue::optionNode* addOptionNode(int xPos, int yPos);
	void editOptionNode(Dialogue::optionNode* node, std::string message, int returnCode, int xPos, int yPos, Dialogue::msgNode* next);
	void linkDialogue(Dialogue::msgNode* node1, Dialogue::msgNode* node2);
	void linkDialogueToOption(Dialogue::msgNode* dNode, Dialogue::optionNode* optNode);
	int getReturnCode(Dialogue::optionNode* node);
	std::string getMessage(Dialogue::msgNode *node);
	std::vector<std::string> getOptions(Dialogue::msgNode* node);
	std::pair<int, int> getDialoguePos(Dialogue::msgNode* node);
	std::pair<int, int> getOptionPos(Dialogue::optionNode* node);

	struct msgNode {
		std::string message;
		std::vector<Dialogue::optionNode *> options;
		int x, y;
	};

	struct optionNode {
		std::string optionMsg;
		Dialogue::msgNode* next;
		int returnCode;
		int x, y;
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