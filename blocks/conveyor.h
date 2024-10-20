#pragma once

#include "../header/building.h"

class conveyor : public building {
private:
	float mSpeed;
	float mTimer;


	inventory view;

	uint16_t mSlotAmmount;

	void shiftInv();
public:
	conveyor(sf::Vector2f, world*, uint16_t, uint16_t, float);

	slot getOut();

	virtual void draw(sf::RenderWindow*) const;
	virtual void update(float);
};
