#include "../blocks/vault.h"


vault::vault(sf::Vector2f sp, world* w, uint16_t sa, uint16_t ss) :
	building(sp, w, sa ,ss) {
	
	this->type = "Vault";
}
