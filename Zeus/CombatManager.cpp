#include "CombatManager.h"

#include <iostream>

CombatManager::CombatManager() :
	combatTurn(0)
{}

CombatManager& CombatManager::getInstance() {
	static CombatManager instance;
	return instance;
}

void CombatManager::loadEntities(const std::string& fileLoc) {
	entt::registry& registry = GameDataManager::getInstance().getRegistry();
	registry.sort<CombatComponent>([](const CombatComponent& c1, const CombatComponent& c2) {
		return c1.speed < c2.speed;
	});

	std::ifstream i(fileLoc);
	json j;
	i >> j;
	unsigned int combatCount = 0;
	for (int i = 0; i < j.at("characters").size(); i++) {
		try {
			// Load through JSON
			json cJSON = j.at("characters").at(i);
			// Character* c = new Character();
			// c->name = cJSON.at("name");
			// this->characterList.push_back(c);
			// Load into ECS
			auto entity = registry.create();
			
			registry.assign<BaseComponent>(entity, std::string(cJSON.at("name")), cJSON.at("type"));

			if (cJSON.at("combat").is_structured()) {
				// Convert and assign a combat component
				json combatJSON = cJSON.at("combat");
				int speed = combatJSON.at("speed");
				registry.assign<CombatComponent>(entity, combatCount++, speed);
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

			if (cJSON.at("health").is_structured()) {
				json healthJSON = cJSON.at("health");
				int max = healthJSON.at("max");
				int current = healthJSON.at("current");
				registry.assign<HealthComponent>(entity, current, max);
			}

			if (cJSON.at("moveset").is_structured() &&
				cJSON.at("moveset").is_array()) {
				json movesJSON = cJSON.at("moveset");
				std::vector<Move> moves;
				for (int i = 0; i < movesJSON.size(); i++) {
					json moveJSON = movesJSON.at(i);
					Move move;
					move.name = moveJSON.at("name");
					move.damage = moveJSON.at("damage");
					move.description = moveJSON.at("description");
					moves.push_back(move);
				}
				registry.assign<MovesetComponent>(entity, moves);
			}
		} catch(std::exception e) {
			std::cout << "Error loading character" << std::endl;
		}
	}
}

void CombatManager::initialize() {
	// After loading everyone, determine who goes first, and if it is the enemy or player.
	this->determineTurnOrder();
}

void CombatManager::determineTurnOrder() {
	this->combatTurn = 0;
	this->combatants.clear();
	entt::registry& registry = GameDataManager::getInstance().getRegistry();
	auto view = registry.view<BaseComponent, RenderComponent, CombatComponent, MovesetComponent>();
	for (auto entity : view) {
		auto& combatC = view.get<CombatComponent>(entity);
		this->combatants.push_back(combatC);
	}
	std::sort(this->combatants.begin(), this->combatants.end(), [](const CombatComponent& lhs, const CombatComponent& rhs) {
		return lhs.speed > rhs.speed;
	});
}

void CombatManager::processPlayerAction(Action& a) {
	if (a.type == TYPE_PASS) {

	} else if (a.type == TYPE_ITEM) {

	} else if (a.type == TYPE_BATTLE) {

	} else {
		// Do nothing? Not yet sure.
	}
}

bool CombatManager::takeTurn() {
	if (this->combatTurn + 1 < this->combatants.size()) {
		this->combatTurn++;
		return true;
	} else {
		// TODO - Confirm this is the right thing to do at this time.
		this->determineTurnOrder();
		return false;
	}
}

int CombatManager::getCombatId() {
	if (this->combatants.size() > 0 && this->combatTurn < this->combatants.size()) {
		return this->combatants[this->combatTurn].combatId;
	} else {
		return -1;
	}
}

bool CombatManager::hasTurnReady() {
	return this->turnReady;
}