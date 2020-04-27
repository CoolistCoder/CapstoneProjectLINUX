
#include "Text.h"

void Text::defaultBehavior(Entity* e){
	static_cast<Text*>(e)->drawText(); //just draw the text
}

void Text::setString(std::string _str){
	//check to see if the string is valid
	if (!_str.empty()){
		//now just set the string
		this->string_to_draw = _str;
		//create all of our tiles that we need
        Tile* newtile; //generate our tile pointer to add our data to the tilemap
        //create a for loop to determine what attribs to give our tile
		for (unsigned int i = 0; i < this->string_to_draw.size(); i++){
            newtile = new Tile; //create our new tile
            newtile->setFrame(i); //set the frame of the sprite based on the value at arr[i]
            newtile->setSize(16,16);
            newtile->setEngine(this->getEngine()); //give our tiles the necessary engine
            newtile->shareImage(this);
            this->tiles.push_back(newtile); //add the tile to the tilemap
            std::cout << i << std::endl;
		}
	}
}

void Text::clearString(){
	//simply clear the string
	this->string_to_draw.clear();
	//then clear all the tiles in the vector
    for (unsigned int i = 0; i < this->tiles.size(); i++) {
    	this->tiles[i]->nullify(); //nullify the images first
    	delete this->tiles[i]; //empty the tiles from the vector
    }
    this->tiles.clear(); //clear out all empty tiles
}

std::string Text::getString(){
	return this->string_to_draw; //retrieve the stored string
}

void Text::drawText(){
    if (this->getEngine()) { //Check to see if we have a valid engine FIRST
        //go through each tile stored in our vector and draw it
        for (unsigned int i = 0; i < this->tiles.size(); i++) {
            this->tiles[i]->setPosition
            (
                i,
                0
            );
            if (this->assignedcamera) //we need to be absolutely certain that the tiles are being assigned properly
            	this->tiles.at(i)->assigned();
            this->tiles[i]->modifyOffset(this->modposX, this->modposY);
            this->tiles[i]->modifyRenderArea(this->renderAreaW, this->renderAreaH);
            this->tiles[i]->setViewData(this->viewarx, this->viewary, this->viewarw, this->viewarh);

            this->tiles.at(i)->draw();
        }
    }
}

void Text::execute(){
	this->storedBehavior(this); //execute the stored behavior
}

Text::Text() {
	// TODO Auto-generated constructor stub
	this->loadImage("text.png"); //load in the default text
	//make sure we have the default font
	if (!this->empty()){ //if we do have the font, use the data from the font
		this->x = 0;
		this->y = 0;
		this->w = this->storedSource->w / 16; //these are the values assigned to each character
		this->h = this->storedSource->h / 6;
		this->hasfont = true;
	}
	else { //if we don't have the font, give it some default values
		this->x = 0;
		this->y = 0;
		this->w = 1;
		this->h = 1;
		this->hasfont = false;
	}

	this->setBehavior(Text::defaultBehavior);


}

Text::~Text() {
	// TODO Auto-generated destructor stub
	this->clearString();
}

