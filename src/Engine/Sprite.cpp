
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

		//we need to get some data
		const unsigned int total_subimages = this->framesW * this->framesH; //the total subimages made from the image

		//make sure we set the mode to gl_texture
		glMatrixMode(GL_TEXTURE);
		glLoadIdentity();

		//we want to make sure that when we load in a texture, we use its pixel coordinates
		//doing this adjusts its scale to the image's size
		glScaled(1.0/this->storedSource->w, 1.0/this->storedSource->h, 1.0);

		//now set up modelview
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//set up the texture parameters so the image will draw using the precise pixels
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		//bind the parameters to the image
		glBindTexture(GL_TEXTURE_2D, this->image);

		//enable texture drawing
		glEnable(GL_TEXTURE_2D);

		//TODO IMPLEMENT THE SUBIMAGE DRAWING
		//begin drawing
		glBegin(GL_QUADS);
			glTexCoord2i(0,0); //top left of the subimage
			glVertex2i(this->x + this->modposX, this->y + this->modposY); //top left of sprite

			glTexCoord2i(16,0); //top right of the subimage
			glVertex2i(this->x + this->w + this->modposX, this->y + this->modposY); //top right of sprite

			glTexCoord2i(16,16); //bottom right of the subimage
			glVertex2i(this->x + this->w + this->modposX, this->y + this->h + this->modposY); //bottom right of sprite

			glTexCoord2i(0,16);  //bottom left of the subimage
			glVertex2i(this->x + this->modposX, this->y + this->h + this->modposY); //bottom left of sprite

		glEnd();

		glMatrixMode(GL_TEXTURE);
		glLoadIdentity();

		glDisable(GL_TEXTURE_2D);

	}
}

void Sprite::execute(){
	//execute the stored behavior
	this->storedBehavior(this);
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

