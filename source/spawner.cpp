#include "../blocks/spawner.h"


spawner::spawner(uint16_t x, uint16_t y, world* w, uint16_t sa, uint16_t ss, ItemType sp) : 
	building(x,y,w,sa,ss)
{

	this->Spawn = sp;
}
spawner::~spawner() {}//I dont know if i should delete anythin here?

void spawner::update() {

	this->inv.add(Spawn, 1);	
}
