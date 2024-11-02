#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <random>
#include "world.h"

namespace resourceManager {
	
	enum Tiles {
		stone,
		grass,
		sand,
		water
	};
	enum Ores {
		copper
	};
	
	inline sf::Texture TextStone;
	inline sf::Texture TextGrass;
	inline sf::Texture TextSand;
	inline sf::Texture TextWater;
	inline sf::Texture TextCopperOre;

	void loadTextures();
};

namespace worldGeneration {

	void fill(world*);
	
	inline std::random_device rd;
	inline std::default_random_engine gen(rd());
	inline std::uniform_int_distribution<uint16_t> dist(0, 99);

	struct probability {
		resourceManager::Tiles t;
		uint16_t prob;
	};
	void waveFunktionCollapse(world*);
	uint16_t collapse(std::vector<probability>*);
//	void removeProbability(std::vector<resourc>*, resourceManager::Tiles);
	void changeProbOf(std::vector<probability>*, resourceManager::Tiles, int16_t);

	void setTile(world*, resourceManager::Tiles, uint16_t, uint16_t);
};
