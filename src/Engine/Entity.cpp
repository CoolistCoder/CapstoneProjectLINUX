

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


void Entity::attachEntity(Entity* newEntity) {
	//sometimes, we need an entity to be aware of another one
	//by simply providing the entity with another one, we can allow it to use values from the other one
	this->attachedEntities.push_back(newEntity); //attach the new entity to this entity
}
void Entity::combineEntity(Entity* newEntity){
	//this one works the same as the attachEntity function but also attaches this entity to the other entity
	this->attachedEntities.push_back(newEntity); //attach the new entity to this entity
	newEntity->attachedEntities.push_back(this); //attach this entity to the new entity
}

Entity* Entity::getAttachedEntity(unsigned int index){
	//this will return nullptr if the index is not valid
	if (index < this->attachedEntities.size()){
		return this->attachedEntities.at(index); //if it is valid it will return the entity stored at this index
	}
	return nullptr;
}

Entity::Entity() {
	// TODO Auto-generated constructor stub
	this->priority = 0; //if priorities match they're drawn in order of when they're added
	this->knownJoystick = nullptr; //initially, there is no joystick
	this->knownEngine = nullptr;
}

Entity::~Entity() {
	// TODO Auto-generated destructor stub
}

