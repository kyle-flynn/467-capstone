#pragma once

#include <SFML/Graphics.hpp>

#include "ItemOption.h"
#include "Character.h"
#include "Player.h"

class InventoryMenu : public sf::Drawable, public sf::Transformable{

public:

	bool visible;

	InventoryMenu();
	void setVisible(bool vis);
	void update(float deltaTime, sf::Vector2i mousePosition);
	void update(sf::Event event, sf::Vector2i mousePosition);
	void loadItems();
	void equipItem(Character::equipSlot slot, Item item);
	void unequipItem(Character::equipSlot slot);
	void setCharacter(Character* character);

private:

	int listIt;
	Character* character;
	Item activeItem;
	const int TEXT_SIZE = 32;
	std::vector<ItemOption> items;
	sf::Texture BGTexture;
	sf::Sprite BGSprite;

	void sortItems(sf::String filter, Item::type typeFilter=Item::type::NULL_TYPE);
	virtual void draw(sf::RenderTarget&, sf::RenderStates states) const;

};

