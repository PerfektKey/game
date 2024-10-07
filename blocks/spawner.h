#pragma once

#include "../header/building.h"

class spawner : public building {
private:
	ItemType Spawn;
public:
	spawner(uint16_t, uint16_t, world*, uint16_t, uint16_t, ItemType);
	~spawner();

	void update();
};
