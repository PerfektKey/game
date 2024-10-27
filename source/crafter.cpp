#include "../blocks/crafter.h"


recepie::recepie(float time, std::vector<slot> inputs, std::vector<slot> outs) {
	mTime = time;
	mInputs = inputs;
	mOutputs = outs;
}

crafter::crafter (sf::Vector2f p, world* w, std::unordered_map<std::string, recepie>* recs, float sp) :
	building(p,w,1,1) {
	
	mRecepies = recs;	
	mTimeModifier = sp;

	mCurrentRecepie = NULL;
	mCurrentRecepieName = "";
	
	selectRecepie("Test 101");
}


bool crafter::selectRecepie(const std::string& rec) {
	if (mRecepies->find(rec) == mRecepies->end()) return false;
	
	if (mCurrentRecepieName == rec) return true;

	mCurrentRecepie     = &mRecepies->at(rec);
	mCurrentRecepieName = rec;

	// need to resize inventory -> just create new inventory
	inv = inventory(mCurrentRecepie->mInputs.size(), 20+1);

	// adding one of all the required inputs
	for (const slot& s : mCurrentRecepie->mInputs) {
		inv.add(s.type, 1);
	}

	mOutputInv = inventory(mCurrentRecepie->mOutputs.size(), 20+1);

	inv.print();

	return true;
}


void crafter::update(float dt, uint16_t frame) {
	if (frame == mFrame) return;
	mFrame = frame;

	if (mCurrentRecepie == NULL) return;
	// checking if enough of all items have been gathered 	
	for (const slot& s : mCurrentRecepie->mInputs) {
		const slot* inp = inv.get(s.type);
		if (inp->ammount-1 < s.ammount) {
			// not enough
			mTimer = 0;
			return;
		}
	}
	
	// check if enought place is in the output
	for (const slot& s : mCurrentRecepie->mOutputs) {
		const slot* inp = mOutputInv.get(s.type);
		if (inp == NULL) continue;
		if (inp->ammount+s.ammount > 20) {
			mTimer = 0;
			return;	
		}
	}
	

	// actual processing
	mTimer += dt;
	if (mTimer*mTimeModifier < mCurrentRecepie->mTime) return;

	mTimer -= mCurrentRecepie->mTime/mTimeModifier;

	for (const slot& s : mCurrentRecepie->mOutputs) {
		mOutputInv.add(s.type, s.ammount);	
	}
	for (const slot& s : mCurrentRecepie->mInputs) {
		inv.remove(s.type, s.ammount);	
	}
	
	mOutputInv.print();
}
