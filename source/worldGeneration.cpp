
#include "../header/worldGeneration.h"
#include <iostream>

void resourceManager::loadTextures() {
	TextStone.loadFromFile("assets/env/stone01.png");
	TextGrass.loadFromFile("assets/env/grass.png");
	TextSand.loadFromFile("assets/env/sand.png");
	TextWater.loadFromFile("assets/env/water.png");
	TextCopperOre.loadFromFile("assets/env/CopperOre.png");


}

void worldGeneration::fill(world* w) {
	sf::Texture* t = new sf::Texture();
	if (!t->loadFromFile("assets/env/stone01.png")) {
	}
	
	uint16_t wi = w->getWidth();
	uint16_t h = w->getHeight();
	for (uint16_t x = 0; x < wi; x++)
	for (uint16_t y = 0; y < h; y++) {
		w->setTile(t, x,y);
	}
}


void worldGeneration::waveFunktionCollapse(world* WORLD) {
	resourceManager::loadTextures();

	uint16_t w = WORLD->getWidth();
	uint16_t h = WORLD->getHeight();

	uint32_t tilesToPlace = w * h;

	// holds all possible locations in the grid with all possible tiles
	std::vector<std::vector<std::vector<probability>>> toPlace;
	// init with all possible values
	for (uint16_t x = 0;x < w; ++x) {
		toPlace.push_back({});
		for (uint16_t y = 0;y < h; ++y) {
			toPlace[x].push_back({});
			
			toPlace[x][y].push_back({resourceManager::Tiles::stone, 25});
			toPlace[x][y].push_back({resourceManager::Tiles::grass, 25});
			toPlace[x][y].push_back({resourceManager::Tiles::sand , 25});
			toPlace[x][y].push_back({resourceManager::Tiles::water, 25});
		}
	}
	//
	while (tilesToPlace > 0) {
		uint16_t indX = 0; // the indexes to toPlace
		uint16_t indY = 0;
		uint16_t lowestProb = 9999999; // the tile with the lowest probability
		uint16_t highestTileProb = 0;

		// get tile with lowest probability
		// it is the one with the lowest possible tiles and it has a tile with the highest probability
		for (uint16_t x = 0;x < w; ++x) 
		for (uint16_t y = 0;y < h; ++y) {
			if (toPlace[x][y].size() == 0) continue; // that tile is finished
			if (toPlace[x][y].size() > lowestProb) continue; // to low
			if (toPlace[x][y].size() == lowestProb) {
				// see if a tile has a higher priority than the current 
				for (auto& p : toPlace[x][y]) {
					if (p.prob <= highestTileProb) continue;
					// it has a higher tile prob
					highestTileProb = p.prob;
					lowestProb = toPlace[x][y].size();
					indX = x;
					indY = y;
				}
			} else {
				lowestProb = toPlace[x][y].size();
				indX = x;
				indY = y;
			}
		}
//		std::cout << "lowest probability in loop " << (w*h)-tilesToPlace << " is " << lowestProb << "\n";
		// choose a tile of that tile at random
		uint16_t collapsed = collapse(&toPlace[indX][indY]);
		resourceManager::Tiles t = toPlace[indX][indY][collapsed].t;
		setTile(WORLD, t, indX, indY);
		// set tile probability to zero
		toPlace[indX][indY] = {};

		//
		// take care of the probabilities around the tile
		// 	1. should increase probability to be the same tile
		// 		-> makes it so that others also decrease (always adds up to 100%)
		// 	3. decrease some, increase others 
		// edge cases if x = 0 or x = width-1 and y = 0 or y = height-1
		// look x + 1, x -1, y + 1, y-1
		//
		
		// tells how much to increase the same tile and how much to decrease all other tiles<
		// if >= 5 different possibilities, remove 2% from all and add possibilites*2% to the same tile
		// else 4, 4: 3:8,2:16, 1:32
		float sameTileChange = ((lowestProp-2 >= 5) ? (2):(1<<(4-lowestProp+4)) ) ;// should be higher the lower the ammount of possibilities
		
		if (t == resourceManager::Tiles::stone) {
			if (indX != 0) {
				changeProbOf(&tilesToPlace[x][y], resourceManager::Tiles::stone, ((lowestProb-2>=5)?(sameTileChange):(sameTileChange*(lowestProp-2))));
				changePropOf(&tilesToPlace[x][y], resourceManager::Tiles::sand, -1*sameTileChange); // finish this
			}
		} else if (t == resourceManager::Tiles::sand) {
		}


		--tilesToPlace;
	} 
	
}

void worldGeneration::changeProbOf(std::vector<probability>* p, resourceManager::Tiles t, int16_t change) {
	for (auto* prob : p) {
		if (prob.t != t) continue;
		prob.prob += change;
	}
}
uint16_t worldGeneration::collapse(std::vector<probability>* p) {

	uint16_t rand = dist(gen);
	uint16_t a = 0;

	for (int i = 0;i < p->size(); ++i) {
		a += p->at(i).prob;
		if (rand < a) return i;
	}

	std::cout << "something has seriously gone wrong in worldGeneraion::collapse\n";
}

void worldGeneration::removeProbability(std::vector<resourceManager::Tiles>* p, resourceManager::Tiles t) {
	
}


void worldGeneration::setTile(world* w, resourceManager::Tiles t, uint16_t x, uint16_t y) {
	
	std::cout << "setting tile " << (uint16_t)t << " at " << x << " , " << y << "\n"; 
	switch (t) {
		case resourceManager::Tiles::stone:
			w->setTile(&resourceManager::TextStone, x, y);
			break;
		case resourceManager::Tiles::grass:
			w->setTile(&resourceManager::TextGrass, x, y);
			break;
		case resourceManager::Tiles::sand:
			w->setTile(&resourceManager::TextSand, x, y);
			break;
		case resourceManager::Tiles::water:
			w->setTile(&resourceManager::TextWater, x, y);
			break;
	}

}
