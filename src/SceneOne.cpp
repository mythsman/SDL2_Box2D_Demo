/*
 * SceneOne.cpp
 *
 *  Created on: Oct 29, 2016
 *      Author: myths
 */

#include"SceneOne.h"
#include"Rope.h"
#include<SDL2/SDL2_gfxPrimitives.h>
#include<iostream>
#include<queue>
SceneOne::SceneOne(SDL_Window *win, SDL_Renderer *ren) :
		Scene(win, ren) {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	SDL_Surface *surface = SDL_GetWindowSurface(window);
	SDL_Rect rectBg = { 0, 0, w, h };
	SDL_FillRect(surface, &rectBg, SDL_MapRGB(surface->format, 255, 255, 255));
	textureBg = SDL_CreateTextureFromSurface(render, surface);
	SDL_FreeSurface(surface);

	world = new b2World(b2Vec2(0, 10));
	b2BodyDef groundBodyDef;
	groundBodyDef.position.SetZero();

	b2Body *groundBody = world->CreateBody(&groundBodyDef);
	b2EdgeShape groundBox;
	groundBox.Set(b2Vec2(0, 0), b2Vec2(w / PTM_RATIO, 0));
	groundBody->CreateFixture(&groundBox, 0);
	groundBox.Set(b2Vec2(0, 0), b2Vec2(0, h / PTM_RATIO));
	groundBody->CreateFixture(&groundBox, 0);
	groundBox.Set(b2Vec2(0, h / PTM_RATIO),
			b2Vec2(w / PTM_RATIO, h / PTM_RATIO));
	groundBody->CreateFixture(&groundBox, 0);
	groundBox.Set(b2Vec2(w / PTM_RATIO, h / PTM_RATIO),
			b2Vec2(w / PTM_RATIO, 0));
	groundBody->CreateFixture(&groundBox, 0);

}

SceneOne::~SceneOne() {
	delete world;
}
void SceneOne::step() {
	float timeStep = 1.0f / 100.0f;
	int velocityIterations = 6;
	int positionIterations = 2;
	world->Step(timeStep, velocityIterations, positionIterations);
}

void SceneOne::paint() {
	SDL_RenderClear(render);
	SDL_RenderCopy(render, textureBg, NULL, NULL);
	for (unsigned int i = 0; i < items.size(); i++) {
		items[i]->draw();
	}
	std::list<SDL_Point>::iterator it1 = mouseList.begin(), it2 =
			mouseList.begin();
	for (it2++; it2 != mouseList.end(); it1++, it2++) {
		thickLineColor(render, it1->x, it1->y, it2->x, it2->y, 5, 0xff00ff00);
	}
	SDL_RenderPresent(render);

}
unsigned int sceneOneStepCallBack(unsigned int interval, void *param) {
	SceneOne *sceneOne = (SceneOne*) param;
	sceneOne->step();
	return interval;
}
unsigned int sceneOnePaintCallBack(unsigned int interval, void *param) {
	SceneOne *sceneOne = (SceneOne*) param;
	sceneOne->paint();
	return interval;
}
int SceneOne::execute() {
	b2Filter filter;
	filter.categoryBits = 0x0000;

	int t1 = SDL_AddTimer(10, sceneOneStepCallBack, this);
	int t2 = SDL_AddTimer(20, sceneOnePaintCallBack, this);

	b2Vec2 startPos(3.6, 0.5);
	b2Vec2 endPos(3.6, 1.5);
	Rope *rope = new Rope(world, render, 1.0, startPos, endPos);
	items.push_back(rope);

	Ball *ball = new Ball(world, render, 3.6, 2, 0.06);
	ball->body->SetType(b2_staticBody);
	ball->fixture->SetFilterData(filter);
	items.push_back(ball);

	ball = new Ball(world, render, 3.6, 3, 0.06);
	ball->body->SetType(b2_staticBody);
	ball->fixture->SetFilterData(filter);
	items.push_back(ball);

	ball = new Ball(world, render, 3.6, 4, 0.06);
	ball->body->SetType(b2_staticBody);
	ball->fixture->SetFilterData(filter);
	items.push_back(ball);

	int signal;
	bool quit = false;
	bool mouseDown;
	while (!quit) {
		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT: {
				quit = true;
				signal = 0;
				break;
			}
			case SDL_MOUSEMOTION: {
				if (mouseDown) {
					if (mouseList.size() == 5) {
						mouseList.pop_front();
					}
					SDL_Point p;
					p.x = e.motion.x;
					p.y = e.motion.y;
					mouseList.push_back(p);

				}
				break;
			}
			case SDL_MOUSEBUTTONDOWN: {
				mouseDown = true;
				break;
			}
			case SDL_MOUSEBUTTONUP: {
				mouseList.clear();
				mouseDown = false;
				break;
			}
			default:
				break;
			}
		}
	}
	SDL_RenderClear(render);
	SDL_RemoveTimer(t1);
	SDL_RemoveTimer(t2);
	return signal;
}

