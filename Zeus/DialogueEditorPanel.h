#pragma once

#include <TGUI/TGUI.hpp>
#include "DIalogueEditorScreen.h"
#include "ScreenManager.h"
#include <iostream>

class DialogueEditorPanel {

public:
	
	static DialogueEditorPanel& getInstance(DialogueEditorScreen* screen = nullptr);
	tgui::Panel::Ptr getPanel();
	void updateNode(Dialogue::msgNode* mNode = nullptr, Dialogue::optionNode* oNode = nullptr);

private:

	DialogueEditorScreen* screen;
	Dialogue::msgNode* activeMNode;
	Dialogue::optionNode* activeONode;
	tgui::Panel::Ptr panel;
	tgui::EditBox::Ptr headerBox, returnBox;
	tgui::TextBox::Ptr messageBox, returnCodeBox;
	tgui::Button::Ptr messageButton, optionButton, deleteButton;

	DialogueEditorPanel(DialogueEditorScreen* screen);
	void messageHandler();
	void optionHandler();
	void deleteHandler();
	void editHandler();
};

