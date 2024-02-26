#include "Tank.h"

Tank::Tank() {}

Tank::Tank(glm::vec3 colors, glm::vec3 detailColors, glm::vec3 position) {
    this->move = new Movement();
    this->colors = colors;
    this->detailColors = detailColors;
    this->position = position;
    this->lifes = 3;
    this->angle = RADIANS(0);
    this->angleTurret = RADIANS(0);
    this->forward = glm::vec3(0, 0, 1);
    this->right = glm::vec3(1, 0, 0);
    this->turretCenter = glm::vec3(0.04032, 2.1319, -0.57159);
    this->cannonCenter = glm::vec3(-0.013699, -0.1367, 4.08859);
    this->cannonForward = glm::vec3(0, 0, 1);
    this->timeToShoot = 0;
}

Tank::~Tank() {}

void Tank::moveW(float deltaTime) {
    glm::vec3 dir = glm::normalize(glm::vec3(forward.x, 0, forward.z));
    position += dir * (deltaTime * 4);
}

void Tank::moveS(float deltaTime) {
    glm::vec3 dir = glm::normalize(glm::vec3(forward.x, 0, forward.z));
    position -= dir * (deltaTime * 4);
}

void Tank::moveA(float deltaTime) {
    angle += RADIANS(1);
    forward = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1), RADIANS(1), glm::vec3(0, 1, 0)) * glm::vec4(forward, 1)));
    cannonForward = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1), RADIANS(1), glm::vec3(0, 1, 0)) * glm::vec4(cannonForward, 1)));
    cannonCenter = glm::vec3(glm::rotate(glm::mat4(1), RADIANS(1), glm::vec3(0, 1, 0)) * glm::vec4(cannonCenter, 1));
}

void Tank::moveD(float deltaTime) {
    angle -= RADIANS(1);
    forward = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1), -RADIANS(1), glm::vec3(0, 1, 0)) * glm::vec4(forward, 1)));
    cannonForward = glm::normalize(glm::vec3(glm::rotate(glm::mat4(1), -RADIANS(1), glm::vec3(0, 1, 0)) * glm::vec4(cannonForward, 1)));
    cannonCenter = glm::vec3(glm::rotate(glm::mat4(1), -RADIANS(1), glm::vec3(0, 1, 0)) * glm::vec4(cannonCenter, 1));
}

glm::vec3 Tank::getColors() {
    return colors;
}

void Tank::setColors(glm::vec3 value) {
    this->colors = value;
}

glm::vec3 Tank::getDetailColors() {
    return detailColors;
}

void Tank::setDetailColors(glm::vec3 value) {
    this->detailColors = value;
}

glm::vec3 Tank::getPosition() {
	return position;
}

void Tank::setPosition(glm::vec3 value) {
	this->position = value;
}

int Tank::getLifes() {
	return lifes;
}

void Tank::setLifes() {
	this->lifes--;
}

float Tank::getAngle() {
    return angle;
}

void Tank::setAngle(float value) {
    angle = value;
}

glm::vec3 Tank::getForward() {
    return forward;
}

void Tank::setForward(glm::vec3 value) {
    forward = value;
}

glm::vec3 Tank::getRight() {
    return right;
}

void Tank::setRight(glm::vec3 value) {
    right = value;
}

float Tank::getAngleTurret() {
    return angleTurret;
}

void Tank::setAngleTurret(float value) {
    angleTurret = value;
}

glm::vec3 Tank::getTurretCenter() {
    return turretCenter;
}

void Tank::setTurretCenter(glm::vec3 value) {
    turretCenter = value;
}
#include <iostream>
glm::vec3 Tank::getCannonCenter() {
    return cannonCenter;
}


void Tank::setCannonCenter(glm::vec3 value) {
    cannonCenter = value;
}

glm::vec3 Tank::getCannonForward() {
    return cannonForward;
}

void Tank::setCannonForward(glm::vec3 value) {
    cannonForward = value;
}

int Tank::getTimeToMove() {
    return timeToMove;
}

void Tank::setTimeToMove(int value) {
    timeToMove = value;
}

uint64_t Tank::getTimeToShoot() {
    return timeToShoot;
}

void Tank::setTimeToShoot(uint64_t value) {
    timeToShoot = value;
}