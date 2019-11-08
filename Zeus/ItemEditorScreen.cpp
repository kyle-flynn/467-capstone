#include "ItemEditorScreen.h"
#include <iostream>

ItemEditorScreen::ItemEditorScreen() {
	Screen();
	it = 0;
	BGTexture.loadFromFile("Resources/images/questjournal/book/book.png");
	BGSprite.setTexture(BGTexture);
	BGSprite.setScale((float)(Game::WIDTH / BGTexture.getSize().x), (float)(Game::HEIGHT / BGTexture.getSize().y));
	defaultIcon.loadFromFile("Resources/images/questjournal/icons/9.png");
	activeIcon.setTexture(defaultIcon);
	activeIcon.setScale((float)(ICON_SIZE / defaultIcon.getSize().x), (float)(ICON_SIZE / defaultIcon.getSize().y));
	header.setFont(FontManager::getInstance().oldStandard);
	activeName.setFont(FontManager::getInstance().oldStandard);
	activeType.setFont(FontManager::getInstance().oldStandard);
	activeStat.setFont(FontManager::getInstance().oldStandard);
	activeDescription.setFont(FontManager::getInstance().oldStandard);
	newItem.setFont(FontManager::getInstance().oldStandard);
	deleteItem.setFont(FontManager::getInstance().oldStandard);
	header.setCharacterSize(32);
	activeName.setCharacterSize(20);
	activeType.setCharacterSize(20);
	newItem.setCharacterSize(20);
	deleteItem.setCharacterSize(20);
	activeStat.setCharacterSize(20);
	activeDescription.setCharacterSize(20);
	header.setFillColor(sf::Color::Black);
	activeName.setFillColor(sf::Color::Black);
	activeType.setFillColor(sf::Color::Black);
	newItem.setFillColor(sf::Color::Black);
	deleteItem.setFillColor(sf::Color::Black);
	activeStat.setFillColor(sf::Color::Black);
	activeDescription.setFillColor(sf::Color::Black);
	header.setString(sf::String("Item List"));
	activeName.setString(sf::String("Item name: ___________"));
	activeType.setString(sf::String("Item type: ___________"));
	activeStat.setString(sf::String("Damage: ___________"));
	activeDescription.setString(sf::String("Description: "));
	newItem.setString(sf::String("New Item"));
	deleteItem.setString(sf::String("Delete Item"));
	header.setPosition(850.0f, 150.0f);
	activeName.setPosition(150.0f, 150.0f);
	activeType.setPosition(150.0f, 225.0f);
	activeStat.setPosition(150.0f, 300.0f);
	activeDescription.setPosition(150.0f, 375.0f);
	activeIcon.setPosition(415.0f, 150.0f);
	newItem.setPosition(800.0f, 550.0f);
	deleteItem.setPosition(newItem.getGlobalBounds().width + 850.0f, 550.0f);
	listUp.setRadius(10);
	listUp.setPointCount(3);
	listUp.setFillColor(sf::Color::Black);
	listUp.setPosition(1100.0f, 200.0f);
	listDown.setRadius(10);
	listDown.setPointCount(3);
	listDown.setRotation(180);
	listDown.setFillColor(sf::Color::Black);
	listDown.setPosition(1120.0f, 500.0f);
	newBounds = sf::Rect<float>(
		800.0f, 550.0f,
		newItem.getGlobalBounds().width,
		newItem.getGlobalBounds().height + 20.0f);
	deleteBounds = sf::Rect<float>(
		deleteItem.getPosition().x, 550.0f,
		deleteItem.getGlobalBounds().width,
		deleteItem.getGlobalBounds().height + 20.0f);
	upBounds = sf::Rect<float>(
		listUp.getPosition().x,
		listUp.getPosition().y, 
		listUp.getGlobalBounds().width, 
		listUp.getGlobalBounds().height);
	downBounds = sf::Rect<float>(
		listDown.getPosition().x - listDown.getRadius(),
		listDown.getPosition().y - listDown.getRadius(),
		listDown.getPosition().x,
		listDown.getPosition().y);
	loadIcons();
	loadItems();
}

void ItemEditorScreen::update(float deltaTime) {
	for (ItemOption& i : items) {
		i.update(deltaTime, mousePosition);
	}
	if (newBounds.contains(mousePosition.x, mousePosition.y)) {
		newItem.setFillColor(sf::Color::Blue);
	}
	else if (deleteBounds.contains(mousePosition.x, mousePosition.y)) {
		deleteItem.setFillColor(sf::Color::Blue);
	}
	else if (upBounds.contains(mousePosition.x, mousePosition.y)) {
		listUp.setFillColor(sf::Color::Blue);
	}
	else if (downBounds.contains(mousePosition.x, mousePosition.y)) {
		listDown.setFillColor(sf::Color::Blue);
	}
	else {
		newItem.setFillColor(sf::Color::Black);
		deleteItem.setFillColor(sf::Color::Black);
		listUp.setFillColor(sf::Color::Black);
		listDown.setFillColor(sf::Color::Black);
	}
}

void ItemEditorScreen::update(sf::Event event) {
	if (event.type == sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Button::Left) {
		if (newBounds.contains(mousePosition.x, mousePosition.y)) {
			addItem();
		}
		else if (deleteBounds.contains(mousePosition.x, mousePosition.y)) {
			removeItem();
		}
		else if (upBounds.contains(mousePosition.x, mousePosition.y)) {
			if (it == 0) {
				it = items.size() - 1;
			}
			else {
				it--;
			}
			std::cout << "List up" << std::endl;
		}
		else if (downBounds.contains(mousePosition.x, mousePosition.y)) {
			std::cout << "List down" << std::endl;
			it = (it + 1) % items.size();
		}
		else {
			for (ItemOption i : items) {
				if (i.isSelected) {
					changeActive();
				}
			}
		}
	}
}

void ItemEditorScreen::draw(sf::RenderWindow& window) {
	mousePosition = sf::Mouse::getPosition(window);
	window.draw(BGSprite);
	window.draw(header);
	window.draw(activeName);
	window.draw(activeType);
	window.draw(activeStat);
	window.draw(activeIcon);
	window.draw(activeDescription);
	window.draw(newItem);
	window.draw(deleteItem);
	window.draw(listUp);
	window.draw(listDown);
	drawActive(window);
	/*for (int i = 0; i < activeItems.size(); i++) {
		activeItems.at(i)->setPosition(715.0f, 225.0f + i * 35.0f);
		window.draw(activeItems.at(i));
	}*/
}

void ItemEditorScreen::handleEvent(sf::Event event) {
	if (event.type == sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Button::Left) {
		std::cout << mousePosition.x << " " << mousePosition.y << std::endl;
		update(event);
	}
}

void ItemEditorScreen::addItem() {
	ItemOption newItem = ItemOption();
	newItem.item.icon = defaultIcon;
	items.push_back(newItem);
	std::cout << items.size() << std::endl;
}

void ItemEditorScreen::removeItem() {
	if (active == nullptr) {
		return;
	}
	else {
		/*for (int i = 0; i < items.size(); i++) {
			if (items.at(i).item == active->item) {
				active = nullptr;
				items.erase(items.begin());
			}
		}*/
		/*auto position = std::find(items.begin(), items.end(), *active);
		items.erase(position);*/
	}
}

void ItemEditorScreen::changeActive() {
	for (ItemOption& i : items) {
		if (i.isSelected) {
			active = &i;
			activeName.setString(sf::String("Item Name: " + i.getName()));
			activeType.setString(sf::String("Item Type: " + i.getType()));
			if (active->item.itemType == Item::Weapon) {
				activeStat.setString(sf::String("Damage: " + std::to_string(active->item.stat)));
			}
			else if (active->item.itemType == Item::Equippable) {
				activeStat.setString(sf::String("Armor: " + std::to_string(active->item.stat)));
			}
			else if (active->item.itemType == Item::Consumable) {
				activeStat.setString(sf::String("Amount: " + std::to_string(active->item.stat)));
			}
			else {
				activeStat.setString(sf::String(""));
			}
			activeIcon.setTexture(i.item.icon);
			break;
		}
	}
}

void ItemEditorScreen::loadIcons() {
	for (const auto& entry : std::filesystem::directory_iterator("Resources/images/questjournal/icons")) {
		sf::Texture texture;
		std::cout << entry.path() << std::endl;
		texture.loadFromFile(entry.path().string());
		icons.push_back(texture);
	}
}

void ItemEditorScreen::loadItems() {

}

void ItemEditorScreen::sortItems() {
	std::vector<ItemOption> tempItems;
	for (ItemOption i : items) {
		if (i.item.itemType == Item::Weapon) {
			tempItems.push_back(i);
		}
	}
	for (ItemOption i : items) {
		if (i.item.itemType == Item::Equippable) {
			tempItems.push_back(i);
		}
	}
	for (ItemOption i : items) {
		if (i.item.itemType == Item::Consumable) {
			tempItems.push_back(i);
		}
	}
	for (ItemOption i : items) {
		if (i.item.itemType == Item::Other) {
			tempItems.push_back(i);
		}
	}
	items.clear();
	for (ItemOption i : tempItems) {
		items.push_back(i);
	}
}

void ItemEditorScreen::drawActive(sf::RenderWindow& window) {
	for (ItemOption& i : items) {
		i.setPosition(0, 0);
	}
	int current = 0;
	int currentIt = it;
	if (items.size() <= 7) {
		for (ItemOption& i : items) {
			i.setPosition(715.0f, 225.0f + current * 35.0f);
			window.draw(i);
			current++;
		}
	}
	else {
		while (current < 7) {
			items.at(currentIt).setPosition(715.0f, 225.0f + current * 35.0f);
			window.draw(items.at(currentIt));
			current++;
			currentIt = (currentIt + 1) % items.size();
		}
	}
}