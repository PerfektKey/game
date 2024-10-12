#include "../header/building.h"


class inserter : public building {
protected:
	float speed;//speed to take out an item from the source and put it in the target
	
	building* source; // wehere to take the item from
	building* target; // where to put the item
public:
	inserter(sf::Vector2f, sf::Vector2f, world*, float);

	virtual void update(float);
};
