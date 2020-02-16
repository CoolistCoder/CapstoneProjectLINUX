/*
 * The Joystick is a small addon for programs that would require better input
 * because it is not a part of either the base engine, nor an entity, it is
 * safe to begin implementing it now
 */


#ifndef ENGINE_JOYSTICK_H_
#define ENGINE_JOYSTICK_H_
#include <SDL2/SDL_image.h>	//We only need SDL2 for this, but due to a bug we include SDL_Image instead
//NOTE: DO NOT NEED TO DO THIS FOR WINDOWS

class Joystick {
private:
	static int totaljoysticks;	//the total number of joysticks
	int joynum;	//the joystick number this joystick is assigned to
	SDL_Joystick* joystick;	//this is the joystick structure we need

public:
	bool getButton(int);	//Function for retrieving the button that's pushed


	Joystick();
	virtual ~Joystick();
};

#endif /* ENGINE_JOYSTICK_H_ */
