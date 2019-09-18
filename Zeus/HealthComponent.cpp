#include "HealthComponent.h"

HealthComponent::HealthComponent(int max, int current) {
	this->maxHitPoints = max;
	this->hitPoints = current;
}

int HealthComponent::getId() {
	return 1;
}