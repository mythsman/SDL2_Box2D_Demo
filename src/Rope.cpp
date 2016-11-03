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

Rope::Rope(b2World *w, SDL_Renderer *r, double length, b2Vec2 startPos,
		Ball* endBall) {
	this->world = w;
	this->render = r;
	this->length = length;
	this->width = 0.05;
	this->startPos = startPos;
	this->endBall = endBall;
	this->endPos = endBall->body->GetPosition();
	int count = 20;

	Box *startBox = new Box(w, r, startPos.x, startPos.y, 0.02, 0.02);
	startBox->body->SetType(b2_staticBody);
	b2Filter filter;
	filter.categoryBits = 0x0000;
	startBox->fixture->SetFilterData(filter);
	boxes.push_back(startBox);
	for (int i = 0; i < count; i++) {
		Box *box = new Box(w, r, startPos.x + length / count / 2, startPos.y,
				length / count / 2, width / 2);
		box->fixture->SetFilterData(filter);
		boxes.push_back(box);
	}

	b2RevoluteJointDef jointDef;
	b2Vec2 left(startPos.x, startPos.y);
	b2Vec2 right(startPos.x + length / count, startPos.y);

	for (unsigned int i = 1; i < boxes.size(); i++) {
		if (i & 1)
			jointDef.Initialize(boxes[i - 1]->body, boxes[i]->body, left);
		else
			jointDef.Initialize(boxes[i - 1]->body, boxes[i]->body, right);

		world->CreateJoint(&jointDef);
	}
	if (count & 1) {
		endBall->body->SetTransform(right, 0);
		jointDef.Initialize(boxes[boxes.size() - 1]->body, endBall->body,
				right);
	} else {
		endBall->body->SetTransform(left, 0);
		jointDef.Initialize(boxes[boxes.size() - 1]->body, endBall->body, left);
	}
	world->CreateJoint(&jointDef);

//	//Add rope joint
//	b2RopeJointDef ropeJointDef;
//	ropeJointDef.bodyA = boxes[0]->body;
//	ropeJointDef.bodyB = endBall->body;
//	ropeJointDef.maxLength = length;
//	b2Vec2 zero(0, 0);
//	ropeJointDef.localAnchorA = zero;
//	ropeJointDef.localAnchorB = zero;
//	world->CreateJoint(&ropeJointDef);

//Move to required location
	double deltaX = (endPos.x - startPos.x) / count;
	double deltaY = (endPos.y - startPos.y) / count;
	for (unsigned int i = 1; i < boxes.size(); i++) {
		b2Vec2 vec(startPos.x + deltaX * i - deltaX / 2,
				startPos.y + deltaY * i - deltaY / 2);
		boxes[i]->body->SetTransform(vec, 0);
	}
	endBall->body->SetTransform(endPos, 0);
}

void Rope::draw() {
	for (unsigned int i = 0; i < boxes.size(); i++) {
		boxes[i]->draw();
	}
	endBall->draw();
}
void Rope::cut(std::list<SDL_Point> points) {

}

Rope::~Rope() {
	for (unsigned int i = 0; i < boxes.size(); i++) {
		delete boxes[i];
	}
}
