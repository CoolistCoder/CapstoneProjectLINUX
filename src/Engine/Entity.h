
#ifndef ENGINE_ENTITY_H_
#define ENGINE_ENTITY_H_
#include "Engine.h"
#include <functional>

//all instances within the engine are entities
//to make games, these can be used to make development easier

class Entity {
protected:
	std::function<void(Entity* e)> storedBehavior; //the behavior stored in the entity
	unsigned int priority; //the priority of the entity and when it is handled in the vector

public:
	void setBehavior(void(Entity*)); //sets the behavior of the entity

	void setPriority(unsigned int p) { this->priority = p; }; //simply set this instances's priority index
	unsigned int getPriority() { return this->priority; }; //simply return this instance's priority index

	virtual void execute() = 0; //pure virtual function for executing the entity's stored behavior

	Entity();
	virtual ~Entity();
};

#endif /* ENGINE_ENTITY_H_ */
