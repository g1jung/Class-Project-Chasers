/******************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Particle.cpp
Author
- Doyoung Lee doyoung413@gmail.com
Creation Date: 2020.08.06

Source file for particle
******************************************************************************/
#include "Particle.hpp"

Particle::Particle(double positionX, double positionY, double speedX, double speedY, double lifeTime)
{
    this->x        = positionX;
    this->y        = positionY;
    xSpeed         = speedX;
    ySpeed         = speedY;
    this->lifeTime = lifeTime;
}

void Particle::Draw()
{
    x += xSpeed;
    y += ySpeed;
    lifeTime -= DeltaTime;

    push_settings();
    draw_ellipse(x, y, 16, 16);
    pop_settings();
}
