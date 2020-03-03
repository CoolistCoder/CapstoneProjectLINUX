

#include "Entity.h"

void Entity::setBehavior(void newBehavior(Entity* e)){
	//like the scene, just give the stored variable the function
	this->storedBehavior = newBehavior;
}

Entity::Entity() {
	// TODO Auto-generated constructor stub
	this->priority = 0; //if priorities match they're drawn in order of when they're added
}

Entity::~Entity() {
	// TODO Auto-generated destructor stub
}

