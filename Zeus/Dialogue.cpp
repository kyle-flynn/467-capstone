#include "Dialogue.h"
#include <iostream>

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
Dialogue::msgNode* Dialogue::addDialogueNode(sf::Vector2f loc) {
	Dialogue::msgNode* newNode = new Dialogue::msgNode;
	newNode->loc = loc;
	newNode->nodeID = nodes.size() + 1;
	nodes.push_back(newNode);
	return newNode;
}

/*
Edits a message node if values entered, all values set to NULL by default.
node = message node to edit
message = new message to display when reached
xPos = new x position in editor window
yPos = new y position in editor window
*/
void Dialogue::editDialoguenode(Dialogue::msgNode* node, std::string message, sf::Vector2f loc) {
	if (!message.empty()) {
		node->message = message;
	}
	if (loc.x != -1) {
		node->loc = loc;
	}
}

/*
Adds a new option node to the current trees optionNodes list.
xPos = the x position in dialogue editor window (set to 0 by default)
yPos = the y position in dialogue editor window (set to 0 by default)
returns newly created option node
*/
Dialogue::optionNode* Dialogue::addOptionNode(sf::Vector2f loc) {
	Dialogue::optionNode* newNode = new Dialogue::optionNode;
	newNode->loc = loc;
	newNode->nodeID = optionNodes.size() + 1;
	newNode->returnCode = 0;
	optionNodes.push_back(newNode);
	return newNode;
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
void Dialogue::editOptionNode(Dialogue::optionNode* node, std::string message, int returnCode, sf::Vector2f loc, Dialogue::msgNode* next) {
	if (!message.empty()) {
		node->optionMsg = message;
	}
	if (returnCode != NULL) {
		node->returnCode = returnCode;
	}
	if (loc.x != -1) {
		node->loc = loc;
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
	float newXPos = (node1->loc.x + node2->loc.x) / 2;
	float newYPos = (node1->loc.y + node2->loc.y) / 2;
	Dialogue::optionNode* newNode = addOptionNode(sf::Vector2f(newXPos, newYPos));
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
sf::Vector2f Dialogue::getDialoguePos(Dialogue::msgNode* node) {
	return node->loc;
}

/*
Getter for option node position.
node = requested option node
returns a pair of ints for editor window*/
sf::Vector2f Dialogue::getOptionPos(Dialogue::optionNode* node) {
	return node->loc;
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
		optionNodes.at(node->previousID - 1)->nextID = NULL;
		optionNodes.at(node->previousID - 1)->next = nullptr;
	}
	nodes.erase(nodes.begin() + node->nodeID - 1);
	nodes.push_back(nullptr);
}

void Dialogue::deleteOptionNode(Dialogue::optionNode* node) {
	if (node->previousID != NULL) {
		Dialogue::msgNode* previous = nodes.at(node->nodeID - 1);
		for (int i = 0; i < previous->options.size(); i++) {
			if (previous->options.at(i)->nodeID = node->nodeID) {
				previous->options.erase(previous->options.begin() + i);
				previous->optionIDs.erase(previous->optionIDs.begin() + i);
				break;
			}
		}
	}
	optionNodes.erase(optionNodes.begin() + node->nodeID - 1);
	optionNodes.push_back(nullptr);
}

std::vector<Dialogue::msgNode*> Dialogue::getMessageNodes() {
	return nodes;
}

std::vector<Dialogue::optionNode*> Dialogue::getOptionNodes() {
	return optionNodes;
}

std::string Dialogue::getTreeName() {
	return entityName;
}

void Dialogue::printTree() {
	for (Dialogue::msgNode* n : nodes) {
		std::cout << n << std::endl;
	}
	for (Dialogue::optionNode* n : optionNodes) {
		std::cout << n << std::endl;
	}
}