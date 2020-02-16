#include "Joystick.h"

int Joystick::totaljoysticks = 0;

bool Joystick::getButton(int button){
	//simply return the specified button if the joystick is pressing it down
	return SDL_JoystickGetButton(this->joystick, button);
}

Joystick::Joystick() {
	// TODO Auto-generated constructor stub
	//first we need to set the current joystick's number to the total
	this->joynum = Joystick::totaljoysticks;
	//now we need to increment the totaljoysticks
	Joystick::totaljoysticks++;
	//This will allow us to start any arrays involving joysticks from 0

	//Now that we have the joystick number, we can open the joystick
	this->joystick = SDL_JoystickOpen(this->joynum);
	//the Joystick's index is based on its number
}

Joystick::~Joystick() {
	// TODO Auto-generated destructor stub
	//for some odd reason, closing the joystick causes a double free
	//This is to do with something changed on the Linux end of things
	//regardless, nothing happens here except a decrease in the number of joysticks
	this->totaljoysticks--;
}

