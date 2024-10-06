#pragma once

#include <stdint.h>
#include <vector>
#include "items.h"

class inventory
{
private:
	struct slot {
		ItemType type;
		uint16_t ammount;
	};
	uint16_t slotAmmount;
	uint16_t slotSize;
	
	std::vector<slot> slots;
public:
	inventory(uint16_t,uint16_t);

	void addItem(item, uint16_t);

	bool hasItem(item&) const;
	void printInventory() const;
};
