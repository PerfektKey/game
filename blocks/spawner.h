#pragma once

#include <math.h>
#include "../header/building.h"

void openInv(component*);

class spawner : public building {
private:
	ItemType mSpawn;

	float timeToSpawn;
	float elapsedTime;
	
	container* selectUI() const;
	void checkButtons(container*);
public:
	spawner(sf::Vector2f, world*, std::string, uint16_t, uint16_t, ItemType, float);
	~spawner();
	
	virtual container* createUI() const;	
	virtual void updateUI(container*);

	virtual void update(float, uint16_t);
};
