#pragma once
#include <string>

enum ItemType {
	EMPTY = 0,
	Copper,
	Iron
};

struct ItemD {
	std::string name;
};

const ItemD ItemData[] = {
	{"empty"},
	{"Copper"}
};
