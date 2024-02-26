#pragma once

#include <iostream>
#include <random>
#include <map>
#include <string>

#include "components/simple_scene.h"

enum class MovementState
{
    GoingForward,
    GoingBackward,
    InPlaceRotationLeft,
    InPlaceRotationRight
};

class Movement
{
public:
    Movement();
    ~Movement();

    MovementState getCurrentState();
    void setCurrentState(MovementState value);
    int GetRandomNumberInRange(const int minInclusive, const int maxInclusive);
    MovementState GetNextMovementState(const MovementState currentState);
    std::string GetMovementStateName(const MovementState state);

private:
    MovementState currentState;

protected:
};