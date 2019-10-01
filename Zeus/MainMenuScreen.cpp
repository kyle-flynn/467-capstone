#include "MainMenuScreen.h"

#include "EntityComponentSystem.h"
#include "Components.h"

MainMenuScreen::MainMenuScreen() : Screen() {
	entt::registry registry;
	auto entity = registry.create();
	registry.assign<ParallaxComponent>(entity, 0.0f, 10.0f);
}

void MainMenuScreen::draw(sf::RenderWindow& window) {

}