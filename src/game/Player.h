//the player is a sprite and therefore inherits from that object

#ifndef GAME_PLAYER_H_
#define GAME_PLAYER_H_
#include "../Engine/Sprite.h"
#include "../Engine/Tilemap.h"
#include "../Engine/Line.h"

class Player : public Sprite{
private:
private:
	//we need behaviors that reflect the state the player is in
	void control(Entity*); //this is the normal control state
	void die(Entity*); //this is the death state when the player dies
	void setup(Entity*); //this is the state that sets up the player and its variables

	//we need to have a few pointers to keep track of things
	Line* laser; //the laser projectile the player will launch
	Tilemap* walls; //the walls that the player must be aware of



public:

	void execute(); //execute the stored behavior

	Player();
	virtual ~Player();
};

#endif /* GAME_PLAYER_H_ */
