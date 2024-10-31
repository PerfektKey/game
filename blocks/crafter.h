#pragma once

#include "../header/building.h"
#include <unordered_map> // will be fast enough

//Recepies:
//	1. NAME
//	2. Items : Ammount
//	3. Time to create
//	4. Energie? liquid?
//

struct recepie {
	std::vector<slot> mInputs;
	std::vector<slot> mOutputs;
	float mTime;
	
	recepie(float, std::vector<slot>, std::vector<slot>);
};

class crafter : public building {
private:
	inventory mOutputInv; // normal inv as input

	float mTimeModifier; // if a recepie takes 10 seconds and this is 2, the recepie takes 5 seconds. recepie.time/mTimeModifier = actual wait time
	float mTimer;

	const std::unordered_map<std::string, recepie>* mRecepies;
	
	std::string mCurrentRecepieName;
	const recepie* mCurrentRecepie;
	
	bool selectRecepie(const std::string&);
public:
	crafter(sf::Vector2f, world*, std::string, std::unordered_map<std::string, recepie>*, float);

	inventory* getOutput();

	virtual void update(float,uint16_t);
};
