#include "Dialogue.h"

Dialogue::Dialogue() {
	this->entityName = "DEFAULT";
	this->nodes;
	this->optionNodes;
}

Dialogue::Dialogue(std::string name) {
	this->entityName = name;
	this->nodes;
	this->optionNodes;
}

Dialogue::msgNode* Dialogue::addDialogueNode(int xPos, int yPos) {
	Dialogue::msgNode* newNode = new Dialogue::msgNode;
	newNode->x = xPos;
	newNode->y = yPos;
	nodes.push_back(newNode);
}

void Dialogue::editDialoguenode(Dialogue::msgNode* node, std::string message = NULL, int xPos = NULL, int yPos = NULL) {
	if (!message.empty()) {
		node->message = message;
	}
	if (xPos != NULL) {
		node->x = xPos;
	}
	if (yPos != NULL) {
		node->y = yPos;
	}
}

Dialogue::optionNode* Dialogue::addOptionNode(int xPos, int yPos) {
	Dialogue::optionNode* newNode = new Dialogue::optionNode;
	newNode->x = xPos;
	newNode->y = yPos;
	optionNodes.push_back(newNode);
}

void Dialogue::editOptionNode(Dialogue::optionNode* node, std::string message = NULL, int returnCode = NULL, int xPos = NULL, int yPos = NULL, Dialogue::msgNode* next = NULL) {
	if (!message.empty()) {
		node->optionMsg = message;
	}
	if (returnCode != NULL) {
		node->returnCode = returnCode;
	}
	if (xPos != NULL) {
		node->x = xPos;
	}
	if (yPos != NULL) {
		node->y = yPos;
	}
	if (next != NULL) {
		node->next = next;
	}
}

void Dialogue::linkDialogue(Dialogue::msgNode* node1, Dialogue::msgNode* node2) {
	int newXPos = (node1->x + node2->x) / 2;
	int newYPos = (node1->y + node2->y) / 2;
	Dialogue::optionNode* newNode = addOptionNode(newXPos, newYPos);
	node1->options.push_back(newNode);
	newNode->next = node2;
}

void Dialogue::linkDialogueToOption(Dialogue::msgNode* dNode, Dialogue::optionNode* optNode) {
	dNode->options.push_back(optNode);
}

int Dialogue::getReturnCode(Dialogue::optionNode* node) {
	return node->returnCode;
}

std::string Dialogue::getMessage(Dialogue::msgNode* node) {
	return node->message;
}

std::vector<std::string> Dialogue::getOptions(Dialogue::msgNode* node) {
	std::vector<std::string> optionList;
	for (auto n : node->options) {
		optionList.push_back(n.optionMsg);
	}
}

std::pair<int, int> Dialogue::getDialoguePos(Dialogue::msgNode* node) {
	return std::make_pair(node->x, node->y);
}

std::pair<int, int> Dialogue::getOptionPos(Dialogue::optionNode* node) {
	return std::make_pair(node->x, node->y);
}