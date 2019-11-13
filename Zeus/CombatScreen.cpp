#include "CombatScreen.h"

#include "CombatManager.h"

#include <iostream>

CombatScreen::CombatScreen() :
	textbox()
{
	CombatManager::getInstance().loadEntities("Resources/test_characters.json");
	entt::registry& registry = GameDataManager::getInstance().getRegistry();
	auto view = registry.view<BaseComponent, RenderComponent, CombatComponent, MovesetComponent>();
	int count = 0;
	int highestSpeed = 0;
	for (auto entity : view) {
		auto& baseC = view.get<BaseComponent>(entity);
		auto& combatC = view.get<CombatComponent>(entity);
		if (combatC.speed >= highestSpeed && baseC.entityType > -1) {
			highestSpeed = combatC.speed;
			auto& movesC = view.get<MovesetComponent>(entity);
			this->textbox.setEntity(entity);
		}
		if (baseC.entityType > -1) {
			auto& renderC = view.get<RenderComponent>(entity);
			PlayerCombatDisplay* display = new PlayerCombatDisplay(std::string(baseC.name), *renderC.sprite);
			display->setPosition((((float)count) * display->getWidth()) + (count > 0 ? 50.0f : 0.0f), 592.0f);
			this->combatDisplays.push_back(display);
			count++;
		}
	}
}

void CombatScreen::update(float deltaTime) {
	for (auto display : this->combatDisplays) {
		display->update(deltaTime);
	}
	this->textbox.update(deltaTime);
	if (this->textbox.hasAction()) {
		entt::registry& registry = GameDataManager::getInstance().getRegistry();
		Action a = this->textbox.getAction();
		entt::entity& entity = a.entity;
		auto& baseC = registry.get<BaseComponent>(entity);
		this->textbox.reset();
		if (a.type == TYPE_ITEM) {
			const std::string desc = baseC.name + " used " + a.item.name + ".";
			this->textbox.updateBattleText(desc);
		} else if (a.type == TYPE_BATTLE) {
			const std::string desc = baseC.name + " used " + a.move.name + ". " + std::to_string(a.move.damage) + "HP of damage.";
			this->textbox.updateBattleText(desc);
		}
	}
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