
#include "Sprite.h"

void Sprite::setPosition(int x, int y){
	//set the position of the sprite with the x and y
	this->x = x;
	this->y = y;
}

void Sprite::setSize(int w, int h){
	//limit the width and height so they can't be less than 0
	if (w > 0){
		this->w = w;
	}
	if (h > 0){
		this->h = h;
	}
}

void Sprite::defaultBehavior(Entity* d){
	//by default, simply draw the sprite
	static_cast<Sprite*>(d)->draw();
}

void Sprite::draw(){
	//we only want to implement the draw if the sprite has data
	if (!this->empty()){

		glMatrixMode(GL_TEXTURE);
		glLoadIdentity();

		glScaled(1.0/this->storedSource->w, 1.0/this->storedSource->h, 1.0);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glBegin(GL_QUADS);
			glVertex2i(this->x + this->modposX, this->y + this->modposY);
			glVertex2i(this->x + this->w + this->modposX, this->y + this->modposY);
			glVertex2i(this->x + this->w + this->modposX, this->y + this->h + this->modposY);
			glVertex2i(this->x + this->modposX, this->y + this->h + this->modposY);

		glEnd();

		glMatrixMode(GL_TEXTURE);
		glLoadIdentity();

	}
}

void Sprite::execute(){

}

Sprite::Sprite() {
	// TODO Auto-generated constructor stub
	//initialize everything to 0 and 1, we don't have any data starting out
	this->x = 0;
	this->y = 0;
	this->w = 1;
	this->h = 1;

	//set the frame to 0, as we have no information regarding that yet
	this->frame = 0;

	//set the rotation of the sprite to 0, we have no data for this yet
	this->rotation = 0;


	//set the default behavior of the sprite
	this->setBehavior(Sprite::defaultBehavior);
}

Sprite::~Sprite() {
	// TODO Auto-generated destructor stub
}

