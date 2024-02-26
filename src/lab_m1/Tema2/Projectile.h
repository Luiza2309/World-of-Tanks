#pragma once

#include "components/simple_scene.h"

class Projectile
{
public:
    Projectile();
    Projectile(glm::vec3 position, glm::vec3 forward, int time);
    ~Projectile();

    glm::vec3 getPosition();
    void setPosition(glm::vec3 position);

    glm::vec3 getForward();
    void setForward(glm::vec3 value);

    int getTime();
    void setTime(int value);

private:
    glm::vec3 position;
    glm::vec3 forward;
    int time;
    //float moveProjectile;

protected:
};