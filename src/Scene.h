/*
 * Scene.h
 *
 *  Created on: Oct 29, 2016
 *      Author: myths
 */

#ifndef SCENE_H_
#define SCENE_H_
#include<SDL2/SDL.h>
#include<Box2D/Box2D.h>
#include<vector>
#include"Drawable.h"
#include<vector>
class Scene {
public:
	SDL_Renderer *render;
	SDL_Window *window;
	b2World *world;
	std::vector<Drawable*> *items;
	SDL_Texture *textureBg;

	Scene(SDL_Window *win, SDL_Renderer *render, b2World *world,std::vector<Drawable*> *items);

	virtual int execute();
	virtual ~Scene();
};

#endif /* SCENE_H_ */
