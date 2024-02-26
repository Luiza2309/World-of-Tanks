#pragma once

#include "components/simple_scene.h"

class Building
{
public:
    Building();
    Building(glm::vec3 position, glm::vec3 color, glm::vec3 scale);
    ~Building();

    glm::vec3 getPosition();
    glm::vec3 getColor();
    glm::vec3 getScale();

private:
    glm::vec3 position;
    glm::vec3 color;
    glm::vec3 scale;

protected:
};