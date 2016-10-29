/*
 * Scene.cpp
 *
 *  Created on: Oct 29, 2016
 *      Author: myths
 */

#include"Scene.h"
#include<SDL2/SDL.h>
#include<vector>
#include<Box2D/Box2D.h>
Scene::Scene(SDL_Window *win, SDL_Renderer *ren, b2World *wor,
		std::vector<Drawable*> *items) {
	this->window = win;
	this->render = ren;
	this->items = items;
	this->world = wor;
	SDL_Surface *surface = SDL_GetWindowSurface(window);
	int width, height;
	SDL_GetWindowSize(window, &width, &height);
	SDL_Rect r = { 0, 0, width, height };
	SDL_FillRect(surface, &r, SDL_MapRGB(surface->format, 255, 255, 255));
	textureBg = SDL_CreateTextureFromSurface(render, surface);
	SDL_FreeSurface(surface);

}
int Scene::execute() {
	return 0;
}
Scene::~Scene() {
}

