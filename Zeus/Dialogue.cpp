#include "Dialogue.h"

/*
Default constructor.
*/
Dialogue::Dialogue() {
	this->entityName = "DEFAULT";
	this->nodes;
	this->optionNodes;
}

/*
Constructor which gives Dialogue tree specific name to determine character
*/
Dialogue::Dialogue(std::string name) {
	this->entityName = name;
	this->nodes;
	this->optionNodes;
}

/*
Adds a new message node to the current trees nodes list.
xPos = the x position in the dialogue editor window (set to 0 by default)
yPos = the y position in the dialogue editor window (set to 0 by default)
returns newly created message node.
*/
Dialogue::msgNode* Dialogue::addDialogueNode(int xPos, int yPos) {
	Dialogue::msgNode* newNode = new Dialogue::msgNode;
	newNode->x = xPos;
	newNode->y = yPos;
	newNode->nodeID = nodes.size() + 1;
	nodes.push_back(newNode);
}

/*
Edits a message node if values entered, all values set to NULL by default.
node = message node to edit
message = new message to display when reached
xPos = new x position in editor window
yPos = new y position in editor window
*/
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

/*
Adds a new option node to the current trees optionNodes list.
xPos = the x position in dialogue editor window (set to 0 by default)
yPos = the y position in dialogue editor window (set to 0 by default)
returns newly created option node
*/
Dialogue::optionNode* Dialogue::addOptionNode(int xPos, int yPos) {
	Dialogue::optionNode* newNode = new Dialogue::optionNode;
	newNode->x = xPos;
	newNode->y = yPos;
	newNode->nodeID = optionNodes.size() + 1;
	optionNodes.push_back(newNode);
}

/*
Edits an option node if values entered, all values set to NULL or nullptr by default.
node = option node to edit
message = new message to display as header
returnCode = code used to determine next step in dialogue tree (see dialogue.h for deatils)
xPos = new x position in editor window
yPos = new y position in editor window
next = message node to point to if option continues down tree
*/
void Dialogue::editOptionNode(Dialogue::optionNode* node, std::string message = NULL, int returnCode = NULL, int xPos = NULL, int yPos = NULL, Dialogue::msgNode* next = nullptr) {
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
	if (next != nullptr) {
		node->next = next;
		node->nextID = next->nodeID;
		next->previousID = node->nodeID;
	}
}

/*
Links 2 message nodes together by creating a new option node and immediately connecting all 3 nodes.
node1 = originating message node
node2 = destination message node
*/
void Dialogue::linkDialogue(Dialogue::msgNode* node1, Dialogue::msgNode* node2) {
	int newXPos = (node1->x + node2->x) / 2;
	int newYPos = (node1->y + node2->y) / 2;
	Dialogue::optionNode* newNode = addOptionNode(newXPos, newYPos);
	node1->options.push_back(newNode);
	node1->optionIDs.push_back(newNode->nodeID);
	newNode->next = node2;
	newNode->nextID = node2->nodeID;
	newNode->previousID = node1->nodeID;
	node2->previousID = newNode->nodeID;
}

/*
Links dialogue to an existing option node.
dNode = originating message node
optNode = option node to link to
*/
void Dialogue::linkDialogueToOption(Dialogue::msgNode* dNode, Dialogue::optionNode* optNode) {
	dNode->options.push_back(optNode);
	dNode->optionIDs.push_back(optNode->nodeID);
	optNode->previousID = dNode->nodeID;
}

/*
Getter for returnCode of a node.
node = option node requested
returns an int returnCode
*/
int Dialogue::getReturnCode(Dialogue::optionNode* node) {
	return node->returnCode;
}

/*
Getter for message of a dialogue node.
node = message node requested
returns a string
*/
std::string Dialogue::getMessage(Dialogue::msgNode* node) {
	return node->message;
}

/*
Getter for options of a message node.
node = message node requested
returns a vector of strings
*/
std::vector<std::string> Dialogue::getOptions(Dialogue::msgNode* node) {
	std::vector<std::string> optionList;
	for (auto o : node->options) {
		optionList.push_back(o->optionMsg);
	}
	return optionList;
}

/*
Getter for message node position.
node = requested message node
returns a pair of ints for editor window
*/
std::pair<int, int> Dialogue::getDialoguePos(Dialogue::msgNode* node) {
	return std::make_pair(node->x, node->y);
}

/*
Getter for option node position.
node = requested option node
returns a pair of ints for editor window*/
std::pair<int, int> Dialogue::getOptionPos(Dialogue::optionNode* node) {
	return std::make_pair(node->x, node->y);
}

/*
Removes an existing message node and severs existing connects to that node freeing up memory as it goes.
node = requested message node to be deleted
*/
void Dialogue::deleteDialogueNode(Dialogue::msgNode* node) {
	for (auto o : node->options) {
		o->previousID = NULL;
	}
	if (node->previousID != NULL) {
		optionNodes.at(node->previousID)->nextID = NULL;
		optionNodes.at(node->previousID)->next = nullptr;
	}
	delete nodes.at(node->nodeID);
}

// TODO
void Dialogue::deleteOptionNode(Dialogue::optionNode* node) {
}