#include "../blocks/vault.h"


vault::vault(sf::Vector2f sp, world* w, std::string ass, uint16_t sa, uint16_t ss) :
	building(sp, w, ass, sa ,ss) {
	
	this->type = "Vault";
}
