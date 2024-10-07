#pragma once

#include <stdint.h>
#include <vector>
#include "item.h"
#include <iostream>


struct slot {
	ItemType type;
	uint16_t ammount;
	slot();
};

class inventory
{
private:
	uint16_t slotAmmount;
	uint16_t slotSize;
	
	std::vector<slot> slots;
public:
	inventory(uint16_t,uint16_t);
	inventory();

	void addItem(ItemType, uint16_t);

	bool hasItem(ItemType) const;
	void print() const;
};
