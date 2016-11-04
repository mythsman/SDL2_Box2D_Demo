/*
 * Ball.cpp
 *
 *  Created on: Oct 28, 2016
 *      Author: myths
 */

#include"Environment.h"
#include"Ball.h"
Ball::Ball(b2World *w, SDL_Renderer *r, double posx, double posy,
		double radius) {
	this->world = w;
	this->render = r;
	this->radius = radius;
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(posx, posy);
	this->body = world->CreateBody(&bodyDef);
	b2CircleShape dynamicCircle;
	dynamicCircle.m_radius = radius;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicCircle;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixture = this->body->CreateFixture(&fixtureDef);

}

void Ball::draw() {
	b2Vec2 position = body->GetPosition();
	filledCircleColor(render, position.x * 100, position.y * 100, radius * 100,
			0xff0000ff);
}

bool Ball::intersect(Ball *next) {
	b2Vec2 position1 = body->GetPosition();
	b2Vec2 position2 = next->body->GetPosition();
	double dist = hypot(position1.x - position2.x, position1.y - position2.y);
	if (dist < radius + next->radius) {
		return true;
	}
	return false;
}
Ball::~Ball() {

}
