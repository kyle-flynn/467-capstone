#include "DialogueEditorPanel.h"

DialogueEditorPanel::DialogueEditorPanel(DialogueEditorScreen* screen) {

	this->screen = screen;

	this->panel = tgui::Panel::create();
	this->panel->setSize(200, 300);
	this->panel->setPosition(40, 25);

	this->headerBox = tgui::EditBox::create();
	this->headerBox->setSize(200, 20);
	this->headerBox->setPosition(0, 0);
	this->headerBox->setDefaultText("Message:");
	this->headerBox->setReadOnly(true);

	this->messageBox = tgui::TextBox::create();
	this->messageBox->setSize(200, 160);
	this->messageBox->setPosition(0, 20);
	this->messageBox->setText("Insert message/option text here...");
	this->messageBox->connect("textchanged", &DialogueEditorPanel::editHandler, this);

	this->returnBox = tgui::EditBox::create();
	this->returnBox->setSize(100, 20);
	this->returnBox->setPosition(0, 180);
	this->returnBox->setDefaultText("Return Code:");
	this->returnBox->setReadOnly(true);
	this->returnCodeBox = tgui::TextBox::create();
	this->returnCodeBox->setSize(100, 20);
	this->returnCodeBox->setPosition(100, 180);
	this->returnCodeBox->setText("0");
	this->returnCodeBox->connect("textchanged", &DialogueEditorPanel::editHandler, this);
	
	this->messageButton = tgui::Button::create();
	this->messageButton->setSize(80, 30);
	this->messageButton->setPosition(10, 210);
	this->messageButton->setTextSize(10);
	this->messageButton->setText("New Message");
	this->messageButton->connect("pressed", &DialogueEditorPanel::messageHandler, this);

	this->optionButton = tgui::Button::create();
	this->optionButton->setSize(80, 30);
	this->optionButton->setPosition(110, 210);
	this->optionButton->setTextSize(10);
	this->optionButton->setText("New Option");
	this->optionButton->connect("pressed", &DialogueEditorPanel::optionHandler, this);

	this->deleteButton = tgui::Button::create();
	this->deleteButton->setSize(80, 30);
	this->deleteButton->setPosition(60, 260);
	this->deleteButton->setTextSize(10);
	this->deleteButton->setText("Delete");
	this->deleteButton->connect("pressed", &DialogueEditorPanel::deleteHandler, this);

	this->panel->add(headerBox);
	this->panel->add(messageBox);
	this->panel->add(returnBox);
	this->panel->add(returnCodeBox);
	this->panel->add(messageButton);
	this->panel->add(optionButton);
	this->panel->add(deleteButton);
}

DialogueEditorPanel& DialogueEditorPanel::getInstance(DialogueEditorScreen* screen) {
	static DialogueEditorPanel instance(screen);
	return instance;
}

tgui::Panel::Ptr DialogueEditorPanel::getPanel() {
	return DialogueEditorPanel::getInstance().panel;
}

void DialogueEditorPanel::messageHandler() {
	this->screen->activeTree->addDialogueNode();
}

void DialogueEditorPanel::optionHandler() {
	this->screen->activeTree->addOptionNode();
}

void DialogueEditorPanel::deleteHandler() {
	if (this->activeMNode != nullptr) {
		this->screen->activeTree->deleteDialogueNode(this->activeMNode);
	}
	else if (this->activeONode != nullptr) {
		this->screen->activeTree->deleteOptionNode(this->activeONode);
	}
}

void DialogueEditorPanel::editHandler() {
	if (this->activeMNode != nullptr) {
		this->activeMNode->message = this->messageBox->getText().toAnsiString();
	}
	else if (this->activeONode != nullptr) {
		this->activeONode->optionMsg = this->messageBox->getText().toAnsiString();
		this->activeONode->returnCode = std::stoi(this->returnCodeBox->getText().toAnsiString());
	}
}

void DialogueEditorPanel::updateNode(Dialogue::msgNode* mNode, Dialogue::optionNode* oNode) {
	this->activeMNode = mNode;
	this->activeONode = oNode;
}