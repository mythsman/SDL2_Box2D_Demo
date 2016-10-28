/*
 * Rope.h
 *
 *  Created on: Oct 28, 2016
 *      Author: myths
 */

#ifndef ROPE_H_
#define ROPE_H_

#include"Drawable.h"
#include"Ball.h"
#include"Box.h"
#include<SDL2/SDL.h>
#include<Box2D/Box2D.h>
#include<vector>
class Rope: public Drawable {
private:
	b2World *world;
	SDL_Renderer *render;
	std::vector<Box*> boxes;
	double length;
	double width;
public:
	Rope(b2World *w, SDL_Renderer *r, double length, double width = 0.05);
	void draw();
};

#endif /* ROPE_H_ */
