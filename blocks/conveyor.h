#pragma once

#include "../header/building.h"


class conveyor : public building {
private:
	float mSpeed;

public:
	conveyor(sf::Vector2f, world*, uint16_t, uint16_t, float);

	virtual void draw(sf::RenderWindow*) const;
	virtual void update(float);
};
