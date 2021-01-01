/******************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Sketch.h
Project Name: doodle
Course Name: CS225
Term: Summer 2020
Author
    - jiwon.jung jjwon6218@gmail.com
Creation Date: 2020.07.20

    Header file for basic test
******************************************************************************/
#pragma once
#include "Object/Block.hpp"
#include "Object/Enemy.hpp"
#include "Object/EnemySpawner.hpp"
#include "Object/Item.hpp"
#include "Object/Object.hpp"
#include "Object/ObjectManager.hpp"
#include "Object/Player.hpp"
#include "Particle/ParticleSystem.hpp"
#include <SFML/Audio.hpp>
#include <vector>

class Sketch
{
public:
    struct Ball
    {
        double x{0}, y{0}, xSpeed{0}, ySpeed{0};
    };

public:
    void setup();
    void draw();

    void OnKeyPressed(KeyboardButtons button) noexcept;
    void OnKeyReleased(KeyboardButtons button) noexcept;
    void OnMousePressed(MouseButtons button) noexcept;
    void OnMouseReleased(MouseButtons button) noexcept;

    void InputActivate(void);

private:
    constexpr static int RADIUS{30};
    std::vector<Ball>    balls;

    bool isLeftArrowOn  = false;
    bool isRightArrowOn = false;
    bool isUpArrowOn    = false;
    bool isDownArrowOn  = false;
    bool isLeftMouseOn  = false;

private:
    void           DrawAndUpdateBall(Ball& ball);
    ObjectManager  objectManager;
    ParticleSystem particleSystem;
    int            ParticleAmount = 0;
};
