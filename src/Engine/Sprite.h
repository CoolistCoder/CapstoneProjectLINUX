
#ifndef ENGINE_SPRITE_H_
#define ENGINE_SPRITE_H_

#include "Entity.h"

//sprites will inherit from entities, and the new image class
class Sprite : public Entity, public Image{
public:

	void execute();

	Sprite();
	virtual ~Sprite();
};

#endif /* ENGINE_SPRITE_H_ */
