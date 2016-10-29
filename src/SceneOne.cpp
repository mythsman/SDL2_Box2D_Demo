/*
 * SceneOne.cpp
 *
 *  Created on: Oct 29, 2016
 *      Author: myths
 */

#include"SceneOne.h"
#include"Rope.h"
#include<iostream>
SceneOne::SceneOne(SDL_Window *win, SDL_Renderer *ren, b2World *wor,
		std::vector<Drawable*>*items) :
		Scene(win, ren, wor, items) {
}

int SceneOne::execute() {
	b2Vec2 startPos(3.6, 0.5);
	b2Vec2 endPos(3.6, 1.5);
	Rope *rope = new Rope(world, render, 1.0, startPos, endPos);
	items->push_back(rope);
	bool quit = false;
	Ball *ball = new Ball(world, render, 3.6, 2, 0.06);
	ball->body->SetType(b2_staticBody);
	items->push_back(ball);
	ball = new Ball(world, render, 3.6, 3, 0.06);
	ball->body->SetType(b2_staticBody);
	items->push_back(ball);
	ball = new Ball(world, render, 3.6, 4, 0.06);
	ball->body->SetType(b2_staticBody);
	items->push_back(ball);
	int signal;
	while (!quit) {
		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT: {
				quit = true;
				signal = 0;
				break;
			}
			case SDL_MOUSEBUTTONDOWN: {
				items->push_back(
						new Box(world, render, e.button.x / 100.0,
								e.button.y / 100.0, 0.2, 0.2));
				break;
			}
			default: {
				break;
			}

			}
		}
	}
	SDL_RenderClear(render);
	items->clear();
	return signal;
}

