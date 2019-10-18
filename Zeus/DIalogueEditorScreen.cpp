#include "DialogueEditorScreen.h"

DialogueEditorScreen::DialogueEditorScreen() {
	Screen();
	this->BGTexture.loadFromFile("Resources/images/questjournal/book/page.png");
	this->BGSprite.setTexture(BGTexture);
	this->BGSprite.setScale((float)(Game::WIDTH / BGTexture.getSize().x), (float)(Game::HEIGHT / BGTexture.getSize().y));
	this->links = sf::VertexArray();
}

void DialogueEditorScreen::update(float deltaTime) {
	
}

void DialogueEditorScreen::draw(sf::RenderWindow& window) {
	this->mousePosition = sf::Mouse::getPosition(window);
	window.draw(this->BGSprite);
}

void DialogueEditorScreen::clearScreen() {
	messages.clear();
	options.clear();
	links.clear();
}

void DialogueEditorScreen::loadNodes() {
	for (Dialogue::msgNode* n : this->activeTree.getMessageNodes()) {
		this->messages.push_back(n);
	}
	for (Dialogue::optionNode* n : this->activeTree.getOptionNodes()) {
		this->options.push_back(n);
	}
	this->linkNodes();
}

void DialogueEditorScreen::changeTrees(Dialogue tree) {
	this->clearScreen();
	this->activeTree = tree;
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