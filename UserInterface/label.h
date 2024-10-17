#pragma once

#include "component.h"
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

class label : public component {
private:
	std::string mContent;

	// font
	std::string mFontPath;
	sf::Font mFont;

	// text object
	sf::Text mText;
	uint16_t mCharSize;
	sf::Color mColor;

public:
	label(sf::Vector2f, container*, std::string, uint16_t, sf::Color, std::string); // position , font path , char size, char color , content

	virtual void draw(sf::RenderWindow*);

	void setString(std::string);
	std::string getContent() const;

	void loadFont(std::string);
	std::string getFontPath() const;

	void setColor(sf::Color);

	void setCharSize(uint16_t);
	uint16_t getCharSize() const;
};
