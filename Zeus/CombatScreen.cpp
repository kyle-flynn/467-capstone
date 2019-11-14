#include "CombatScreen.h"

#include "CombatManager.h"

#include <iostream>

CombatScreen::CombatScreen() :
	textbox(),
	textDisplayChange(false),
	lastDisplay(false),
	enemyTurn(false)
{
	CombatManager::getInstance().setBattleTextbox(&this->textbox);
	CombatManager::getInstance().loadEntities("Resources/test_characters.json");
	entt::registry& registry = GameDataManager::getInstance().getRegistry();
	auto view = registry.view<BaseComponent, RenderComponent, CombatComponent, MovesetComponent>();
	int count = 0;
	for (auto entity : view) {
		auto& baseC = view.get<BaseComponent>(entity);
		auto& combatC = view.get<CombatComponent>(entity);
		if (baseC.entityType > -1) {
			auto& renderC = view.get<RenderComponent>(entity);
			PlayerCombatDisplay* display = new PlayerCombatDisplay(std::string(baseC.name), *renderC.sprite);
			display->setPosition((((float)count) * display->getWidth()) + (count > 0 ? 50.0f : 0.0f), 592.0f);
			display->setCombatComponent(combatC);
			this->combatDisplays.push_back(display);
			count++;
		}

		if (combatC.combatId == CombatManager::getInstance().getCombatId() && baseC.entityType > -1) {
			this->textbox.setEntity(entity);
			for (auto display : this->combatDisplays) {
				if (display->getCombatComponent().combatId == combatC.combatId) {
					display->setActive(true);
				} else {
					display->setActive(false);
				}
			}
		}
	}

	// Finally, initialize combat sequence after everything is setup.
	CombatManager::getInstance().initialize();
}

void CombatScreen::update(float deltaTime) {
	for (auto display : this->combatDisplays) {
		display->update(deltaTime);
	}
	this->textbox.update(deltaTime);
	
	if (this->textbox.hasAction()) {
		Action a = this->textbox.getAction();
		CombatManager::getInstance().processPlayerAction(a);
		CombatManager::getInstance().takeTurn();
		this->textbox.reset();
		if (CombatManager::getInstance().checkForEnemyTurn()) {
			CombatManager::getInstance().processEnemyAction();
			CombatManager::getInstance().takeTurn();
			enemyTurn = true;
		}
	}

	if (this->textDisplayChange) {
		entt::registry& registry = GameDataManager::getInstance().getRegistry();
		int count = 0;
		auto view = registry.view<BaseComponent, RenderComponent, CombatComponent, MovesetComponent>();
		for (auto entity : view) {
			auto& baseC = view.get<BaseComponent>(entity);
			auto& combatC = view.get<CombatComponent>(entity);
			if (combatC.combatId == CombatManager::getInstance().getCombatId() && baseC.entityType > -1) {
				this->textbox.setEntity(entity);
				for (auto display : this->combatDisplays) {
					if (display->getCombatComponent().combatId == combatC.combatId) {
						display->setActive(true);
					} else {
						display->setActive(false);
					}
				}
			}
		}
	}

	this->textDisplayChange = (!this->textbox.hasText() && this->lastDisplay);
	this->lastDisplay = this->textbox.hasText();
}

void CombatScreen::draw(sf::RenderWindow& window) {
	for (auto display : this->combatDisplays) {
		window.draw(*display);
	}
	
	entt::registry& registry = GameDataManager::getInstance().getRegistry();
	auto view = registry.view<BaseComponent, RenderComponent, CombatComponent>();
	for (auto entity : view) {
		auto& baseC = view.get<BaseComponent>(entity);
		if (baseC.entityType == -1) {
			auto& renderC = view.get<RenderComponent>(entity);
			float spriteW = renderC.sprite->getLocalBounds().width;
			float spriteH = renderC.sprite->getLocalBounds().height;
			renderC.sprite->setPosition((Game::WIDTH / 2) - (spriteW), (Game::HEIGHT / 2) - (spriteH));
			window.draw(*renderC.sprite);
		}
	}

	window.draw(this->textbox);
}

void CombatScreen::handleEvent(sf::Event event) {
	this->textbox.handleEvent(event);
}