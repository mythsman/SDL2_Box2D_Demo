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

#include"SceneOne.h"

//b2World *world;
//std::vector<Drawable*> items;

//void initWorld() {
//	b2Vec2 gravity(0.0f, 10.0f);
//	world = new b2World(gravity);
//	b2PolygonShape groundBox;
//	double delta = 0.1;
//	b2BodyDef leftBorderDef;
//	leftBorderDef.position.Set(-delta, HEIGHT / 200.0);
//	b2Body* leftBorderBody = world->CreateBody(&leftBorderDef);
//	groundBox.SetAsBox(delta, HEIGHT / 200.0);
//	leftBorderBody->CreateFixture(&groundBox, 0.0f);
//
//	b2BodyDef rightBorderDef;
//	rightBorderDef.position.Set(WIDTH / 100.0 + delta, HEIGHT / 200.0);
//	b2Body* rightBorderBody = world->CreateBody(&rightBorderDef);
//	groundBox.SetAsBox(delta, HEIGHT / 200.0);
//	rightBorderBody->CreateFixture(&groundBox, 0.0f);
//
//	b2BodyDef upBorderDef;
//	upBorderDef.position.Set(WIDTH / 200.0, -delta);
//	b2Body* upBorderBody = world->CreateBody(&upBorderDef);
//	groundBox.SetAsBox(WIDTH, delta);
//	upBorderBody->CreateFixture(&groundBox, 0.0f);
//
//	b2BodyDef downBorderDef;
//	downBorderDef.position.Set(WIDTH / 200.0, HEIGHT / 100.0 + delta);
//	b2Body* downBorderBody = world->CreateBody(&downBorderDef);
//	groundBox.SetAsBox(WIDTH / 100.0, delta);
//	downBorderBody->CreateFixture(&groundBox, 0.0f);
//}

//unsigned int timerStep(unsigned int interval, void *param) {
//	if (param != NULL) {
//		Scene *scene = (Scene *) param;
//		scene->step();
//	}

//	return interval;
//}
//
//unsigned int timerPaint(unsigned int interval, void *param) {
//	if (param != NULL) {
//		Scene *scene = (Scene *) param;
//		scene->paint();
//	}
//	SDL_RenderClear(render);
//	SDL_RenderCopy(render, textureBg, NULL, NULL);
//	for (unsigned int i = 0; i < items.size(); i++) {
//		items[i]->draw();
//	}
//	SDL_RenderPresent(render);
//	return interval;
//}

#define WIDTH 720
#define HEIGHT 540

SDL_Window *window;
SDL_Renderer *render;
SDL_Texture *textureBg, *textureBtn1, *textureBtn2, *textureBtn3;
SDL_Rect rectBg, rectBtn1, rectBtn2, rectBtn3;

int getPos(int x, int y) {
	if (x >= rectBtn1.x && x <= rectBtn1.x + rectBtn1.w && y >= rectBtn1.y
			&& y <= rectBtn1.y + rectBtn1.h) {
		return 1;
	} else if (x >= rectBtn2.x && x <= rectBtn2.x + rectBtn2.w
			&& y >= rectBtn2.y && y <= rectBtn2.y + rectBtn2.h) {
		return 2;
	} else if (x >= rectBtn3.x && x <= rectBtn3.x + rectBtn3.w
			&& y >= rectBtn3.y && y <= rectBtn3.y + rectBtn3.h) {
		return 3;
	}
	return 0;
}
void paint() {
	SDL_RenderClear(render);
	SDL_RenderCopy(render, textureBg, NULL, &rectBg);
	SDL_RenderCopy(render, textureBtn1, NULL, &rectBtn1);
	SDL_RenderCopy(render, textureBtn2, NULL, &rectBtn2);
	SDL_RenderCopy(render, textureBtn3, NULL, &rectBtn3);
	SDL_RenderPresent(render);
}
int main() {

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
	rectBg = {0, 0, WIDTH, HEIGHT};
	SDL_FillRect(surface, &rectBg, SDL_MapRGB(surface->format, 111, 111, 111));
	textureBg = SDL_CreateTextureFromSurface(render, surface);
	SDL_FillRect(surface, &rectBg, SDL_MapRGB(surface->format, 255, 255, 255));
	textureBtn1 = SDL_CreateTextureFromSurface(render, surface);
	SDL_FillRect(surface, &rectBg, SDL_MapRGB(surface->format, 255, 255, 255));
	textureBtn2 = SDL_CreateTextureFromSurface(render, surface);
	SDL_FillRect(surface, &rectBg, SDL_MapRGB(surface->format, 255, 255, 255));
	textureBtn3 = SDL_CreateTextureFromSurface(render, surface);
	SDL_FreeSurface(surface);
	rectBtn1= {WIDTH/5*2,HEIGHT/7,WIDTH/5,HEIGHT/7};
	rectBtn2= {WIDTH/5*2,HEIGHT/7*3,WIDTH/5,HEIGHT/7};
	rectBtn3= {WIDTH/5*2,HEIGHT/7*5,WIDTH/5,HEIGHT/7};

	bool quit = false;
	int signal = -1;
	while (!quit) {
		paint();
		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT: {
				quit = true;
				break;
			}
			case SDL_MOUSEBUTTONDOWN: {
				int btn = getPos(e.button.x, e.button.y);
				if (btn == 1) {
					SceneOne sceneOne(window, render);
					signal = sceneOne.execute();
				}
			}
			default: {
				break;
			}

			}
		}
		if (signal == 0)
			quit = true;
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(render);
	SDL_DestroyTexture(textureBg);
	SDL_DestroyTexture(textureBtn1);
	SDL_DestroyTexture(textureBtn2);
	SDL_DestroyTexture(textureBtn3);
	SDL_Quit();
}
