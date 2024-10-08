#pragma once

#include <SFML/Graphics.hpp>

class building;

enum bType {
	NOTHING,
	TILE,
	SPAWNER
};

class buildingUI {
private:

	bType choosenB;
public:


	building* factorie(bType);

	void update(float);

	void choose();
};
