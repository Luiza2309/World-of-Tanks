#include "Building.h"

Building::Building() {}

Building::Building(glm::vec3 position, glm::vec3 color, glm::vec3 scale) {
	this->position = position;
	this->color = color;
	this->scale = scale;
}

Building::~Building() {}

glm::vec3 Building::getPosition() {
	return position;
}

glm::vec3 Building::getColor() {
	return color;
}

glm::vec3 Building::getScale() {
	return scale;
}