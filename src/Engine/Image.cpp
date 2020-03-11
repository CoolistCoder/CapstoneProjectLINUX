#include "Image.h"

void Image::loadImage(const char* imageName){
	//TODO implement image load
}

bool Image::empty(){
	//Check to see if the source failed to load
	//if the source fails, just return false
	if (!this->storedSource){
		return false;
	}
	//check to see if the image drawn isn't there
	//if the drawn image returns 0, return false
	if (this->image == 0){
		return false;
	}

	//return true if the other returns don't trigger
	return true;
}

Image::Image() {
	// TODO Auto-generated constructor stub
	this->storedSource = nullptr; //this is a pointer, init it to a nullptr
	this->image = 0; //because this is an integer at heart, we can initialize it to 0

}

Image::~Image() {
	// TODO Auto-generated destructor stub
}

