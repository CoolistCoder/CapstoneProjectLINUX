
#ifndef ENGINE_ENTITY_H_
#define ENGINE_ENTITY_H_
#include "Engine.h"
#include <functional>

//all instances within the engine are entities
//to make games, these can be used to make development easier

class Entity {
private:
	std::function<void(Entity*)> storedBehavior; //the behavior stored in the entity


public:
	void setBehavior(void(Entity*)); //sets the behavior of the entity

	//virtual void execute() = 0; //pure virtual function for executing the entity

	Entity();
	virtual ~Entity();
};

#endif /* ENGINE_ENTITY_H_ */
