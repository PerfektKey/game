#pragma once

#include <stdint.h>
#include <vector>
#include "item.h"
#include <iostream>


struct slot {
	ItemType type;
	uint16_t ammount;
	slot();
	slot(ItemType, uint16_t);
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

	uint16_t add(ItemType, uint16_t);
	uint16_t add(ItemType, uint16_t, uint16_t);
	uint16_t remove(ItemType, uint16_t);
	slot remove(uint16_t,  uint16_t);

	const slot* get(ItemType);
	slot getSlot(uint16_t) const;
	bool setSlot(uint16_t, slot);
	ItemType getLastItem() const;

	bool hasItem(ItemType) const;
	void print() const;

	uint16_t getSlotAmmount() const;
	uint16_t getSlotSize() const;
};
