#include "Body.h"

Body::Body(Polygon *shape_, unsigned int x, unsigned int y)
	: shape(shape_->Clone())
{
	shape->body = this;
	position = Vector2f((float)x, (float)y);
	velocity = Vector2f(0, 0);
	angularVelocity = 0;
	torque = 0;
	orient = random(-PI, PI);
	force = Vector2f(0, 0);
	staticFriction = 0.5f;
	dynamicFriction = 0.3f;
	restitution = 0.2f;
	shape->initialize();
}

void Body::SetOrient(float radians) {
	orient = radians;
	shape->SetOrient(radians);
}