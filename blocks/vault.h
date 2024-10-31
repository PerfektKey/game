#pragma once

#include "../header/building.h"

// basically normal building, just a renamed version
class vault : public building {
public:
	// screen position, world pointer, slot ammount, slot size
	vault(sf::Vector2f, world*, std::string, uint16_t, uint16_t);
};
