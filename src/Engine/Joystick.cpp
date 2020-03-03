#include "Joystick.h"

int Joystick::totaljoysticks = 0;

void Joystick::detect(){
	//To redetect the joystick we just need to open it agian
	this->joystick = SDL_JoystickOpen(this->joynum);
}


void Joystick::updateSticks(){
	//update the left stick first because that one is usually used for character movement
	//The way the sticks work in Xinput is kind of weird, so X and Y axis pertains to the left stick
	this->leftjoyX = SDL_JoystickGetAxis(this->joystick, 0) / 125; //divide the amount returned by 125 to get a smaller result
	this->leftjoyY = SDL_JoystickGetAxis(this->joystick, 1) / 125; //same for all axis'
	this->rightjoyX = SDL_JoystickGetAxis(this->joystick, 3) / 125; //the right joystick is defined by this axis
	this->rightjoyY = SDL_JoystickGetAxis(this->joystick, 4) / 125;

}

bool Joystick::getButton(int button){
	//simply return the specified button if the joystick is pressing it down
	return SDL_JoystickGetButton(this->joystick, button);
}

bool Joystick::getPad(int dir){
	//We only need to get the direction and make sure it's true
	if (SDL_JoystickGetHat(this->joystick, 0) == dir)
	return true;	//if the direction of the single dpad on the joypad is pressed, we can return true
	return false;	//otherwise it returns false
}

int Joystick::getLeftStickX(){
	//before doing anything, the positions need to be updated
	this->updateSticks();
	return this->leftjoyX; //simply return the left joystick's X position
}

int Joystick::getLeftStickY(){
	//before doing anything, the positions need to be updated
	this->updateSticks();
	return this->leftjoyY; //simply return the left joystick's Y position
}

int Joystick::getRightStickX(){
	//before doing anything, the positions need to be updated
	this->updateSticks();
	return this->rightjoyX; //simply return the right joystick's X position
}

int Joystick::getRightStickY(){
	//before doing anything, the positions need to be updated
	this->updateSticks();
	return this->rightjoyY; //simply return the right joystick's Y position
}


int Joystick::getTotalJoysticks(){
	return Joystick::totaljoysticks;	//simply return how many joysticks we've got
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

	//set the joystick values to 0 so we don't get any weird yellow lines in the code
	this->leftjoyX = 0;
	this->leftjoyY = 0;
	this->rightjoyX = 0;
	this->rightjoyY = 0;

}

bool Joystick::getPluggedIn(){
	//NOTE: this will only work if the joystick was plugged in already
	return SDL_JoystickGetAttached(this->joystick);
}

Joystick::~Joystick() {
	// TODO Auto-generated destructor stub
	//for some odd reason, closing the joystick causes a double free
	//This is to do with something changed on the Linux end of things
	//regardless, nothing happens here except a decrease in the number of joysticks
	this->totaljoysticks--;
}

