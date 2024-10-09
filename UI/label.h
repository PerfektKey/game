#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "component.h"

class label : public component{
private:
	sf::Text text;
	sf::Font font;
	uint16_t characterSize;
	std::string string;
public:
	label(sf::Vector2f, std::string, sf::Color, uint16_t, std::string);
	virtual ~label();

	virtual void draw(sf::RenderWindow*) const;
	virtual void action(sf::Event, sf::Vector2f);
	
	virtual void focusedMouse(sf::Vector2f);

	sf::Vector2f getPosition() const;
	virtual void setPosition(sf::Vector2f);

	std::string getText() const;
	void setText(std::string);

	void setVisibility(bool);


};
