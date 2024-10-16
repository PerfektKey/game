#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <string>

class component {
protected:
	sf::Vector2f screenPosition;
	sf::Vector2f relativPosition;
	sf::Vector2f anchorPosition; // to where the relativ position is relativ to
	bool show;
	
	sf::RectangleShape hitbox;
	sf::Vector2f hitboxSize;
	bool focusedByMouse;

	bool movable;

public:
	component(sf::Vector2f, sf::Vector2f);
	component(sf::Vector2f, sf::Vector2f, sf::Color);
	virtual ~component();

	virtual void draw(sf::RenderWindow*) const;
	virtual void action(sf::Event, sf::Vector2f);
	
	virtual void focusedMouse(sf::Vector2f);

	void setMovable(bool);
	bool getMovable() const;

	sf::Vector2f getPosition() const;
	virtual void setPosition(sf::Vector2f);

	void setAnchorPosition(sf::Vector2f);
	sf::Vector2f getAnchorPosition() const;
	sf::Vector2f getRelativPosition() const;
	void setRelativPosition(sf::Vector2f);

	void setVisibility(bool);
	bool getVisibility() const;

};
