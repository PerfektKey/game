#pragma once

#include <SFML/Graphics.hpp>

class component {
protected:
	sf::Vector2f mGlobalPosition;
	sf::Vector2f mRelativPosition;
	sf::Vector2f mRelativAnchor;

	sf::RectangleShape mHitbox;
	sf::Vector2f mHitboxSize;
public:
	component(sf::Vector2f, sf::Vector2f); // position on screen and size
	component(sf::Vector2f, sf::Vector2f, sf::Color); // position on screen and size
					      
	virtual void draw(sf::RenderWindow*) const;

	void setSize(sf::Vector2f);
	sf::Vector2f getSize() const;

	void setGlobalPosition(sf::Vector2f);
	sf::Vector2f getGlobalPosition() const;

	void setRelativPosition(sf::Vector2f);
	sf::Vector2f getRelativPosition() const;

	void setRelaticAnchor(sf::Vector2f);
	sf::Vector2f getRelativAnchor() const;
};
