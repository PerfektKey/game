#pragma once

#include "../header/building.h"
#include <unordered_map> // will be fast enough

class crafter : public building {
private:
	inventory mOutputInv; // normal inv as input
	std::vector<slot> mInputs ; // basically saves the recepi. says what can be inputed
	std::vector<slot> mOutputs; // same as input. says what will be outputed once crafted

	float mSpeed;
public:
	crafter(sf::Vector2f, world*, float);

	bool canAdd(slot);
	inventory* getOutput();

	virtual void update(float,uint16_t);
};
