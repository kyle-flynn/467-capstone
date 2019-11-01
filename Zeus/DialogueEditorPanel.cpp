#include "DialogueEditorPanel.h"

DialogueEditorPanel::DialogueEditorPanel() {

	//this->screen = dynamic_cast<DialogueEditorScreen&>(ScreenManager::getInstance().getScreen());

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
	this->messageBox->setText("");
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

DialogueEditorPanel& DialogueEditorPanel::getInstance() {
	static DialogueEditorPanel instance;
	return instance;
}

tgui::Panel::Ptr DialogueEditorPanel::getPanel() {
	return this->panel;
}

void DialogueEditorPanel::messageHandler() {
	dynamic_cast<DialogueEditorScreen&>(ScreenManager::getInstance().getScreen()).addMessage();
}

void DialogueEditorPanel::optionHandler() {
	dynamic_cast<DialogueEditorScreen&>(ScreenManager::getInstance().getScreen()).addOption();
}

void DialogueEditorPanel::deleteHandler() {
	dynamic_cast<DialogueEditorScreen&>(ScreenManager::getInstance().getScreen()).deleteNode();
}

void DialogueEditorPanel::editHandler() {
	int returnCode;
	try {
		returnCode = std::stoi(returnCodeBox->getText().toAnsiString());
	}
	catch (...) {
		returnCode = 0;
	}
	dynamic_cast<DialogueEditorScreen&>(ScreenManager::getInstance().getScreen()).editNode(this->messageBox->getText().toAnsiString(), returnCode);
}

void DialogueEditorPanel::updatePanel(Dialogue::msgNode* mNode, Dialogue::optionNode* oNode) {
	if (mNode != nullptr) {
		messageBox->setText(sf::String(mNode->message));
		returnCodeBox->setText(sf::String("0"));
	}
	else if (oNode != nullptr) {
		messageBox->setText(sf::String(oNode->optionMsg));
		returnCodeBox->setText(sf::String(std::to_string(oNode->returnCode)));
	}
}