#pragma once

#ifndef GAME_INTERFACE_COMPONENT_H
#define GAME_INTERFACE_COMPONENT_H

class IComponent {
public:
	IComponent();
	virtual int getId() = 0;
};

#endif