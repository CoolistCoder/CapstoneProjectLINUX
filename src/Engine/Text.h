#ifndef ENGINE_TEXT_H_
#define ENGINE_TEXT_H_
#include "Tile.h"

class Text : public Image, public Entity{

private:
	std::string string_to_draw; //the string that will be drawn to the string

public:
	Text();
	virtual ~Text();
};

#endif /* ENGINE_TEXT_H_ */
