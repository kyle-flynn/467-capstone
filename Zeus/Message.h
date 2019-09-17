#pragma once

#include <string>
#include <memory>

#ifndef GAME_MESSAGE_H
#define GAME_MESSAGE_H

class Message {
public:
	Message(std::string name, std::shared_ptr<void> data);

	std::string getName();
	std::shared_ptr<void> getData();

private:
	std::string name;
	std::shared_ptr<void> data;
};

#endif // !GAME_MESSAGE_H