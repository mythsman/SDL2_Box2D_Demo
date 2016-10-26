/*
 * main.cpp
 *
 *  Created on: Oct 26, 2016
 *      Author: myths
 */

#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include<Box2D/Box2D.h>

#define WIDTH 720
#define HEIGHT 540
const double delta = 10.0;

SDL_Window *window;
SDL_Renderer *render;
SDL_Texture *texture, *bodyTexture;
SDL_Surface *surface;

int initSDL() {
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Title", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
	if (window == NULL) {
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	if (render == NULL) {
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	texture = IMG_LoadTexture(render, "resources/a.jpg");
	if (texture == NULL) {
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	SDL_RenderClear(render);
	SDL_RenderCopy(render, texture, NULL, NULL);
	SDL_RenderPresent(render);
	surface = SDL_GetWindowSurface(window);
	SDL_Rect r = { 0, 0, WIDTH, HEIGHT };
	SDL_FillRect(surface, &r, SDL_MapRGB(surface->format, 120, 120, 120));
	bodyTexture = SDL_CreateTextureFromSurface(render, surface);
	return 0;
}

void drawRect(SDL_Rect *rect) {
	SDL_RenderClear(render);
	SDL_RenderCopy(render, texture, NULL, NULL);
	SDL_RenderCopyEx(render, bodyTexture, NULL, rect, 0, NULL, SDL_FLIP_NONE);
	SDL_RenderPresent(render);
}

b2Vec2 gravity(0.0f, 50.0f);
b2World world(gravity);

void addBorder() {
	b2PolygonShape groundBox;

	b2BodyDef leftBorderDef;
	leftBorderDef.position.Set(-delta, HEIGHT / 2.0);
	b2Body* leftBorderBody = world.CreateBody(&leftBorderDef);
	groundBox.SetAsBox(delta, HEIGHT / 2.0);
	leftBorderBody->CreateFixture(&groundBox, 0.0f);

	b2BodyDef rightBorderDef;
	rightBorderDef.position.Set(WIDTH + delta, HEIGHT / 2.0);
	b2Body* rightBorderBody = world.CreateBody(&rightBorderDef);
	groundBox.SetAsBox(delta, HEIGHT / 2.0);
	rightBorderBody->CreateFixture(&groundBox, 0.0f);

	b2BodyDef upBorderDef;
	upBorderDef.position.Set(WIDTH / 2.0, -delta);
	b2Body* upBorderBody = world.CreateBody(&upBorderDef);
	groundBox.SetAsBox(WIDTH, delta);
	upBorderBody->CreateFixture(&groundBox, 0.0f);

	b2BodyDef downBorderDef;
	downBorderDef.position.Set(WIDTH / 2.0, HEIGHT + delta);
	b2Body* downBorderBody = world.CreateBody(&downBorderDef);
	groundBox.SetAsBox(WIDTH, delta);
	downBorderBody->CreateFixture(&groundBox, 0.0f);
}

float32 timeStep = 1.0f / 100.0f;
int32 velocityIterations = 6;
int32 positionIterations = 2;
b2Body* body;
double bodySize = 30;

Uint32 timer1(Uint32 interval, void *param) {
	world.Step(timeStep, velocityIterations, positionIterations);
	return interval;
}

Uint32 timer2(Uint32 interval, void *param) {
	b2Vec2 position = body->GetPosition();
	float32 angle = body->GetAngle();
	printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
	SDL_Rect r = { (int) (position.x - bodySize), (int) (position.y - bodySize),
			int(bodySize * 2), int(bodySize * 2) };
	drawRect(&r);
	return interval;
}
int main() {
	if (initSDL() == 1)
		return 1;

	addBorder();

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(WIDTH / 2, bodySize);
	body = world.CreateBody(&bodyDef);
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(bodySize, bodySize);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);

	SDL_AddTimer(10, timer1, NULL);
	SDL_AddTimer(20, timer2, NULL);
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
	SDL_DestroyTexture(texture);
	SDL_Quit();
}
