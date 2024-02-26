#include "Projectile.h"

Projectile::Projectile() {}

Projectile::Projectile(glm::vec3 position, glm::vec3 forward, int time) {
	this->position = position;
	this->forward = forward;
	this->time = time;
}

Projectile::~Projectile() {}

glm::vec3 Projectile::getPosition() {
	return position;
}

void Projectile::setPosition(glm::vec3 position) {
	this->position = position;
}

glm::vec3 Projectile::getForward() {
	return forward;
}

void Projectile::setForward(glm::vec3 value) {
	this->forward = value;
}

int Projectile::getTime() {
	return time;
}

void Projectile::setTime(int value) {
	this->time = value;
}