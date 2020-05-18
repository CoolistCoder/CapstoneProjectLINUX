#ifndef GAME_SCORE_H_
#define GAME_SCORE_H_
#include "../Engine/Text.h"
#include "Player.h"

class Score : public Text{
private:
	int score; //the player's score
	static void defaultBehavior(Entity*); //by default, it updates and draws itself
	Player* knownPlayer; //the known player
public:

	void givePlayer(Player*); //give the score a player to track


	Score();
	virtual ~Score();
};

#endif /* GAME_SCORE_H_ */
