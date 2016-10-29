/*
 * main.cpp
 *
 *  Created on: Oct 26, 2016
 *      Author: myths
 */

#include<iostream>
#include<vector>
#include<cmath>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL2_gfxPrimitives.h>
#include<Box2D/Box2D.h>
#include"Box.h"
#include"Ball.h"
#include"Scene.h"
#include"Rope.h"
#include"SceneOne.h"

#define WIDTH 720
#define HEIGHT 540

SDL_Window *window;
SDL_Renderer *render;
SDL_Texture *textureBg;

b2World *world;
std::vector<Drawable*> items;

int initSDL() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Title", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	if (render == NULL) {
		printf("Could not create render: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Surface *surface = SDL_GetWindowSurface(window);
	SDL_Rect r = { 0, 0, WIDTH, HEIGHT };
	SDL_FillRect(surface, &r, SDL_MapRGB(surface->format, 255, 255, 255));
	textureBg = SDL_CreateTextureFromSurface(render, surface);
	SDL_FreeSurface(surface);

	SDL_RenderClear(render);
	SDL_RenderCopy(render, textureBg, NULL, NULL);
	SDL_RenderPresent(render);

	return 0;
}

void initWorld() {
	b2Vec2 gravity(0.0f, 10.0f);
	world = new b2World(gravity);
	b2PolygonShape groundBox;
	double delta = 0.1;
	b2BodyDef leftBorderDef;
	leftBorderDef.position.Set(-delta, HEIGHT / 200.0);
	b2Body* leftBorderBody = world->CreateBody(&leftBorderDef);
	groundBox.SetAsBox(delta, HEIGHT / 200.0);
	leftBorderBody->CreateFixture(&groundBox, 0.0f);

	b2BodyDef rightBorderDef;
	rightBorderDef.position.Set(WIDTH / 100.0 + delta, HEIGHT / 200.0);
	b2Body* rightBorderBody = world->CreateBody(&rightBorderDef);
	groundBox.SetAsBox(delta, HEIGHT / 200.0);
	rightBorderBody->CreateFixture(&groundBox, 0.0f);

	b2BodyDef upBorderDef;
	upBorderDef.position.Set(WIDTH / 200.0, -delta);
	b2Body* upBorderBody = world->CreateBody(&upBorderDef);
	groundBox.SetAsBox(WIDTH, delta);
	upBorderBody->CreateFixture(&groundBox, 0.0f);

	b2BodyDef downBorderDef;
	downBorderDef.position.Set(WIDTH / 200.0, HEIGHT / 100.0 + delta);
	b2Body* downBorderBody = world->CreateBody(&downBorderDef);
	groundBox.SetAsBox(WIDTH / 100.0, delta);
	downBorderBody->CreateFixture(&groundBox, 0.0f);
}

unsigned int timerStep(unsigned int interval, void *param) {
	float timeStep = 1.0f / 100.0f;
	int velocityIterations = 6;
	int positionIterations = 2;
	world->Step(timeStep, velocityIterations, positionIterations);
	return interval;
}

unsigned int timerPaint(unsigned int interval, void *param) {

	SDL_RenderClear(render);
	SDL_RenderCopy(render, textureBg, NULL, NULL);
	for (unsigned int i = 0; i < items.size(); i++) {
		items[i]->draw();
	}
	SDL_RenderPresent(render);
	return interval;
}
int main() {
	initSDL();
	initWorld();

	SDL_AddTimer(10, timerStep, NULL);
	SDL_AddTimer(20, timerPaint, NULL);

	bool quit = false;
	int signal = -1;
	while (!quit) {
		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT: {
				quit = true;
				break;
			}
			case SDL_MOUSEBUTTONDOWN: {
				break;
			}
			case SDL_KEYDOWN: {
				SceneOne sceneOne(window, render, world, &items);
				signal = sceneOne.execute();
				initWorld();
				break;
			}
			default: {
				break;
			}

			}
		}
		switch (signal) {
		case 0:
			quit = true;
			break;
		default:
			break;
		}
	}
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(render);
	SDL_DestroyTexture(textureBg);
	SDL_Quit();
}
