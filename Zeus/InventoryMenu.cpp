#include "InventoryMenu.h"

InventoryMenu::InventoryMenu() {
	visible = false;
	listIt = 0;
	BGTexture.loadFromFile("Resources/images/questjournal/book/book.png");
	BGSprite.setTexture(BGTexture);
	//TODO SET BACKGROUND SCALE TO WHATEVER
}

void InventoryMenu::setVisible(bool vis) {
	visible = vis;
	if (vis) {
		loadItems();
	}
}

void InventoryMenu::update(float deltaTime, sf::Vector2i mousePosition) {
}

void InventoryMenu::update(sf::Event event, sf::Vector2i mousePosition) {
}

void InventoryMenu::loadItems() {
	items.clear();
	for (Item i : character->equipment) {
		items.push_back(ItemOption(i));
	}
}

void InventoryMenu::equipItem(Character::equipSlot slot, Item item) {
	switch (slot) {
	case Character::equipSlot::Head:
		character->head = item;
		break;
	case Character::equipSlot::Chest:
		character->chest = item;
		break;
	case Character::equipSlot::Legs:
		character->legs = item;
		break;
	case Character::equipSlot::MainHand:
		character->mainHand = item;
		break;
	case Character::equipSlot::OffHand:
		character->offHand = item;
		break;
	case Character::equipSlot::Back:
		character->back = item;
		break;
	}
}

void InventoryMenu::unequipItem(Character::equipSlot slot) {
	switch (slot) {
	case Character::equipSlot::Head:
		character->head = GameDataManager::getInstance().nullItem;
		break;
	case Character::equipSlot::Chest:
		character->chest = GameDataManager::getInstance().nullItem;
		break;
	case Character::equipSlot::Legs:
		character->legs = GameDataManager::getInstance().nullItem;
		break;
	case Character::equipSlot::MainHand:
		character->mainHand = GameDataManager::getInstance().nullItem;
		break;
	case Character::equipSlot::OffHand:
		character->offHand = GameDataManager::getInstance().nullItem;
		break;
	case Character::equipSlot::Back:
		character->back = GameDataManager::getInstance().nullItem;
		break;
	}
}

void InventoryMenu::setCharacter(Character* character) {
	this->character = character;
}

void InventoryMenu::sortItems(sf::String filter, Item::type typeFilter) {
	std::vector<ItemOption> tempItems;
	if (filter.isEmpty() && typeFilter == Item::type::NULL_TYPE) {
		for (ItemOption i : items) {
			if (i.item.itemType == Item::type::Weapon) {
				tempItems.push_back(i);
			}
		}
		for (ItemOption i : items) {
			if (i.item.itemType == Item::type::Equippable) {
				tempItems.push_back(i);
			}
		}
		for (ItemOption i : items) {
			if (i.item.itemType == Item::type::Consumable) {
				tempItems.push_back(i);
			}
		}
		for (ItemOption i : items) {
			if (i.item.itemType == Item::type::Other) {
				tempItems.push_back(i);
			}
		}
		items.clear();
		for (ItemOption i : tempItems) {
			items.push_back(i);
		}
	}
	else if (filter.isEmpty()) {
		for (ItemOption i : items) {
			if (i.item.itemType == typeFilter) {
				tempItems.push_back(i);
			}
		}
		items.clear();
		for (ItemOption i : tempItems) {
			items.push_back(i);
		}
	}
	else if (typeFilter == Item::type::NULL_TYPE) {
		for (ItemOption i : items) {
			if (i.item.name.find(filter)) {
				tempItems.push_back(i);
			}
		}
		items.clear();
		for (ItemOption i : tempItems) {
			items.push_back(i);
		}
	}
	else {
		for (ItemOption i : items) {
			if (i.item.name.find(filter) && i.item.itemType == typeFilter) {
				tempItems.push_back(i);
			}
		}
		items.clear();
		for (ItemOption i : tempItems) {
			items.push_back(i);
		}
	}
}

void InventoryMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= getTransform();
	states.texture = NULL;
	target.draw(BGSprite);
	//TODO Draw inventory list
	//TODO Draw equipped items
}