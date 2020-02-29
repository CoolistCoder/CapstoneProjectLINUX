#include "Scene.h"

void Scene::giveEngine(Engine* newEngine){
	if (newEngine){ //we only want to set this if the engine isn't null
		this->knownEngine = newEngine;	//if the engine isn't null, simply put it in there
	}
}

void Scene::setBehavior(void newBehavior(Scene* ns)){
	if (newBehavior){ //if the address location of the function is valid
		this->storedBehavior = newBehavior; //store the address of the function
	}
}

void Scene::execute(){
	this->knownEngine->clearScreen();

	this->storedBehavior(this);

	this->knownEngine->drawScreen();
}

Scene::Scene(Engine* newEngine) {
	// TODO Auto-generated constructor stub
	//This object NEEDS to know what an engine is, if it doesn't, then it defeats the point of having a scene object
	this->giveEngine(newEngine);
}

Scene::~Scene() {
	// TODO Auto-generated destructor stub
}

