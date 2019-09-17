#include "TestMessage.h"

TestMessage::TestMessage(std::string data) : Message(std::string("TEST_MSG"), std::make_shared<std::string>(data)) {

}