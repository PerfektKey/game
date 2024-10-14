#include "../blocks/inserter.h"
#include "../header/world.h"

inserter::inserter(sf::Vector2f sp, world* w, float sd, uint16_t ts): 
	building(sp, w, 1, ts) {
	this->speed = sd;
	this->timer = 0;
	this->transferSize = ts;

	this->type = "Inserter";
}


void inserter::update(float dt) {
	timer += dt;
//	std::cout << "\033[31mUPDATING INSERTER " << this << "\033[37m\n";
//	std::cout << "\tcurrent timer: " << timer << "\n";
//	std::cout << "\tplanned source building location: (x)" << (mapPosition.x - 1) << "\n"; 
//	std::cout << "\tplanned target building location: (x)" << (mapPosition.x + 1) << "\n"; 

	if (timer < speed) return;
	timer -= speed;
	
	building* source = WORLD->getBuilding(mapPosition - sf::Vector2f(1, 0));
	building* target = WORLD->getBuilding(mapPosition + sf::Vector2f(1, 0));
	
//	std::cout <<"\tsource: " << source << "\n";
//	std::cout <<"\ttarget: " << target << "\n";

	if (source == NULL || target == NULL) return;

	inventory* sourceINV = source->getInventory();	
	inventory* targetINV = target->getInventory();
	
//	std::cout <<"\tsource inventory: " << sourceINV << "\n";
//	std::cout <<"\ttarget inventory: " << targetINV << "\n";

//	std::cout << "\ttesting source inventory pointer existence: \n"; *sourceINV;
//	std::cout << "\ttesting target inventory pointer existence: \n"; *targetINV;

	if (sourceINV == NULL || targetINV == NULL) return;	

//	std::cout << "\033[31mPerforming Item Transfer: \033[37m\n";

	ItemType ItemToTransfer = sourceINV->getLastItem();
//	std::cout << "\ttransfer item: " << ItemData[ItemToTransfer].name << "\n";
	if (ItemToTransfer == ItemType::EMPTY) return;
	uint16_t transfered = sourceINV->remove(ItemToTransfer , transferSize);
//	std::cout << "\tmanaged to transfer: " << transfered << "\n";
	targetINV->add(ItemToTransfer , transfered);

}
