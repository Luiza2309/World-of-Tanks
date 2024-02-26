#pragma once

#include "components/simple_scene.h"
#include "Movement.h"

class Tank
{
public:
    Tank();
    Tank(glm::vec3 colors, glm::vec3 position);
    Tank(glm::vec3 colors, glm::vec3 detailColors, glm::vec3 position);
    ~Tank();

    Movement* move;

    glm::vec3 getColors();
    void setColors(glm::vec3 value);

    glm::vec3 getDetailColors();
    void setDetailColors(glm::vec3 value);

    glm::vec3 getPosition();
    void setPosition(glm::vec3 value);

    int getLifes();
    void setLifes();

    float getAngle();
    void setAngle(float value);

    glm::vec3 getForward();
    void setForward(glm::vec3 value);

    glm::vec3 getRight();
    void setRight(glm::vec3 value);

    float getAngleTurret();
    void setAngleTurret(float value);

    glm::vec3 getTurretCenter();
    void setTurretCenter(glm::vec3 value);

    glm::vec3 getCannonCenter();
    void setCannonCenter(glm::vec3 value);

    glm::vec3 getCannonForward();
    void setCannonForward(glm::vec3 value);

    int getTimeToMove();
    void setTimeToMove(int value);

    uint64_t getTimeToShoot();
    void setTimeToShoot(uint64_t value);

    void moveW(float deltaTime);
    void moveS(float deltaTime);
    void moveA(float deltaTime);
    void moveD(float deltaTime);

private:
    glm::vec3 colors;
    glm::vec3 detailColors;
    glm::vec3 position;
    int lifes;
    float angle;
    glm::vec3 forward;
    glm::vec3 right;
    float angleTurret;
    glm::vec3 turretCenter;
    glm::vec3 cannonCenter;
    glm::vec3 cannonForward;
    int timeToMove;
    uint64_t timeToShoot;


protected:
};