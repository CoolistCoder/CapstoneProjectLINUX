
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
	Joystick* knownJoystick; //the joystick that the entity is given
	Engine* knownEngine; //the engine known by the entity

	//the camera-modified positions of Entities.  Only entities that need them will use them.
	int modposX, modposY;

	std::vector<Entity*> attachedEntities; //list of entities connected to this entity

public:
	void setBehavior(void(Entity*)); //sets the behavior of the entity

	void setPriority(unsigned int p) { this->priority = p; }; //simply set this instances's priority index
	unsigned int getPriority() { return this->priority; }; //simply return this instance's priority index

	void giveJoystick(Joystick*); //gives the entity a joystick
	Joystick* getJoystick(); //get the joystick associated with this entity

	//attachment functions
	void attachEntity(Entity*); //attaches an entity one way to this entity
	void coupleEntity(Entity*); //attaches an entity two ways to this entity
	Entity* getAttachedEntity(unsigned int); //get the attached entity by index
	//Entity* getAttachedEntity(Entity*); //get the attached entity by address (not very useful)
	void detachEntity(Entity*); //detach a specified entity
	void decoupleEntity(Entity*); //remove a specified entity from both entities

	//engine functions
	void setEngine(Engine* e) { this->knownEngine = e;}; //let the entity know about the engine
	Engine* getEngine() { return this->knownEngine; }; //retrieve the engine known by the entity

	void modifyOffset(int, int); //modify the modposx and modposy variables within the entity

	virtual void execute() = 0; //pure virtual function for executing the entity's stored behavior

	Entity();
	virtual ~Entity();
};

#endif /* ENGINE_ENTITY_H_ */
