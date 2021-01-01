/******************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   ParticleSystem.hpp
Project Name: doodle
Course Name: CS225
Term: Summer 2020
Author
- Doyoung Lee doyoung413@gmail.com
Creation Date: 2020.08.06

Header file for particle system
******************************************************************************/
#pragma once
#include "Particle.hpp"
#include <doodle/doodle.hpp>
#include <doodle/drawing.hpp>
#include <doodle/environment.hpp>

using namespace doodle;

class ParticleSystem
{
public:
    ParticleSystem() = default;
    ParticleSystem(double positionX, double positionY, double speedX, double speedY, double lifeTime,
                   int particleAmount);
    ~ParticleSystem();

    ParticleSystem(const ParticleSystem& rhs);
    ParticleSystem(ParticleSystem&& rhs) noexcept;

    ParticleSystem& operator=(const ParticleSystem& rhs);
    ParticleSystem& operator=(ParticleSystem&& rhs) noexcept;

    void Draw();

private:
    Particle* particles;
    int       totalParticles;
};