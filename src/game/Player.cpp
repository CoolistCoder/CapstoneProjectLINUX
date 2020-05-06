
#include "Player.h"

void Player::control(Entity* p){

}

void Player::die(Entity* p){

}

void Player::setup(Entity* p){

}

void Player::execute(){
	//execute the stored behavior
	this->storedBehavior(this);
}

Player::Player() {
	// TODO Auto-generated constructor stub

}

Player::~Player() {
	// TODO Auto-generated destructor stub
}

