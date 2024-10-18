#pragma once

#include "../header/building.h"
#include "container.h"
#include "component.h"
#include "label.h"
#include "button.h"

void hideInterface(component*);

class inventoryInterface {
private:
	sf::Vector2f mGlobalPosition;
	building* mRef; // the building that is 
	container* mCont; // the container
	void update();
public:
	inventoryInterface();
	      
	void setRef(building*);

	void draw(sf::RenderWindow*);
	void action(sf::Event, sf::Vector2f);
	void show(bool);
};
