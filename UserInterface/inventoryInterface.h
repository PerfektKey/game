#pragma once

#include <iostream>

#include "../header/building.h"
#include "container.h"
#include "component.h"
#include "label.h"
#include "button.h"
#include <cmath>

void hideInterface(component*);

class inventoryInterface {
private:
	sf::Vector2f mGlobalPosition;
	building* mRef; // the building that is 
	container* mCont; // the container
	void createUI();
public:
	inventoryInterface();
	      
	void setRef(building*);
	
	void update(); // updates labels

	void draw(sf::RenderWindow*);
	void action(sf::Event, sf::Vector2f);
	void show(bool);
};
