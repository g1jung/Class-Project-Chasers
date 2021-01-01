/******************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   ParticleSystem.cpp
Project Name: doodle
Course Name: CS225
Term: Summer 2020
Author
- Doyoung Lee doyoung413@gmail.com
Creation Date: 2020.08.06

Source file for particle system
******************************************************************************/
#include "ParticleSystem.hpp"

ParticleSystem::ParticleSystem(double positionX, double positionY, double speedX, double speedY, double lifeTime,
                               int particleAmount)
{
    totalParticles = particleAmount;
    particles      = new Particle[totalParticles];
    for (int i = 0; i < totalParticles; i++) // loop for generate particle
    {
        double xVel  = speedX + rand() % 20 - rand() % 20;
        double yVel  = speedY + rand() % 20 - rand() % 20;
        particles[i] = Particle(positionX, positionY, xVel, yVel, lifeTime);
    }
}

ParticleSystem::~ParticleSystem() { delete[] particles; }

ParticleSystem::ParticleSystem(const ParticleSystem& rhs)
    : particles(new Particle[rhs.totalParticles]), totalParticles(rhs.totalParticles)
{
    std::copy(&rhs.particles[0], &rhs.particles[rhs.totalParticles], &particles[0]);
}

ParticleSystem::ParticleSystem(ParticleSystem&& rhs) noexcept
    : particles{(rhs.particles)}, totalParticles(rhs.totalParticles)
{
    rhs.particles = nullptr;
}

ParticleSystem& ParticleSystem::operator=(const ParticleSystem& rhs)
{
    delete[] particles;
    this->particles = new Particle[rhs.totalParticles];
    std::copy(&rhs.particles[0], &rhs.particles[rhs.totalParticles], &particles[0]);
    this->totalParticles = rhs.totalParticles;

    return *this;
}

ParticleSystem& ParticleSystem::operator=(ParticleSystem&& rhs) noexcept
{
    delete[] particles;
    this->particles      = rhs.particles;
    this->totalParticles = rhs.totalParticles;
    rhs.particles        = nullptr;

    return *this;
}

void ParticleSystem::Draw()
{
    for (int i = 0; i < totalParticles; i++)
    {
        if (particles[i].inUse() == true) // check particle life time is still left
        {
            particles[i].Draw();
        }
    }
}