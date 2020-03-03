

#include "Entity.h"

void Entity::setBehavior(void newBehavior(Entity* e)){
	//like the scene, just give the stored variable the function
	this->storedBehavior = newBehavior(this);
}

Entity::Entity() {
	// TODO Auto-generated constructor stub

}

Entity::~Entity() {
	// TODO Auto-generated destructor stub
}

