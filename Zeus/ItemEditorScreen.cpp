#include "ItemEditorScreen.h"

ItemEditorScreen::ItemEditorScreen() {
	Screen();
	it = 0;
	BGTexture.loadFromFile("Resources/images/questjournal/book/book.png");
	BGSprite.setTexture(BGTexture);
	BGSprite.setScale((float)(Game::WIDTH / BGTexture.getSize().x), (float)(Game::HEIGHT / BGTexture.getSize().y));
	defaultIcon.loadFromFile("Resources/images/questjournal/icons/9.png");
	activeIcon.setTexture(defaultIcon);
	activeIcon.setScale((float)(ICON_SIZE / defaultIcon.getSize().x), (float)(ICON_SIZE / defaultIcon.getSize().y));
	/*header.setFont(FontManager::getInstance().oldStandard);
	activeName.setFont(FontManager::getInstance().oldStandard);
	activeType.setFont(FontManager::getInstance().oldStandard);
	activeStat.setFont(FontManager::getInstance().oldStandard);
	activeDescription.setFont(FontManager::getInstance().oldStandard);*/
	newItem.setFont(FontManager::getInstance().oldStandard);
	deleteItem.setFont(FontManager::getInstance().oldStandard);
	header.setCharacterSize(32);
	/*activeName.setCharacterSize(20);
	activeType.setCharacterSize(20);
	activeStat.setCharacterSize(20);
	activeDescription.setCharacterSize(20);*/
	newItem.setCharacterSize(20);
	deleteItem.setCharacterSize(20);
	header.setFillColor(sf::Color::Black);
	/*activeName.setFillColor(sf::Color::Black);
	activeType.setFillColor(sf::Color::Black);
	activeStat.setFillColor(sf::Color::Black);
	activeDescription.setFillColor(sf::Color::Black);*/
	newItem.setFillColor(sf::Color::Black);
	deleteItem.setFillColor(sf::Color::Black);
	header.setString(sf::String("Item List"));
	/*activeName.setText(sf::String("Item name: ___________"));
	activeType.setText(sf::String("Item type: ___________"));
	activeStat.setText(sf::String("Damage: ___________"));
	activeDescription.setText(sf::String("Description: "));*/
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
	activeType.setEditable(false);
	activeStat.setNumeric(true);
	loadIcons();
	loadItems();
}

void ItemEditorScreen::update(float deltaTime) {
	sortItems();
	activeName.update(deltaTime, mousePosition);
	activeType.update(deltaTime, mousePosition);
	activeStat.update(deltaTime, mousePosition);
	activeDescription.update(deltaTime, mousePosition);
	for (ItemOption* i : items) {
		i->update(deltaTime, mousePosition);
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
	sf::Rect<float> typeBounds(
		activeType.getPosition().x,
		activeType.getPosition().y,
		activeType.getSize().x,
		activeType.getSize().y);
	activeName.update(event, mousePosition);
	activeType.update(event, mousePosition);
	activeStat.update(event, mousePosition);
	activeDescription.update(event, mousePosition);
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
		}
		else if (downBounds.contains(mousePosition.x, mousePosition.y)) {
			it = (it + 1) % items.size();
		}
		else if (typeBounds.contains(mousePosition.x, mousePosition.y)) {
			active->item.itemType = (type)(((int)(active->item.itemType) + 1) % 4);
			updateActiveStats();
		}
		else {
			for (ItemOption* i : items) {
				if (i->isSelected) {
					changeActive();
				}
			}
		}
	}
	if (active != nullptr) {
		active->item.name = activeName.getText();
		active->item.stat = std::stof(activeStat.getText().toAnsiString());
		active->item.description = activeDescription.getText();
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
	/*if (event.type == sf::Event::MouseButtonPressed &&
		event.mouseButton.button == sf::Mouse::Button::Left) {
		std::cout << mousePosition.x << " " << mousePosition.y << std::endl;
		update(event);
	}*/
	update(event);
}

void ItemEditorScreen::addItem() {
	ItemOption* newItem = new ItemOption();
	newItem->item.icon = defaultIcon;
	items.push_back(newItem);
}

void ItemEditorScreen::removeItem() {
	if (active == nullptr) {
		return;
	}
	else {
		for (int i = 0; i < items.size(); i++) {
			if (items.at(i) == active) {
				active = nullptr;
				delete items[i];
				items.erase(items.begin() + i);
			}
		}
	}
	changeActive();
}

void ItemEditorScreen::changeActive() {
	for (ItemOption* i : items) {
		if (i->isSelected) {
			active = i;
			updateActiveStats();
			/*activeName.setText(sf::String(i->getName()));
			activeType.setText(sf::String( i->getType()));
			if (active->item.itemType == type::Weapon) {
				activeStat.setText(sf::String(std::to_string(active->item.stat)));
			}
			else if (active->item.itemType == type::Equippable) {
				activeStat.setText(sf::String(std::to_string(active->item.stat)));
			}
			else if (active->item.itemType == type::Consumable) {
				activeStat.setText(sf::String(std::to_string(active->item.stat)));
			}
			else {
				activeStat.setText(sf::String(""));
			}
			activeDescription.setText(sf::String(i->getDescription()));
			activeIcon.setTexture(i->item.icon);*/
			return;
		}
	}
	activeName.setText(sf::String("__________"));
	activeType.setText(sf::String("__________"));
	activeStat.setText(sf::String("__________"));
	activeDescription.setText(sf::String("__________"));
	activeIcon.setTexture(defaultIcon);
}

void ItemEditorScreen::loadIcons() {
	for (const auto& entry : std::filesystem::directory_iterator("Resources/images/questjournal/icons")) {
		sf::Texture texture;
		texture.loadFromFile(entry.path().string());
		icons.push_back(texture);
	}
}

void ItemEditorScreen::loadItems() {

}

void ItemEditorScreen::sortItems() {
	std::vector<ItemOption*> tempItems;
	for (ItemOption* i : items) {
		if (i->item.itemType == type::Weapon) {
			tempItems.push_back(i);
		}
	}
	for (ItemOption* i : items) {
		if (i->item.itemType == type::Equippable) {
			tempItems.push_back(i);
		}
	}
	for (ItemOption* i : items) {
		if (i->item.itemType == type::Consumable) {
			tempItems.push_back(i);
		}
	}
	for (ItemOption* i : items) {
		if (i->item.itemType == type::Other) {
			tempItems.push_back(i);
		}
	}
	items.clear();
	for (ItemOption* i : tempItems) {
		items.push_back(i);
	}
}

void ItemEditorScreen::updateActiveStats() {
	activeName.setText(sf::String(active->item.name));
	if (active->item.itemType == type::Weapon) {
		activeType.setText(sf::String("Weapon"));
		activeStat.setDefault(sf::String("Damage:"));
		activeStat.setText(sf::String(std::to_string(active->item.stat)));
	}
	else if (active->item.itemType == type::Equippable) {
		activeType.setText(sf::String("Equippable"));
		activeStat.setDefault(sf::String("Armor:"));
		activeStat.setText(sf::String(std::to_string(active->item.stat)));
	}
	else if (active->item.itemType == type::Consumable) {
		activeType.setText(sf::String("Consumable"));
		activeStat.setDefault(sf::String("Stat:"));
		activeStat.setText(sf::String(std::to_string(active->item.stat)));
	}
	else {
		activeType.setText(sf::String("Other"));
		activeStat.setDefault(sf::String("Other"));
		activeStat.setText(sf::String(std::to_string(active->item.stat)));
	}
	activeDescription.setText(sf::String(active->item.description));
	activeIcon.setTexture(active->item.icon);
}

void ItemEditorScreen::drawActive(sf::RenderWindow& window) {
	for (ItemOption* i : items) {
		i->setPosition(0, 0);
	}
	int current = 0;
	int currentIt = it;
	if (items.size() <= 7) {
		for (ItemOption* i : items) {
			i->setPosition(715.0f, 225.0f + current * 35.0f);
			window.draw(*i);
			current++;
		}
		it = 0;
	}
	else {
		while (current < 7) {
			items.at(currentIt)->setPosition(715.0f, 225.0f + current * 35.0f);
			window.draw(*items.at(currentIt));
			current++;
			currentIt = (currentIt + 1) % items.size();
		}
	}
}