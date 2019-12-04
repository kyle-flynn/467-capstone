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
	if (this->checkForEnemyTurn()) {
		this->processEnemyAction();
		this->takeTurn();
	} else {
		this->textbox->reset();
	}
}

bool CombatManager::checkForEnemyTurn() {
	entt::registry& registry = GameDataManager::getInstance().getRegistry();
	auto view = registry.view<BaseComponent, CombatComponent>();
	for (auto entity : view) {
		auto& baseC = view.get<BaseComponent>(entity);
		auto& combatC = view.get<CombatComponent>(entity);
		if (this->combatants[combatTurn].combatId == combatC.combatId) {
			if (baseC.entityType == -1) {
				return true;
			}
		}
	}
	return false;
}

void CombatManager::determineTurnOrder() {
	this->combatTurn = 0;
	this->combatants.clear();
	entt::registry& registry = GameDataManager::getInstance().getRegistry();
	auto view = registry.view<BaseComponent, RenderComponent, CombatComponent, HealthComponent, MovesetComponent>();
	for (auto entity : view) {
		auto& combatC = view.get<CombatComponent>(entity);
		auto& healthC = view.get<HealthComponent>(entity);
		if (healthC.hitpoints > 0) {
			this->combatants.push_back(combatC);
		}
	}
	std::sort(this->combatants.begin(), this->combatants.end(), [](const CombatComponent& lhs, const CombatComponent& rhs) {
		return lhs.speed > rhs.speed;
	});
}

void CombatManager::processPlayerAction(Action& a) {
	entt::registry& registry = GameDataManager::getInstance().getRegistry();
	auto& baseC = registry.get<BaseComponent>(a.entity);

	if (a.type == TYPE_PASS) {
		const std::string moveDesc = baseC.name + " used their turn to... pass.";
		this->textbox->appendBattleText(moveDesc, BattleTextMode::SINGLE_ROW_COMBAT);
	} else if (a.type == TYPE_ITEM) {
		const std::string moveDesc = baseC.name + " used " + a.item.name + ".";
		this->textbox->appendBattleText(moveDesc, BattleTextMode::SINGLE_ROW_COMBAT);
		// this->textbox->appendBattleText(moveDmg, BattleTextMode::SINGLE_ROW_COMBAT);
	} else if (a.type == TYPE_BATTLE) {
		const std::string moveDesc = baseC.name + " used " + a.move.name + ".";
		const std::string moveDmg = std::to_string(a.move.damage) + "HP of damage.";
		this->textbox->appendBattleText(moveDesc, BattleTextMode::SINGLE_ROW_COMBAT);
		this->textbox->appendBattleText(moveDmg, BattleTextMode::SINGLE_ROW_COMBAT);

		entt::entity enemy;
		entt::registry& registry = GameDataManager::getInstance().getRegistry();
		auto view = registry.view<BaseComponent, RenderComponent, CombatComponent, HealthComponent, MovesetComponent>();
		std::vector<CombatComponent> targets;
		for (auto entity : view) {
			auto& baseC = view.get<BaseComponent>(entity);
			auto& combatC = view.get<CombatComponent>(entity);
			auto& healthC = view.get<HealthComponent>(entity);
			if (baseC.entityType == -1) {
				if (!this->calculateDamage(a.move, entity)) {
					this->textbox->appendBattleText(baseC.name + " has been defeated!", BattleTextMode::SINGLE_ROW_COMBAT);
					this->battleFinished = true;
				}
				break;
			}
		}
	} else {
		// Do nothing? Not yet sure.
	}
	// this->hasTurnReady = true;
}

void CombatManager::processEnemyAction() {
	bool found = false;
	entt::entity enemy;
	entt::registry& registry = GameDataManager::getInstance().getRegistry();
	auto view = registry.view<BaseComponent, RenderComponent, CombatComponent, HealthComponent, MovesetComponent>();
	std::vector<CombatComponent> targets;
	for (auto entity : view) {
		auto& baseC = view.get<BaseComponent>(entity);
		auto& healthC = view.get<HealthComponent>(entity);
		auto& combatC = view.get<CombatComponent>(entity);
		if (this->combatants[combatTurn].combatId == combatC.combatId) {
			// We found our entity.
			enemy = entity;
			found = true;
		} else {
			if (healthC.hitpoints > 0) {
				targets.push_back(combatC);
			}
		}
	}
	if (found) {
		auto& baseC = view.get<BaseComponent>(enemy);
		auto& combatC = view.get<CombatComponent>(enemy);
		auto& moveC = view.get<MovesetComponent>(enemy);
		std::random_device rand;
		std::mt19937 engine(rand());
		std::uniform_int_distribution<> moveDistribution(0, moveC.moves.size() - 1);
		std::uniform_int_distribution<> entityDistribution(0, targets.size() - 1);
		int move = moveDistribution(engine);
		int player = entityDistribution(engine);
		int count = 0;
		int targetId = 0;
		Move m = moveC.moves[move];
		std::string moveDesc = baseC.name + " used " + m.name;
		std::string moveDmg = std::to_string(m.damage) + " HP of damage ";
		for (auto target : targets) {
			if (count == player) {
				targetId = target.combatId;
			}
			count++;
		}
		bool deadPlayer = false;
		std::string deadDesc;
		for (auto entity : view) {
			auto& targetC = view.get<CombatComponent>(entity);
			auto& targetHealth = view.get<HealthComponent>(entity);
			if (targetC.combatId == targetId) {
				auto& targetName = view.get<BaseComponent>(entity).name;
				moveDmg += "to " + targetName + ".";
				if (!this->calculateDamage(m, entity)) {
					deadDesc = "Player " + targetName + " has fainted!";
					deadPlayer = true;
					if (targets.size() == 1) {
						this->battleFinished = true;
					}
				}
				break;
			}
		}
		this->textbox->appendBattleText(moveDesc, BattleTextMode::SINGLE_ROW_COMBAT);
		this->textbox->appendBattleText(moveDmg, BattleTextMode::SINGLE_ROW_COMBAT);
		if (deadPlayer) {
			this->textbox->appendBattleText(deadDesc, BattleTextMode::SINGLE_ROW_COMBAT);
		}
		// this->hasTurnReady = true;
	}
}

void CombatManager::setBattleTextbox(BattleTextbox* textbox) {
	this->textbox = textbox;
}

bool CombatManager::takeTurn() {
	this->turnReady = false;
	if ((this->combatTurn + 1) < this->combatants.size()) {
		this->combatTurn++;
		return true;
	} else {
		// TODO - Confirm this is the right thing to do at this time.
		this->determineTurnOrder();
		return false;
	}
}

bool CombatManager::calculateDamage(Move m, entt::entity& entity) {
	entt::registry& registry = GameDataManager::getInstance().getRegistry();
	auto& healthC = registry.get<HealthComponent>(entity);
	if ((healthC.hitpoints - m.damage) >= 0) {
		healthC.hitpoints -= m.damage;
		return true;
	} else {
		healthC.hitpoints = 0;
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

bool CombatManager::isBattleFinished() {
	return this->battleFinished;
}