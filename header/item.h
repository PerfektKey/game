#pragma once
#include <string>

enum ItemType {
	EMPTY = 0,
	Copper,
	Iron
};

struct ItemData {
	std::string name;
};

const ItemData[] = {
	{"empty"},
	{"Copper"}
};
