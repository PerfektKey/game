#pragma once

#include "../header/building.h"

class conveyor : public building {
private:
	float mSpeed;
	float mTimer;
	
	sf::Vector2f mSourceOffset;
	sf::Vector2f mTargetOffset;

	uint16_t mSlotAmmount;

	void shiftInv();
public:
	conveyor(sf::Vector2f, world*, std::string, uint16_t, uint16_t, uint16_t, float);

	slot getOut();

	virtual void setRotation(uint16_t);

//	virtual void draw(sf::RenderWindow*) const;
	virtual void update(float, uint16_t);
};
