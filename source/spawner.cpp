#include "../blocks/spawner.h"

void openInv(component* c) {
	container* cont = c->getParent(); 
	static_cast<container*>(cont->get("inventory UI", 3))->show(true);
}

spawner::spawner(sf::Vector2f sp, world* w, std::string ass, uint16_t sa, uint16_t ss, ItemType st, float ips) : 
	building(sp,w, ass,sa,ss)
{
	
	this->mSpawn = st;
	
	this->type = "Spawner";

	this->timeToSpawn = 1/ips;
}
spawner::~spawner() {}//I dont know if i should delete anythin here?


container* spawner::createUI() const {
	return selectUI();
	return createInventoryUI(&inv);
}

container* spawner::selectUI() const {
	// crreates the UI that gives the ability to select the item to spawn

	container* mCont = new container(NULL);

	// up 50(tile size) + size of board pixels
	component* bg = new component(screenPosition+sf::Vector2f(0, -250), sf::Vector2f(200, 250), mCont, sf::Color(0,0,180,125));
	mCont->add("bg", bg, 3);

	button* b = new button(sf::Vector2f(0,0), sf::Vector2f(50,50), mCont, sf::Color(255,0,0), hideInterface);
	b->setRelativAnchor(bg->getGlobalPosition());
	b->setRelativPosition(sf::Vector2f(10,10));
	mCont->add("closeButton", b, 0);

	button* iob = new button(sf::Vector2f(0,0), sf::Vector2f(50,50), mCont, sf::Color(153, 255, 102), openInv);
	iob->setRelativAnchor(bg->getGlobalPosition());
	iob->setRelativPosition(sf::Vector2f(10,70));
	mCont->add("openInvButton", iob, 0);

	mCont->add("inventory UI", createInventoryUI(&inv), 3);

	label* lsp = new label(sf::Vector2f(0,0), mCont, "assets/arial.ttf", 15, sf::Color::Black, "Spawning: ");
	lsp->setRelativAnchor(bg->getGlobalPosition());
	lsp->setRelativPosition(sf::Vector2f(65, 10));
	mCont->add("spawningInfoLabel", lsp, 0);

	button* bsco = new button(sf::Vector2f(0,0), sf::Vector2f(100,20), mCont, sf::Color(0,0,0));
	bsco->setRelativAnchor(bg->getGlobalPosition());
	bsco->setRelativPosition(sf::Vector2f(50,140));
	mCont->add("selectCopperOre", bsco, 0);
	
	button* bscp = new button(sf::Vector2f(0,0), sf::Vector2f(100,20), mCont, sf::Color(0,0,0));
	bscp->setRelativAnchor(bg->getGlobalPosition());
	bscp->setRelativPosition(sf::Vector2f(50,165));
	mCont->add("selectCopperPlate", bscp, 0);

	return mCont;
}

void spawner::checkButtons(container* c) {
	if (static_cast<button*>(c->get("selectCopperOre", 0))->isPressed())
		mSpawn = ItemType::CopperOre;
	else if (static_cast<button*>(c->get("selectCopperPlate", 0))->isPressed())
		mSpawn = ItemType::CopperPlate;

	static_cast<label*>(c->get("spawningInfoLabel", 0))->setContent("Spawning:\n" + ItemData[mSpawn].name);
}

void spawner::updateUI(container* mCont) {
	if (mCont == NULL) return;	


	checkButtons(mCont);
	updateInventoryUI(static_cast<container*>(mCont->get("inventory UI", 3)), &inv);
}

void spawner::update(float dt, uint16_t frame) {

	// add the time since last frame to the time since the last spawning
	elapsedTime += dt;

	float EPSILON = std::numeric_limits<float>::epsilon();

	while (timeToSpawn - elapsedTime < EPSILON) { // while the elapsed time is less than the time required to spawn, spawn
		this->inv.add(mSpawn, 1); // spawn
		elapsedTime -= timeToSpawn; // reset the elapsed time
		if (elapsedTime < 0) elapsedTime = 0; // if the elapsed time is less than 0, set it to 0
		// update labels
	}
}
