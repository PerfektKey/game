#pragma once

#include <cmath>

#include "UI"
#include "component.h"
#include "button.h"

// a factory that creates a UI element
//

// inventory 
UI* makeInventory(uint16_t slots) {
	uint16_t RowSize = 8;
	uint16_t collums = floor(slots/RowSize);

	UI* u = new UI();

	
}
