#include "../header/building.h"


class inserter : public building {
protected:
	float speed;//speed to take out an item from the source and put it in the target
	float timer;

public:
	inserter(sf::Vector2f, world*, float, uint16_t);

	virtual void update(float);
};
