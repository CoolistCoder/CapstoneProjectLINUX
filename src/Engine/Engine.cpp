

#include "Engine.h"

void Engine::init(){

}

void Engine::end(){

}

void Engine::makeWindow(unsigned int w, unsigned int h, std::string title){

}

void Engine::setGLDefaults(){
	//TODO implement this during the make window routine
}

bool Engine::getRunning(){
	//not much to it, just get the isrunning variable and return it
	return this->isrunning;
}

void Engine::clearScreen(){

}

void Engine::drawScreen(){

}

void Engine::setPosition(unsigned int x, unsigned int y){

}

void Engine::setSize(unsigned int w, unsigned int h){

}

void Engine::setName(std::string newname){

}

void Engine::setFPS(unsigned int newFPS){

}

Engine::Engine() {
	//begin by setting the defaults of everything
	this->context = 0; //don't need the context yet
	this->window = nullptr;		//no window has been created
	this->isrunning = false;	//the window is not running, therefore this is false for now
	this->success = true;	//this is set to true by default, but if anything wrong happens during init, change it
	this->framerate = 60;	//by default, the engine runs at 60 hrz

	this->init();	//perform the init after the engine's default values have been set

}

Engine::~Engine() {
	//clear out the engine once it has been deleted
	this->end();
}

