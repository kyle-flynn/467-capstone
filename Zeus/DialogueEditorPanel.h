#pragma once

#include <TGUI/TGUI.hpp>
#include "DIalogueEditorScreen.h"
#include "ScreenManager.h"
#include <iostream>

class DialogueEditorPanel {

public:
	
	static DialogueEditorPanel& getInstance();
	tgui::Panel::Ptr getPanel();
	void updatePanel(Dialogue::msgNode* mNode = nullptr, Dialogue::optionNode* oNode = nullptr);

private:

	//DialogueEditorScreen screen;

	tgui::Panel::Ptr panel;
	tgui::EditBox::Ptr headerBox, returnBox;
	tgui::TextBox::Ptr messageBox, returnCodeBox;
	tgui::Button::Ptr messageButton, optionButton, deleteButton;
	
	DialogueEditorPanel();
	void messageHandler();
	void optionHandler();
	void deleteHandler();
	void editHandler();
};

