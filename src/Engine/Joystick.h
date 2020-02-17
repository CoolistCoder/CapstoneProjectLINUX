/*
 * The Joystick is a small addon for programs that would require better input
 * because it is not a part of either the base engine, nor an entity, it is
 * safe to begin implementing it now
 */


#ifndef ENGINE_JOYSTICK_H_
#define ENGINE_JOYSTICK_H_
#include <SDL2/SDL_image.h>	//We only need SDL2 for this, but due to a bug we include SDL_Image instead
//NOTE: DO NOT NEED TO DO THIS FOR WINDOWS

#include <iostream>

class Joystick {
private:
	static int totaljoysticks;	//the total number of joysticks
	int joynum;	//the joystick number this joystick is assigned to
	SDL_Joystick* joystick;	//this is the joystick structure we need

	//these functions update the left and right sticks on a standard xinput controller
	int leftjoyX, leftjoyY; //this is where the information on the left joystick will be kept
	int rightjoyX, rightjoyY;	//this is where the information on the right joystick will be kept

	void updateSticks();	//this updates the stick positions

public:
	bool getButton(int);	//Function for retrieving the button that's pushed
	bool getPad(int); 		//Function for retrieving the current direction of the pad
	int getLeftStickX();	//Function for getting hte position of the left stick's X position
	int getLeftStickY();	//Function for getting hte position of the left stick's Y position
	int getRightStickX();	//Function for getting hte position of the right stick's X position
	int getRightStickY();	//Function for getting hte position of the right stick's Y position

	void detect();	//this simply finds the joystick again if it was removed
	static int getTotalJoysticks();	//this returns how many total joysticks were instanciated

	Joystick();
	virtual ~Joystick();
};

#endif /* ENGINE_JOYSTICK_H_ */
