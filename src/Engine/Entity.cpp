

#include "Entity.h"

void Entity::setBehavior(void newBehavior(Entity* e)){
	//like the scene, just give the stored variable the function
	this->storedBehavior = newBehavior;
}

void Entity::giveJoystick(Joystick* newjoystick){
	//simply give the entity the joystick
	if (newjoystick){
		this->knownJoystick = newjoystick;
	}
}

Joystick* Entity::getJoystick(){
	//just return the stored joystick
	return this->knownJoystick;
}

Entity::Entity() {
	// TODO Auto-generated constructor stub
	this->priority = 0; //if priorities match they're drawn in order of when they're added
	this->knownJoystick = nullptr; //initially, there is no joystick
}

Entity::~Entity() {
	// TODO Auto-generated destructor stub
}

