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
#include"Rope.h"

#define WIDTH 720
#define HEIGHT 540

SDL_Window *window;
SDL_Renderer *render;
SDL_Texture *textureBg, *bodyTexture;
SDL_Surface *surface;
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

	surface = SDL_GetWindowSurface(window);
	SDL_Rect r = { 0, 0, WIDTH, HEIGHT };
	SDL_FillRect(surface, &r, SDL_MapRGB(surface->format, 255, 255, 255));
	textureBg = SDL_CreateTextureFromSurface(render, surface);
	SDL_FreeSurface(surface);

	SDL_RenderClear(render);
	SDL_RenderCopy(render, textureBg, NULL, NULL);
	SDL_RenderPresent(render);
	surface = SDL_GetWindowSurface(window);
	SDL_FillRect(surface, &r, SDL_MapRGB(surface->format, 120, 120, 120));
	bodyTexture = SDL_CreateTextureFromSurface(render, surface);
	return 0;
}

b2Vec2 gravity(0.0f, 10.0f);
b2World world(gravity);

void addBorder() {
	b2PolygonShape groundBox;
	double delta = 0.1;
	b2BodyDef leftBorderDef;
	leftBorderDef.position.Set(-delta, HEIGHT / 200.0);
	b2Body* leftBorderBody = world.CreateBody(&leftBorderDef);
	groundBox.SetAsBox(delta, HEIGHT / 200.0);
	leftBorderBody->CreateFixture(&groundBox, 0.0f);

	b2BodyDef rightBorderDef;
	rightBorderDef.position.Set(WIDTH / 100.0 + delta, HEIGHT / 200.0);
	b2Body* rightBorderBody = world.CreateBody(&rightBorderDef);
	groundBox.SetAsBox(delta, HEIGHT / 200.0);
	rightBorderBody->CreateFixture(&groundBox, 0.0f);

	b2BodyDef upBorderDef;
	upBorderDef.position.Set(WIDTH / 200.0, -delta);
	b2Body* upBorderBody = world.CreateBody(&upBorderDef);
	groundBox.SetAsBox(WIDTH, delta);
	upBorderBody->CreateFixture(&groundBox, 0.0f);

	b2BodyDef downBorderDef;
	downBorderDef.position.Set(WIDTH / 200.0, HEIGHT / 100.0 + delta);
	b2Body* downBorderBody = world.CreateBody(&downBorderDef);
	groundBox.SetAsBox(WIDTH / 100.0, delta);
	downBorderBody->CreateFixture(&groundBox, 0.0f);
}

std::vector<Drawable*> items;
unsigned int timerStep(unsigned int interval, void *param) {
	float timeStep = 1.0f / 100.0f;
	int velocityIterations = 6;
	int positionIterations = 2;
	world.Step(timeStep, velocityIterations, positionIterations);
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
	if (initSDL() == 1)
		return 1;

	addBorder();
	Rope *rope = new Rope(&world, render, 2);
	items.push_back(rope);

	SDL_AddTimer(10, timerStep, NULL);
	SDL_AddTimer(20, timerPaint, NULL);

	bool quit = false;
	while (!quit) {
		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT: {
				quit = true;
				break;
			}
			case SDL_MOUSEBUTTONDOWN: {
				items.push_back(
						new Box(&world, render, e.button.x / 100.0,
								e.button.y / 100.0, 0.2, 0.2));
				break;
			}
			default: {
				break;
			}

			}
		}
	}
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(render);
	SDL_DestroyTexture(textureBg);
	SDL_Quit();
}
