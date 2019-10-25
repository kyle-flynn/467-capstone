#include "DialogueEditorScreen.h"
#include <iostream>

DialogueEditorScreen::DialogueEditorScreen() {
	Screen();
	this->BGTexture.loadFromFile("Resources/images/questjournal/book/page.png");
	this->BGSprite.setTexture(BGTexture);
	this->BGSprite.setScale((float)(Game::WIDTH / BGTexture.getSize().x), (float)(Game::HEIGHT / BGTexture.getSize().y));
	this->links = sf::VertexArray();
	if (this->dialogueTrees.empty()) {
		Dialogue* newTree = new Dialogue();
		this->activeTree = newTree;
		this->dialogueTrees.push_back(newTree);
	}
}

void DialogueEditorScreen::update(float deltaTime) {
	for (DialogueEditorMessageNode n : this->messages) {
		n.update(deltaTime, this->mousePosition);
		if (n.isSelected) {
			this->changeActive(n.getNode(), nullptr);
		}
	}
	for (DialogueEditorOptionNode n : this->options) {
		n.update(deltaTime, this->mousePosition);
		if (n.isSelected) {
			this->changeActive(nullptr, n.getNode());
		}
	}
}

void DialogueEditorScreen::draw(sf::RenderWindow& window) {
	this->mousePosition = sf::Mouse::getPosition(window);
	window.draw(this->BGSprite);
	//TODO DRAW CONNECTING LINES
	for (DialogueEditorMessageNode n : this->messages) {
		window.draw(n);
	}
	for (DialogueEditorOptionNode n : this->options) {
		window.draw(n);
	}
}

void DialogueEditorScreen::addMessage(sf::Vector2f loc) {
	this->messages.push_back(this->activeTree->addDialogueNode(loc));
}

void DialogueEditorScreen::addOption(sf::Vector2f loc) {
	this->options.push_back(this->activeTree->addOptionNode(loc));
	this->options.push_back(this->activeTree->addOptionNode(loc));
}

void DialogueEditorScreen::deleteNode() {
	/*if (this->activeMNode != nullptr) {
		for (int i = 0; i < this->messages.size(); i++) {
			if (this->messages.at(i).getNode()->nodeID == this->activeMNode->nodeID) {
				this->messages.erase(this->messages.begin() + i);
				this->messages.push_back(nullptr);
				this->activeTree->deleteDialogueNode(this->activeMNode);
				break;
			}
		}
	}
	else if (this->activeONode != nullptr) {
		for (int i = 0; i < this->options.size(); i++) {
			if (options.at(i).getNode()->nodeID == this->activeONode->nodeID) {
				options.erase(options.begin() + i);
				options.push_back(nullptr);
				this->activeTree->deleteOptionNode(this->activeONode);
				break;
			}
		}
	}*/
	this->changeActive(nullptr, nullptr);
}

void DialogueEditorScreen::editNode(std::string message, int returnCode) {
	if (this->activeMNode != nullptr) {
		this->activeTree->editDialoguenode(this->activeMNode, message);
		for (DialogueEditorMessageNode n : this->messages) {
			if (n.getNode()->nodeID == this->activeMNode->nodeID) {
				n.getNode()->message = message;
				break;
			}
		}
	}
	else if (this->activeONode != nullptr) {
		this->activeTree->editOptionNode(this->activeONode, message, returnCode);
		for (DialogueEditorOptionNode n : this->options) {
			if (n.getNode()->nodeID == this->activeONode->nodeID) {
				n.getNode()->optionMsg = message;
				n.getNode()->returnCode = returnCode;
				break;
			}
		}
	}
}

void DialogueEditorScreen::clearScreen() {
	messages.clear();
	options.clear();
	links.clear();
}

void DialogueEditorScreen::loadNodes() {
	for (Dialogue::msgNode* n : this->activeTree->getMessageNodes()) {
		this->messages.push_back(DialogueEditorMessageNode(n));
	}
	for (Dialogue::optionNode* n : this->activeTree->getOptionNodes()) {
		this->options.push_back(DialogueEditorOptionNode(n));
	}
	this->linkNodes();
}

void DialogueEditorScreen::changeTrees(Dialogue* tree) {
	this->clearScreen();
	this->activeTree = tree;
}

void DialogueEditorScreen::newTree() {
	Dialogue* newTree = new Dialogue();
	this->dialogueTrees.push_back(newTree);
	this->changeTrees(newTree);
}

void DialogueEditorScreen::linkNodes() {
	for (DialogueEditorMessageNode m : this->messages) {
		for (Dialogue::optionNode* o : m.getNode()->options) {
			links.append(m.getPosition());
			links.append(this->getOptionNode(o).getPosition());
		}
	}
	for (DialogueEditorOptionNode o : this->options) {
		auto node = o.getNode();
		if (node->nextID != NULL) {
			links.append(o.getPosition());
			links.append(this->getMsgNode(o.getNode()->next).getPosition());
		}
	}
}

void DialogueEditorScreen::loadTrees() {
	//TODO
}

DialogueEditorMessageNode DialogueEditorScreen::getMsgNode(Dialogue::msgNode* node) {
	for (DialogueEditorMessageNode n : this->messages) {
		int nodeID = n.getNode()->nodeID;
		if (n.getNode()->nodeID == node->nodeID) {
			return n;
		}
	}
	return NULL;
}

DialogueEditorOptionNode DialogueEditorScreen::getOptionNode(Dialogue::optionNode* node) {
	for (DialogueEditorOptionNode n : this->options) {
		if (n.getNode()->nodeID = node->nodeID) {
			return n;
		}
	}
	return NULL;
}

void DialogueEditorScreen::changeActive(Dialogue::msgNode* mNode, Dialogue::optionNode* oNode) {
	this->activeMNode = mNode;
	this->activeONode = oNode;
	DialogueEditorPanel::getInstance().updatePanel(mNode, oNode);
}

tgui::Panel::Ptr DialogueEditorScreen::getPanel() {
	//return panel->getPanel();
	return NULL;
}
