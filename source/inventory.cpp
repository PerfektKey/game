#include "../header/inventory.h"

slot::slot() {
	this->type = ItemType::EMPTY;
	this->ammount = 0;
}
slot::slot(ItemType t, uint16_t amm) :
	type(t), ammount(amm){
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

uint16_t inventory::add(ItemType t, uint16_t toAdd, uint16_t index) {
	if (index >= slotAmmount) return toAdd;
	if (slots[index].type != t && slots[index].type != ItemType::EMPTY) return toAdd;

	// calculate space left in slot
	uint16_t spaceLeft = slotSize - slots[index].ammount;
	// calculate how much can be added
	uint16_t addable = std::min(toAdd, spaceLeft);
	
	slots[index].type = t;
	slots[index].ammount += addable;


	return toAdd - addable; // returns how much couldnt be added

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

slot inventory::remove(uint16_t index,  uint16_t toRemove) {
	if (index >= slotAmmount) return slot();
	
	uint16_t removable = std::min(slots[index].ammount, toRemove);
	slots[index].ammount -= removable;
	ItemType t = slots[index].type;

	if (slots[index].ammount == 0 ) slots[index].type = ItemType::EMPTY;

	return slot(t, removable);
}

slot inventory::getSlot(uint16_t ind) const {
	if (ind >= slotAmmount) return slot();
	return slots[ind];

}
bool inventory::setSlot(uint16_t i, slot s) {
	if (i >= slotAmmount) return false;
	slots[i] = s;
	return true;
}

uint16_t inventory::getSlotAmmount() const {return slotAmmount;}
uint16_t inventory::getSlotSize() const {return slotSize;}


void inventory::print() const {
	// loop through slot vector, print name with ammount
	for (uint16_t i = 0; i < slotAmmount; i++) {
		std::cout  << ItemData[slots[i].type].name << " x " << slots[i].ammount << "\n";
	}
}
