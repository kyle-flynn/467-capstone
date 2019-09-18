#pragma once

#include "IComponent.h"

#ifndef GAME_COMPONENT_HEALTH_H
#define GAME_COMPONENT_HEALTH_H

class HealthComponent : public IComponent {
public:
	HealthComponent(int max, int current);
	int maxHitPoints;
	int hitPoints;
	int getId() override;
};

#endif