#include "../UserInterface/label.h"


label::label(sf::Vector2f p, container* parent, std::string fp, uint16_t cs, sf::Color c, std::string cont) :
	component(p, sf::Vector2f(cont.length()*cs , cs) , parent) { // position , font path , char size, char color , content
	
	loadFont(fp);
	
	mCharSize = cs;
	mColor = c;

	mContent = cont;

	mText.setFillColor(mColor);
	mText.setPosition(mGlobalPosition);
	mText.setCharacterSize(mCharSize);
	mText.setString(mContent);
}

void label::draw(sf::RenderWindow* w){
	// setting text of mText here, because otherwise it will never be updated
	mText.setPosition(mGlobalPosition);
	w->draw(mText);
}

void label::setContent(std::string s) {
	mContent = s;
	mText.setString(mContent);
}
std::string label::getContent() const {return mContent;}

void label::loadFont(std::string s) {
	// load font, set text to font
	mFontPath = s;

	if ( !mFont.loadFromFile(mFontPath) ) {
		std::cerr << "\033[31mFont: " << mFontPath << "not loadable\033[37m\n";
		std::exit(EXIT_FAILURE);
	}
	mText.setFont(mFont);
}
std::string label::getFontPath() const {return mFontPath;}

void label::setColor(sf::Color c) {
	mColor = c;
	mText.setColor(c);
}

void label::setCharSize(uint16_t cs) {
	mCharSize = cs;
	mText.setCharacterSize(cs);
}
uint16_t label::getCharSize() const {return mCharSize;}
