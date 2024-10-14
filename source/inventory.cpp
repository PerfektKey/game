#include "../header/inventory.h"

slot::slot()
{
	this->type = ItemType::EMPTY;
	this->ammount = 0;
}

inventory::inventory(uint16_t sa, uint16_t ss) 
{
	slots = std::vector<slot>(sa, slot());	
	
	this->slotSize = ss;	
	this->slotAmmount = sa;
}
inventory::inventory() {

} 

uint16_t inventory::add(ItemType t, uint16_t amm) {
	
	// how much left to add
	uint16_t toAdd = amm;

	// loop through vector
	for (uint16_t i = 0; i < slotAmmount; i++) {
		//check if the item at the slot is empty or the item to add
		if (slots[i].type == ItemType::EMPTY || slots[i].type == t) {
			// check how much space is left in the slot
			uint16_t SpaceLeft = this->slotSize - slots[i].ammount;
			// if toAdd > SpaceLeft: add SpaceLeft else: add toAdd
			uint16_t adding = std::min(toAdd, SpaceLeft);
			//update how much to add
			toAdd = toAdd - adding;

			// if the type is empty, set the type:
			if (slots[i].type == ItemType::EMPTY) slots[i].type = t;	
			// add the items
			slots[i].ammount += adding;
		}

		// if all items have been added, break
		if (toAdd == 0) break;
	}

	return toAdd;
}



ItemType inventory::getLastItem() const {
	for (int i = slotAmmount-1; i >= 0; i--) {
		if (slots[i].type == ItemType::EMPTY) continue;
		return slots[i].type;
	}	
	return ItemType::EMPTY;
}

uint16_t inventory::remove(ItemType t, uint16_t amm) {
	if (t == ItemType::EMPTY) return 0;
	
	uint16_t toRemove = amm;
	
	// check all slots for the item (looping from last to first)
	for (int i = slotAmmount; i >= 0; i--) {
		if (slots[i].type != t) continue; // if the slot doesnt have the item I am searching for, continue
		// it is the item
		// three options:
		// 	1. slot ammount == amm : set slot to empty
		// 	2. Slot ammount > amm  : remove amm from slot
		// 	3. Slot ammount < amm : set slot to empty and decrease toRemove
		if (slots[i].ammount >= toRemove) {
			slots[i].ammount -= toRemove;
			if (slots[i].ammount == 0) slots[i].type = ItemType::EMPTY;
			toRemove = 0;
		} else if (slots[i].ammount < toRemove) {
			toRemove -= slots[i].ammount;
			slots[i].ammount = 0;
			slots[i].type = ItemType::EMPTY;
		}
		if (toRemove == 0) break;
	}

	return (amm - toRemove); // returns how much has been added
}

slot inventory::getItemAt(uint16_t ind) {
	if (ind >= slotAmmount) return slot();
	return slots[ind];

}

uint16_t inventory::getSlotAmmount() const {return slotAmmount;}
uint16_t inventory::getSlotSize() const {return slotSize;}


void inventory::print() const {
	// loop through slot vector, print name with ammount
	for (uint16_t i = 0; i < slotAmmount; i++) {
		std::cout  << ItemData[slots[i].type].name << " x " << slots[i].ammount << "\n";
	}
}
