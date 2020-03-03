#include "Scene.h"

//there are always 0 scenes at the start
unsigned int Scene::numscenes = 0;
std::vector<Scene*> Scene::allScenes;

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

void Scene::addEntity(Entity* newEntity){
	 //only add an entity if the entity isn't null
	if (newEntity){
		this->entitiesInScene.push_back(newEntity); //give us the brand new entity
	}
}

void Scene::execute(){
	//the execute function works like a normal loop
	//executed within the main loop

	//clear the screen
	this->knownEngine->clearScreen();

	//perform any behavior that is stored
	this->storedBehavior(this);

	//handle all of the entities here
	for (unsigned int i=0; i<this->entitiesInScene.size(); i++){
		//TODO run the execute function for each entity
	}

	//draw the screen
	this->knownEngine->drawScreen();
}

void Scene::cleanup(){
	//go through each instance of scene and delete it from memory
	for (unsigned int i=0; i < Scene::allScenes.size(); i++){
		delete allScenes.at(i);
	}
}

Scene::Scene(Engine* newEngine) {
	// TODO Auto-generated constructor stub
	//This object NEEDS to know what an engine is, if it doesn't, then it defeats the point of having a scene object
	this->giveEngine(newEngine);
	Scene::numscenes++; //increment the number of scenes
}

Scene::~Scene() {
	// TODO Auto-generated destructor stub

	//TODO clean up the entities loaded into the scene

	//if there is only one scene left
	if (Scene::numscenes <= 1){
		//just delete all of the scenes
		Scene::cleanup();
	}
	Scene::numscenes--; //decrement the number of scenes
}

