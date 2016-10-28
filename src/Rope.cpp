/*
 * Rope.cpp
 *
 *  Created on: Oct 28, 2016
 *      Author: myths
 */
#include"Drawable.h"
#include"Ball.h"
#include"Rope.h"
#include<SDL2/SDL.h>
#include<Box2D/Box2D.h>
#include<vector>

Rope::Rope(b2World *w, SDL_Renderer *r, double length, double width) {
	this->world = w;
	this->render = r;
	this->length = length;
	this->width = width;
	int count = 40;
	for (int i = 0; i < count; i++) {
		Box *box = new Box(w, r, 5.0, 2.0, width / 2, length / count/2);
		b2Filter filter;
		filter.categoryBits = 0x0000;
		box->fixture->SetFilterData(filter);
		boxes.push_back(box);
	}
	boxes[0]->body->SetType(b2_staticBody);
	Box *endBox = new Box(w, r, 5, 2, width / 2, length / count/2);
	b2RopeJointDef jointDef;
	jointDef.maxLength = length;
	jointDef.bodyA = boxes[boxes.size() - 1]->body;
	jointDef.bodyB = endBox->body;
	b2Vec2 vv(0, 0);
	jointDef.localAnchorA = vv;
	jointDef.localAnchorB = vv;
	world->CreateJoint(&jointDef);

	boxes.push_back(endBox);
	for (unsigned int i = 1; i < boxes.size(); i++) {
		/*
		 b2RopeJointDef jointDef;
		 jointDef.maxLength = width;
		 jointDef.bodyA = balls[i - 1]->body;
		 jointDef.bodyB = balls[i]->body;
		 b2Vec2 vv(0, 0);
		 jointDef.localAnchorA = vv;
		 jointDef.localAnchorB = vv;
		 world->CreateJoint(&jointDef);
		 */
		b2RevoluteJointDef jointDef;
		b2Vec2 left(5 , 2- length / count / 2+0.01);
		b2Vec2 right(5 , 2+ length / count / 2-0.01);
		if (i & 1)
			jointDef.Initialize(boxes[i - 1]->body, boxes[i]->body, left);
		else
			jointDef.Initialize(boxes[i - 1]->body, boxes[i]->body, right);

		world->CreateJoint(&jointDef);
	}
	/*
	 *
	 jointDef.maxLength = length;
	 jointDef.bodyA = balls[0]->body;
	 jointDef.bodyB = balls[balls.size() - 1]->body;
	 jointDef.localAnchorA = vv;
	 jointDef.localAnchorB = vv;
	 world->CreateJoint(&jointDef);
	 */
}

void Rope::draw() {
	for (unsigned int i = 0; i < boxes.size(); i++) {
		boxes[i]->draw();
	}
}
