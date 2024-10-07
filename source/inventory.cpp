#include "../header/inventory.h"

slot::slot()
{
	this->type = ItemType::EMPTY;
	this->ammount = 0;
}

inventory::inventory(uint16_t sa, uint16_t slottSize) 
{
	slots = std::vector<slot>(sa, slot());	
	
	this->slotAmmount = sa;
}
inventory::inventory() {

} 

void inventory::print() const
{
	// loop through slot vector, print name with ammount
	for (uint16_t i = 0; i < slotAmmount; i++) {
		std::cout  << ItemData[slots[i].type].name << " x " << slots[i].ammount << "\n";
	}
}
