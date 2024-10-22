#pragma once

#include <math.h>
#include "../header/building.h"

class spawner : public building {
private:
	ItemType Spawn;

	float timeToSpawn;
	float elapsedTime;
public:
	spawner(sf::Vector2f, sf::Vector2f, world*, uint16_t, uint16_t, ItemType);
	spawner(sf::Vector2f, world*, uint16_t, uint16_t, ItemType);
	~spawner();

	virtual void update(float, uint16_t);
};
