#pragma once
#include <string>

enum ItemType {
	EMPTY = 0,
	CopperOre,
	CopperPlate
};

struct ItemD {
	std::string name;
	std::string abbreviation;
};

const ItemD ItemData[] = {
	{"empty", "E"},
	{"Copper Ore", "Co"},
	{"Copper Plate", "Cp"}
};
