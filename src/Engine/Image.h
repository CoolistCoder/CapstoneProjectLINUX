//image loading library for creating objects that require images

#ifndef ENGINE_IMAGE_H_
#define ENGINE_IMAGE_H_
#include <SDL2/SDL_image.h> //image library
#include <GL/gl.h> //the library that stores the image

class Image {
private:
	SDL_Surface* storedSource; //The source image, stored into the image object
	GLuint image; //The image that will be drawn

public:
	void loadImage(const char*); //loads an image from a source file
	bool empty();

	Image();
	virtual ~Image();
};

#endif /* ENGINE_IMAGE_H_ */
