
#ifndef ENGINE_SPRITE_H_
#define ENGINE_SPRITE_H_

#include "Entity.h"

//sprites will inherit from entities, and the new image class
class Sprite : public Entity, public Image{
private:
	int x, y; //the position data of the sprite
	int w, h; //the width and height of the sprite

	int frame; //the frame the sprite is drawn at

	int rotation; //the rotation of the sprite

	static void defaultBehavior(Entity*);

public:

	void setPosition(int, int);
	void setSize(int, int);

	void draw(); //the draw function for the sprite

	void execute(); //execute the sprite's stored behavior

	Sprite();
	virtual ~Sprite();
};

#endif /* ENGINE_SPRITE_H_ */
