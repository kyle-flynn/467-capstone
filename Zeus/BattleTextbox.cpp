#include "BattleTextbox.h"
#include "Game.h"
#include "FontManager.h"

#include <iostream>

BattleTextbox::BattleTextbox() :
combatTextbox(sf::Quads, 12),
combatOptionsBox(sf::Quads, 12),
combatActionsBox(sf::Quads, 12),
combatDescriptionBox(sf::Quads, 12),
selectedOption(0),
selectedAction(0),
dualRows(0),
actionReady(false)
{
	std::vector<Move> moves(0);
	this->moveset.moves = moves;
	this->textboxTexture.loadFromFile("Resources/Sprites/spritesheet_combat.png");

	// Load text and fonts
	this->optionOne.setFont(FontManager::getInstance().joystick);
	this->optionTwo.setFont(FontManager::getInstance().joystick);
	this->optionThree.setFont(FontManager::getInstance().joystick);
	this->optionFour.setFont(FontManager::getInstance().joystick);
	this->singleRow.setFont(FontManager::getInstance().joystick);
	this->descriptionText.setFont(FontManager::getInstance().joystick);

	// Set text font sizes
	this->optionOne.setCharacterSize(24);
	this->optionTwo.setCharacterSize(24);
	this->optionThree.setCharacterSize(24);
	this->optionFour.setCharacterSize(24);
	this->singleRow.setCharacterSize(18);
	this->descriptionText.setCharacterSize(18);

	// Set text fill colors
	this->optionOne.setFillColor(sf::Color::Black);
	this->optionTwo.setFillColor(sf::Color::Black);
	this->optionThree.setFillColor(sf::Color::Black);
	this->optionFour.setFillColor(sf::Color::Black);
	this->singleRow.setFillColor(sf::Color::Black);
	this->descriptionText.setFillColor(sf::Color::Black);

	// Set text positions
	float leftPadding = ((Game::WIDTH / 4) * 3);
	float topPadding = 30.0f;
	float height = 90.0f;
	this->optionOne.setPosition(leftPadding, topPadding);
	this->optionTwo.setPosition(leftPadding + ((Game::WIDTH / 8) * 1), topPadding);
	this->optionThree.setPosition(leftPadding, height - topPadding);
	this->optionFour.setPosition(leftPadding + ((Game::WIDTH / 8) * 1), height - topPadding);
	this->singleRow.setPosition(30.0f, topPadding);
	this->descriptionText.setPosition(30.0f, height + 20.0f);

	// Set text strings
	
	this->optionOne.setString("Battle");
	this->optionTwo.setString("Items");
	this->optionThree.setString("Pass");
	this->optionFour.setString("Run");
	this->singleRow.setString("Choose a course of action.");

	this->descriptionText.setString("Description for thing here.");

	this->initBattleBoxVertices();
	this->initOptionsBoxVertices();
	this->initActionsBoxVertices();
	this->initDescriptionBoxVertices();

	this->setSelectedOption(0);
	this->textMode = BattleTextMode::SINGLE_ROW;
	this->battleMode = BattleMode::OPTIONS_CHOOSING;
}

void BattleTextbox::setSelectedOption(int selected) {
	this->selectedOption = selected;
	switch (selected) {
	case 0:
		this->optionOne.setFillColor(sf::Color::Color(0.0f, 119.0f, 255.0f));
		this->optionTwo.setFillColor(sf::Color::Black);
		this->optionThree.setFillColor(sf::Color::Black);
		this->optionFour.setFillColor(sf::Color::Black);
		break;
	case 1:
		this->optionTwo.setFillColor(sf::Color::Color(0.0f, 119.0f, 255.0f));
		this->optionOne.setFillColor(sf::Color::Black);
		this->optionThree.setFillColor(sf::Color::Black);
		this->optionFour.setFillColor(sf::Color::Black);
		break;
	case 2:
		this->optionThree.setFillColor(sf::Color::Color(0.0f, 119.0f, 255.0f));
		this->optionOne.setFillColor(sf::Color::Black);
		this->optionTwo.setFillColor(sf::Color::Black);
		this->optionFour.setFillColor(sf::Color::Black);
		break;
	case 3:
		this->optionFour.setFillColor(sf::Color::Color(0.0f, 119.0f, 255.0f));
		this->optionOne.setFillColor(sf::Color::Black);
		this->optionTwo.setFillColor(sf::Color::Black);
		this->optionThree.setFillColor(sf::Color::Black);
		break;
	default:
		this->optionOne.setFillColor(sf::Color::Color(0.0f, 119.0f, 255.0f));
		this->optionTwo.setFillColor(sf::Color::Black);
		this->optionThree.setFillColor(sf::Color::Black);
		this->optionFour.setFillColor(sf::Color::Black);
	}
}

void BattleTextbox::setSelectedAction(int selected) {
	if (selected < this->dualRows.size() && selected >= 0) {
		for (auto text : this->dualRows) {
			text->setFillColor(sf::Color::Black);
		}
		if (this->battleMode == BattleMode::ACTIONS_CHOOSING_BATTLE) {
			this->descriptionText.setString(this->moveset.moves[selected].description);
		} else if (this->battleMode == BattleMode::ACTIONS_CHOOSING_ITEMS) {
			this->descriptionText.setString(this->items[selected].description);
		}
	
		this->selectedAction = selected;
		this->dualRows[selected]->setFillColor(sf::Color::Color(0.0f, 119.0f, 255.0f));
	}
}

void BattleTextbox::setBattleMode(BattleMode newMode) {
	this->battleMode = newMode;
	switch (newMode) {
	case OPTIONS_CHOOSING:
		//this->textMode = BattleTextMode::ACTIONS_SINGLE_ROW;
		break;
	case ACTIONS_CHOOSING_BATTLE:
		//this->textMode = BattleTextMode::ACTIONS_DUAL_ROW_DUAL_COLUMN;
		break;
	case ACTIONS_CHOOSING_ITEMS:
		//this->textMode = BattleTextMode::ACTIONS_DUAL_ROW_DUAL_COLUMN;
		break;
	case COMBAT_LOG:
		//this->textMode = BattleTextMode::ACTIONS_DUAL_ROW_DUAL_COLUMN;
		break;
	default:
		//this->textMode = BattleTextMode::GENERAL_SINGLE_ROW;
		break;
	}
}

void BattleTextbox::initBattleBoxVertices() {
	float topPadding = 15.0f;
	float sidePadding = 30.0f;
	float outsideWidth = 90.0f;
	float innerWidth = Game::WIDTH - (2 * outsideWidth) - (2 * sidePadding);
	float height = 90.0f;

	this->drawSquare(this->combatTextbox, 0, sidePadding, topPadding, outsideWidth, height);
	this->drawSquare(this->combatTextbox, 4, sidePadding + outsideWidth, topPadding, innerWidth, height);
	this->drawSquare(this->combatTextbox, 8, sidePadding + outsideWidth + innerWidth, topPadding, outsideWidth, height);

	this->assignTexCoords(this->combatTextbox, 0, 0.0f, 0.0f, 30.0f, 30.0f);
	this->assignTexCoords(this->combatTextbox, 4, 30.0f, 0.0f, 30.0f, 30.0f);
	this->assignTexCoords(this->combatTextbox, 8, 60.0f, 0.0f, 30.0f, 30.0f);
}

void BattleTextbox::initOptionsBoxVertices() {
	float topPadding = 15.0f;
	float sidePadding = ((Game::WIDTH / 4) * 3) - 15.0f;
	float outsideWidth = 90.0f;
	float innerWidth = (Game::WIDTH / 4) - (2 * outsideWidth);
	float height = 90.0f;

	this->drawSquare(this->combatOptionsBox, 0, sidePadding, topPadding, outsideWidth, height);
	this->drawSquare(this->combatOptionsBox, 4, sidePadding + outsideWidth, topPadding, innerWidth, height);
	this->drawSquare(this->combatOptionsBox, 8, sidePadding + outsideWidth + innerWidth, topPadding, outsideWidth, height);

	this->assignTexCoords(this->combatOptionsBox, 0, 0.0f, 0.0f, 30.0f, 30.0f);
	this->assignTexCoords(this->combatOptionsBox, 4, 30.0f, 0.0f, 30.0f, 30.0f);
	this->assignTexCoords(this->combatOptionsBox, 8, 60.0f, 0.0f, 30.0f, 30.0f);
}

void BattleTextbox::initActionsBoxVertices() {
	float topPadding = 15.0f;
	float sidePadding = 15.0f;
	float outsideWidth = 90.0f;
	float innerWidth = (((Game::WIDTH / 4) * 3) - 15.0f) - (2 * outsideWidth) - (2 * sidePadding);
	float height = 90.0f;

	this->drawSquare(this->combatActionsBox, 0, sidePadding, topPadding, outsideWidth, height);
	this->drawSquare(this->combatActionsBox, 4, sidePadding + outsideWidth, topPadding, innerWidth, height);
	this->drawSquare(this->combatActionsBox, 8, sidePadding + outsideWidth + innerWidth, topPadding, outsideWidth, height);

	this->assignTexCoords(this->combatActionsBox, 0, 0.0f, 0.0f, 30.0f, 30.0f);
	this->assignTexCoords(this->combatActionsBox, 4, 30.0f, 0.0f, 30.0f, 30.0f);
	this->assignTexCoords(this->combatActionsBox, 8, 60.0f, 0.0f, 30.0f, 30.0f);
}

void BattleTextbox::initDescriptionBoxVertices() {
	float topPadding = 105.0f;
	float sidePadding = 15.0f;
	float outsideWidth = 90.0f;
	float innerWidth = (((Game::WIDTH / 4) * 3) - 15.0f) - (2 * outsideWidth) - (2 * sidePadding);
	float height = 60.0f;

	this->drawSquare(this->combatDescriptionBox, 0, sidePadding, topPadding, outsideWidth, height);
	this->drawSquare(this->combatDescriptionBox, 4, sidePadding + outsideWidth, topPadding, innerWidth, height);
	this->drawSquare(this->combatDescriptionBox, 8, sidePadding + outsideWidth + innerWidth, topPadding, outsideWidth, height);

	this->assignTexCoords(this->combatDescriptionBox, 0, 0.0f, 0.0f, 30.0f, 30.0f);
	this->assignTexCoords(this->combatDescriptionBox, 4, 30.0f, 0.0f, 30.0f, 30.0f);
	this->assignTexCoords(this->combatDescriptionBox, 8, 60.0f, 0.0f, 30.0f, 30.0f);
}

void BattleTextbox::drawSquare(sf::VertexArray& vertices, size_t index, float x, float y, float width, float height) {
	vertices[index].position = sf::Vector2f(x, y);
	vertices[index + 1].position = sf::Vector2f(x + width, y);
	vertices[index + 2].position = sf::Vector2f(x + width, y + height);
	vertices[index + 3].position = sf::Vector2f(x, y + height);
}

void BattleTextbox::assignTexCoords(sf::VertexArray& vertices, size_t index, float x, float y, float width, float height) {
	vertices[index].texCoords = sf::Vector2f(x, y);
	vertices[index + 1].texCoords = sf::Vector2f(x + width, y);
	vertices[index + 2].texCoords = sf::Vector2f(x + width, y + height);
	vertices[index + 3].texCoords = sf::Vector2f(x, y + height);
}

void BattleTextbox::update(float deltaTime) {
	
}

void BattleTextbox::handleEvent(sf::Event event) {
	if (this->battleMode == BattleMode::OPTIONS_CHOOSING) {
		if (event.type == sf::Event::KeyPressed) {
			if (event.text.unicode == sf::Keyboard::Left) {
				if (this->selectedOption < 2) {
					this->setSelectedOption(this->selectedOption == 0 ? 1 : 0);
				} else {
					this->setSelectedOption(this->selectedOption == 2 ? 3 : 2);
				}
			} else if (event.text.unicode == sf::Keyboard::Right) {
				if (this->selectedOption < 2) {
					this->setSelectedOption(this->selectedOption == 0 ? 1 : 0);
				} else {
					this->setSelectedOption(this->selectedOption == 2 ? 3 : 2);
				}
			} else if (event.text.unicode == sf::Keyboard::Up) {
				if (this->selectedOption + 2 > 3) {
					this->setSelectedOption(this->selectedOption - 2);
				} else {
					this->setSelectedOption(this->selectedOption + 2);
				}
			} else if (event.text.unicode == sf::Keyboard::Down) {
				if (this->selectedOption + 2 > 3) {
					this->setSelectedOption(this->selectedOption - 2);
				} else {
					this->setSelectedOption(this->selectedOption + 2);
				}
			} else if (event.text.unicode == sf::Keyboard::Enter) {
				this->executeSelectedOption();
			}
		}
	} else if (this->battleMode == BattleMode::ACTIONS_CHOOSING_BATTLE ||
			   this->battleMode == BattleMode::ACTIONS_CHOOSING_ITEMS) {
		if (event.type == sf::Event::KeyPressed) {
			if (event.text.unicode == sf::Keyboard::Left) {
				this->setSelectedAction(this->selectedAction - 1);
			} else if (event.text.unicode == sf::Keyboard::Right) {
				this->setSelectedAction(this->selectedAction + 1);
			} else if (event.text.unicode == sf::Keyboard::Up) {
				this->setSelectedAction(this->selectedAction - 3);
			} else if (event.text.unicode == sf::Keyboard::Down) {
				this->setSelectedAction(this->selectedAction + 3);
			} else if (event.text.unicode == sf::Keyboard::Enter) {
				this->executeSelectedAction();
			} else if (event.text.unicode == sf::Keyboard::Escape) {
				this->battleMode = BattleMode::OPTIONS_CHOOSING;
				this->textMode = BattleTextMode::SINGLE_ROW;
				this->singleRow.setPosition(30.0f, 30.0f);
				this->singleRow.setString("Choose a course of action.");
			}
		}
	} else if (this->battleMode == BattleMode::COMBAT_LOG) {
		if (event.type == sf::Event::KeyPressed) {
			if (event.text.unicode == sf::Keyboard::Enter) {
				this->battleMode = BattleMode::OPTIONS_CHOOSING;
				this->textMode = BattleTextMode::SINGLE_ROW;
				this->singleRow.setPosition(30.0f, 30.0f);
				this->singleRow.setString("Choose a course of action.");
			}
		}
	}
}

void BattleTextbox::updateBattleText(const std::string& text) {
	this->battleMode = BattleMode::COMBAT_LOG;
	this->singleRow.setString(text);
	/*if (this->textMode == BattleTextMode::SINGLE_ROW_COMBAT) {
		this->singleRow.setPosition(45.0f, 30.0f);
	} else {
		this->singleRow.setPosition(30.0f, 30.0f);
	}*/
	this->singleRow.setPosition(45.0f, 30.0f);
	this->checkForNewlines(text);
}

// TODO
void BattleTextbox::checkForNewlines(const std::string& text) {
	/*
	for (int i = 0; i < this->battleText.getString().getSize(); i++) {
		float x = this->battleText.findCharacterPos(i).x;
		float maxWidth = this->textboxSprite.getGlobalBounds().width - this->battleText.getCharacterSize();
		if (x > maxWidth) {
			std::string newString = std::string(text).insert(i, "-\n");
			if (text[i] == ' ') {
				newString = newString.replace(i + 2, 1, "");
			}
			this->battleText.setString(newString);
			break;
			// this->checkForNewlines(newString);
		}
	}
	*/
}

void BattleTextbox::executeSelectedOption() {
	switch (this->selectedOption) {
	case 0:
		this->battleMode = BattleMode::ACTIONS_CHOOSING_BATTLE;
		this->renderMoveset();
		break;
	case 1:
		this->battleMode = BattleMode::ACTIONS_CHOOSING_ITEMS;
		this->renderItems();
		break;
	case 2:
		this->textMode = BattleTextMode::SINGLE_ROW_COMBAT;
		this->dualRows.clear();
		this->updateBattleText("You've decided to take a pass on that one.");
		break;
	case 3:
		this->textMode = BattleTextMode::SINGLE_ROW_COMBAT;
		this->dualRows.clear();
		this->updateBattleText("Couldn't run away!");
		break;
	default:
		// Do nothing.
		break;
	}
}

void BattleTextbox::executeSelectedAction() {
	this->action.move = this->moveset.moves[this->selectedAction];
	this->actionReady = true;
}

void BattleTextbox::renderItems() {
	this->dualRows.clear();
	this->textMode = BattleTextMode::DUAL_ROW_DUAL_COLUMNS;
	int colCount = 0;
	int rowCount = 0;
	for (int i = 0; i < this->items.size(); i++) {
		sf::Text* itemText = new sf::Text();
		itemText->setFont(FontManager::getInstance().joystick);
		itemText->setCharacterSize(18);
		itemText->setFillColor(sf::Color::Black);
		if (colCount == 3) {
			colCount = 0;
			rowCount++;
		}

		itemText->setPosition(30.0f + ((i % 3) * 320.0f), 30.0f + (rowCount * 20.0f));
		itemText->setString(this->items[i].name);
		colCount++;
		this->dualRows.push_back(itemText);
	}
	this->setSelectedAction(0);
}

void BattleTextbox::renderMoveset() {
	this->dualRows.clear();
	this->textMode = BattleTextMode::DUAL_ROW_DUAL_COLUMNS;
	int colCount = 0;
	int rowCount = 0;
	for (int i = 0; i < this->moveset.moves.size(); i++) {
		sf::Text* itemText = new sf::Text();
		itemText->setFont(FontManager::getInstance().joystick);
		itemText->setCharacterSize(18);
		itemText->setFillColor(sf::Color::Black);
		if (colCount == 3) {
			colCount = 0;
			rowCount++;
		}

		itemText->setPosition(30.0f + ((i % 3) * 320.0f), 30.0f + (rowCount * 20.0f));
		itemText->setString(this->moveset.moves[i].name);
		colCount++;
		this->dualRows.push_back(itemText);
	}
	this->setSelectedAction(0);
}

void BattleTextbox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = &this->textboxTexture;

	// target.draw(this->textboxSprite, states);
	// target.draw(this->battleText, states);
	if (this->battleMode == BattleMode::OPTIONS_CHOOSING ||
		this->battleMode == BattleMode::ACTIONS_CHOOSING_BATTLE ||
		this->battleMode == BattleMode::ACTIONS_CHOOSING_ITEMS) {
		target.draw(this->combatOptionsBox, states);
		target.draw(this->combatActionsBox, states);
		target.draw(this->optionOne, states);
		target.draw(this->optionTwo, states);
		target.draw(this->optionThree, states);
		target.draw(this->optionFour, states);
		if (this->textMode == BattleTextMode::SINGLE_ROW) {
			target.draw(this->singleRow);
		} else if (this->textMode == BattleTextMode::DUAL_ROW_DUAL_COLUMNS ||
				   this->textMode == BattleTextMode::DUAL_ROW) {
			for (auto text : this->dualRows) {
				target.draw(*text, states);
			}
		}
		if (this->battleMode == BattleMode::ACTIONS_CHOOSING_BATTLE ||
			(this->battleMode == BattleMode::ACTIONS_CHOOSING_ITEMS &&
			 this->items.size() > 0)) {
			target.draw(this->combatDescriptionBox, states);
			target.draw(this->descriptionText, states);
		}
	} else if (this->battleMode == BattleMode::COMBAT_LOG) {
		target.draw(this->combatTextbox, states);
		target.draw(this->singleRow, states);
	}
}

void BattleTextbox::reset() {
	this->actionReady = false;
	this->setSelectedOption(0);
}

void BattleTextbox::setEntity(entt::entity& entity) {
	entt::registry& registry = GameDataManager::getInstance().getRegistry();
	this->action.entity = entity;
	this->moveset = registry.get<MovesetComponent>(entity);
}

void BattleTextbox::setItems(std::vector<Item> items) {
	this->items = items;
}

bool BattleTextbox::hasAction() {
	return this->actionReady;
}

Action BattleTextbox::getAction() {
	return this->action;
}