/*
 * SceneOne.h
 *
 *  Created on: Oct 29, 2016
 *      Author: myths
 */

#ifndef SCENEONE_H_
#define SCENEONE_H_
#include"Scene.h"
#include<list>
class SceneOne: public Scene {
private:
	const double PTM_RATIO = 100.0;
	std::vector<Drawable*> items;
	std::list<SDL_Point> mouseList;
	SDL_Texture *textureBg;
	b2World *world;
public:
	SceneOne(SDL_Window *win, SDL_Renderer *ren);
	int execute();
	void step();
	void paint();
	~SceneOne();
};

#endif /* SCENEONE_H_ */
