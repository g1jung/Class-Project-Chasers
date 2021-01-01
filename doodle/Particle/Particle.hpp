/******************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Particle.hpp
Author
- Doyoung Lee doyoung413@gmail.com
Creation Date: 2020.08.06

Header file for particle
******************************************************************************/
#pragma once
#include <doodle/doodle.hpp>
#include <doodle/drawing.hpp>
#include <doodle/environment.hpp>
using namespace doodle;

class Particle
{
public:
    Particle() = default;
    Particle(double positionX, double positionY, double speedX, double speedY, double lifeTime);

    void Draw();
    bool inUse() const { return lifeTime > 0; }

    double xSpeed = 0;
    double ySpeed = 0;

private:
    double x        = 0;
    double y        = 0;
    double lifeTime = 0;
};