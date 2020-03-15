
#ifndef ENGINE_SPRITE_H_
#define ENGINE_SPRITE_H_

#include "Entity.h"

//sprites will inherit from entities, and the new image class
class Sprite : public Entity, public Image{
private:
	int x, y; //the position data of the sprite
	int w, h; //the width and height of the sprite

	int frame; //the frame the sprite is drawn at

public:

	void draw(); //the draw function for the sprite

	void execute();

	Sprite();
	virtual ~Sprite();
};

#endif /* ENGINE_SPRITE_H_ */
