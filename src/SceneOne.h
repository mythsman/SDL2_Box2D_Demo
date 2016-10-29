/*
 * SceneOne.h
 *
 *  Created on: Oct 29, 2016
 *      Author: myths
 */

#ifndef SCENEONE_H_
#define SCENEONE_H_
#include"Scene.h"
class SceneOne: public Scene {
public:
	SceneOne(SDL_Window *win, SDL_Renderer *ren, b2World *wor,
			std::vector<Drawable*>*items);
	int execute();

};

#endif /* SCENEONE_H_ */
