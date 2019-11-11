#include "CombatManager.h"

#include <iostream>

CombatManager::CombatManager() {}

CombatManager& CombatManager::getInstance() {
	static CombatManager instance;
	return instance;
}

void CombatManager::loadEntities(const std::string& fileLoc) {
	std::ifstream i(fileLoc);
	json j;
	i >> j;
	for (int i = 0; i < j.at("characters").size(); i++) {
		try {
			// Load through JSON
			json cJSON = j.at("characters").at(i);
			// Character* c = new Character();
			// c->name = cJSON.at("name");
			// this->characterList.push_back(c);
			// Load into ECS
			entt::registry& registry = GameDataManager::getInstance().getRegistry();
			auto entity = registry.create();
			
			registry.assign<BaseComponent>(entity, std::string(cJSON.at("name")), cJSON.at("type"));

			if (cJSON.at("combat").is_structured()) {
				// Convert and assign a combat component
				json combatJSON = cJSON.at("combat");
				int speed = combatJSON.at("speed");
				registry.assign<CombatComponent>(entity, speed);
			}

			if (cJSON.at("render").is_structured()) {
				// Convert and assign a render component
				json renderJSON = cJSON.at("render");
				sf::Texture* texture = new sf::Texture();
				texture->loadFromFile(renderJSON.at("sprite_sheet"));
				sf::Sprite* sprite = new sf::Sprite();
				sprite->setTexture(*texture);
				int tileSizeX = renderJSON.at("tile_size_x");
				int tileSizeY = renderJSON.at("tile_size_y");
				int tileStartX = renderJSON.at("tile_start_x");
				int tileStartY = renderJSON.at("tile_start_y");
				float scale = renderJSON.at("scale");
				sprite->setScale(scale, scale);
				sprite->setTextureRect(sf::IntRect(tileStartX, tileStartY, tileSizeX, tileSizeY));
				registry.assign<RenderComponent>(entity, texture, sprite, sf::Vector2i(tileSizeX, tileSizeY), sf::Vector2i(tileStartX, tileStartY), scale);
			}
		} catch(std::exception e) {
			std::cout << "Error loading character" << std::endl;
		}
	}
}

void CombatManager::initialize() {
	
}