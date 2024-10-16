#pragma once

#include "component.h"
#include <vector>

// Just to group components
class container : public component {
private:
	std::vector<component*> cont;
public:
};
