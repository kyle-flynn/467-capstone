#include "CombatScreen.h"

#include "CombatManager.h"

#include <iostream>

CombatScreen::CombatScreen() :
	textbox()
{
	CombatManager::getInstance().loadEntities("Resources/test_characters.json");
	entt::registry& registry = GameDataManager::getInstance().getRegistry();
	auto view = registry.view<BaseComponent, RenderComponent, CombatComponent>();
	int count = 0;
	for (auto entity : view) {
		auto& baseC = view.get<BaseComponent>(entity);
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
	this->textbox.update(deltaTime);
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