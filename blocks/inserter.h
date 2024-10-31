#pragma once

#include "../header/building.h"
#include "conveyor.h"
#include "crafter.h"

class inserter : public building {
protected:
	float speed;//speed to take out an item from the source and put it in the target
	float timer;

	sf::Vector2f mSourceOffset;
	sf::Vector2f mTargetOffset;
	
	uint16_t transferSize;
public:
	inserter(sf::Vector2f, world*, std::string, uint16_t, uint16_t, float);

	virtual void setRotation(uint16_t);
	
//	virtual void draw(sf::RenderWindow*) const;
	virtual void update(float, uint16_t);
};
