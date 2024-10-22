#include "../blocks/inserter.h"
#include "../header/world.h"

inserter::inserter(sf::Vector2f sp, world* w, float sd, uint16_t ts): 
	building(sp, w, 1, ts) {
	this->speed = sd;
	this->timer = 0;
	this->transferSize = ts;

	this->type = "Inserter";
}


void inserter::update(float dt, uint16_t frame) {
	timer += dt;

	if (timer < speed) return;
	timer -= speed;
	
	building* source = WORLD->get(mapPosition - sf::Vector2f(1, 0));
	building* target = WORLD->get(mapPosition + sf::Vector2f(1, 0));
	
	if (source == NULL || target == NULL) return;

	inventory* sourceINV = source->getInventory();	
	
	inventory* targetINV = target->getInventory();
/*
	if (target->getType() != "conveyor") 
		targetINV = target->getInventory();
	else {
		conveyor* c = (conveyor*)target;
		targetINV = c->getAccessInv();
	}
*/
	if (sourceINV == NULL || targetINV == NULL) return;	


	ItemType ItemToTransfer = sourceINV->getLastItem();
	if (ItemToTransfer == ItemType::EMPTY) return;
	uint16_t transfered = sourceINV->remove(ItemToTransfer , transferSize);
	if (target->getType() != "conveyor") 
		targetINV->add(ItemToTransfer , transfered);
	else
		targetINV->add(ItemToTransfer, transfered, 0);
}
