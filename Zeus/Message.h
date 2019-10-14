#pragma once

#include <SFML/Network.hpp>
#include <string>

#ifndef GAME_MESSAGE_H
#define GAME_MESSAGE_H

/*
	This header file is responsible for outlining basic structs for message relaying.
	Messages are data-holders that contain no methods, much like a component in our ECS.
*/

struct Message {
	Message() {};
	Message(std::string type) : type(type) {};
	std::string type;

	friend sf::Packet& operator <<(sf::Packet& packet, const Message& message) {
		return packet << message.type;
	}

	friend sf::Packet& operator >>(sf::Packet& packet, Message& message) {
		return packet >> message.type;
	}
};

#endif // !GAME_MESSAGE_H