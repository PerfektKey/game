#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class tile {
private:
	sf::Vector2f mWorldPosition;
	sf::Vector2f mScreenPosition;
	sf::Vector2f* pCameraPosition;

	sf::Texture* pTexture;
	sf::Sprite mSprite;

public:
	tile();
	tile(sf::Vector2f*);

	void draw(sf::RenderWindow*);
	
	sf::Vector2f getScreenPosition() const;
	sf::Vector2f getWorldPosition() const;

	void setWorldPosition(const sf::Vector2f&);
	void setTexture(sf::Texture*);
};
