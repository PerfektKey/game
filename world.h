#pragma once
#include<vector>
#include<stdint.h>
#include "building.h"


class world {
private:
	std::vector<std::vector<building*>> map;
	
	uint16_t width;
	uint16_t height;
public:
	world(uint16_t,uint16_t);


	building* getBuilding(uint16_t, uint16_t) const;
	building* setBuilding(uint16_t,uint16_t, building*);	

	uint16_t getWidth () const;
	uint16_t getHeight() const;
	
};
