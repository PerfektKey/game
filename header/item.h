#pragma once
#include <string>

enum ItemType {
	EMPTY = 0,
	Copper,
	Iron
};

struct ItemD {
	std::string name;
	std::string abbreviation;
};

const ItemD ItemData[] = {
	{"empty", "E"},
	{"Copper", "C"}
};
