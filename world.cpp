#include "world.h"



world::world(uint16_t w, uint16_t h) 
{
	this->width  = w;	
	this->height = h;
	this->map = std::vector<std::vector<building*>>(w, std::vector<building*>(h, NULL));
}

building* world::getBuilding(uint16_t wx, uint16_t hy) const {return map.at(wx).at(hy);}
building* world::setBuilding(uint16_t wx, uint16_t hy, building* b)
{
	if (wx > width || hy > height) return b;
	map[wx][hy] = b;
	return NULL;
}

uint16_t world::getWidth() const {return this->width;}
uint16_t world::getHeight() const {return this->height;}

