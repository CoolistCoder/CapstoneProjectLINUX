
#ifndef ENGINE_SPRITE_H_
#define ENGINE_SPRITE_H_

#include "Entity.h"

//sprites will inherit from entities, and the new image class
class Sprite : public Entity, public Image{
private:
	int x, y; //the position data of the sprite
	int w, h; //the width and height of the sprite
	unsigned int framesW, framesH; //the number of horizontal and vertical frames

	int frame; //the frame the sprite is drawn at

	int rotation; //the rotation of the sprite

	static void defaultBehavior(Entity*); //the default behavior of the sprite

public:

	void setPosition(int, int); //set the position of the sprite
	void setSize(int, int); //set the size of the sprite
	void setFrameCount(unsigned int, unsigned int); //set the number of horizontal and vertical frames
	void setFrame(int); //set the current frame

	void draw(); //the draw function for the sprite

	void execute(); //execute the sprite's stored behavior

	Sprite();
	virtual ~Sprite();
};

#endif /* ENGINE_SPRITE_H_ */
