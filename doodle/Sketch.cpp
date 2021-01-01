/******************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Sketch.cpp
Project Name: doodle
Course Name: CS225
Term: Summer 2020
Author
    - jiwon.jung jjwon6218@gmail.com
Creation Date: 2020.07.20

    Source file for basic test
******************************************************************************/
#include "Sketch.h"
#include <doodle/angle.hpp>
#include <doodle/drawing.hpp>
#include <doodle/environment.hpp>
#include <doodle/input.hpp>
#include <doodle/random.hpp>
#include <doodle/window.hpp>
#include <iostream>
using namespace doodle;

[[noreturn]] void error(const std::string& s) { throw std::runtime_error(s); }

void Sketch::setup()
{
    balls = {{200.0, 80.0, 8.0, 9.0}};

    no_fill();
    set_outline_color(240, 230, 245);
    set_outline_width(7.0f);

    set_callback_key_pressed([this](KeyboardButtons b) { OnKeyPressed(b); });
    set_callback_key_released([this](KeyboardButtons b) { OnKeyReleased(b); });
    set_callback_mouse_pressed([this](MouseButtons m) { OnMousePressed(m); });
    set_callback_mouse_released([this](MouseButtons m) { OnMouseReleased(m); });

    objectManager.AddObject<Player>(0, 0, 5, 5, 48.0, 32.0, DrawType::RECTANGLE, &objectManager);
    objectManager.AddObject<Block>(0, 128, 0, 0, 128.0, 32.0, DrawType::ELLIPSE);
    objectManager.AddObject<Block>(0, -128, 0, 0, 128.0, 32.0, DrawType::ELLIPSE);
    objectManager.AddObject<Block>(128, 0, 0, 0, 32.0, 128.0, DrawType::ELLIPSE);
    objectManager.AddObject<Item>(360, 0, 0, 0, 32.0, 32.0, DrawType::RECTANGLE, ItemType::MEDKIT, &objectManager);
    objectManager.AddObject<Item>(360, 128, 0, 0, 32.0, 32.0, DrawType::RECTANGLE, ItemType::AMMO, &objectManager);
    objectManager.AddObject<Item>(360, 256, 0, 0, 32.0, 32.0, DrawType::RECTANGLE, ItemType::MEDKIT, &objectManager);
    objectManager.AddObject<Item>(-360, 0, 0, 0, 32.0, 32.0, DrawType::RECTANGLE, ItemType::MEDKIT, &objectManager);
    objectManager.AddObject<Item>(-360, 128, 0, 0, 32.0, 32.0, DrawType::RECTANGLE, ItemType::MEDKIT, &objectManager);
    objectManager.AddObject<EnemySpawner>(Width / 2.0 + 64.0, Height / 2.0 + 64.0, 0, 0, 48.0, 48.0,
                                          DrawType::RECTANGLE, &objectManager);
    objectManager.AddObject<EnemySpawner>(-Width / 2.0 - 64.0, Height / 2.0 + 64.0, 0, 0, 48.0, 48.0,
                                          DrawType::RECTANGLE, &objectManager);
    objectManager.AddObject<EnemySpawner>(Width / 2.0 + 64.0, -Height / 2.0 - 64.0, 0, 0, 48.0, 48.0,
                                          DrawType::RECTANGLE, &objectManager);
    objectManager.AddObject<EnemySpawner>(-Width / 2.0 - 64.0, -Height / 2.0 - 64.0, 0, 0, 48.0, 48.0,
                                          DrawType::RECTANGLE, &objectManager);
    particleSystem = ParticleSystem(0, 0, (static_cast<double>(rand() % 5) - static_cast<double>(rand() % 5)),
                                    (static_cast<double>(rand() % 5) - static_cast<double>(rand() % 5)), 2.0, 100);
}

void Sketch::draw()
{
    InputActivate();
    clear_background(0);
    for (auto& ball : balls)
    {
        DrawAndUpdateBall(ball);
    }
    objectManager.Update();

    particleSystem.Draw();
}


void Sketch::OnKeyPressed(KeyboardButtons button) noexcept
{
    if (button == KeyboardButtons::A)
        isLeftArrowOn = true;
    if (button == KeyboardButtons::D)
        isRightArrowOn = true;
    if (button == KeyboardButtons::W)
        isUpArrowOn = true;
    if (button == KeyboardButtons::S)
        isDownArrowOn = true;


    if (button == KeyboardButtons::_1)
    {
        objectManager.GetPlayer()->SetWeapon(WeaponType::NORMAL);
    }
    else if (button == KeyboardButtons::_2)
    {
        objectManager.GetPlayer()->SetWeapon(WeaponType::SHOTGUN);
    }
    else if (button == KeyboardButtons::_3)
    {
        objectManager.GetPlayer()->SetWeapon(WeaponType::MACHINEGUN);
    }
}

void Sketch::OnKeyReleased(KeyboardButtons button) noexcept
{
    if (button == KeyboardButtons::A)
    {
        isLeftArrowOn = false;
        objectManager.GetPlayer()->Move(Direction::NODIRECTION);
    }
    if (button == KeyboardButtons::D)
    {
        isRightArrowOn = false;
        objectManager.GetPlayer()->Move(Direction::NODIRECTION);
    }
    if (button == KeyboardButtons::W)
    {
        isUpArrowOn = false;
        objectManager.GetPlayer()->Move(Direction::NODIRECTION);
    }
    if (button == KeyboardButtons::S)
    {
        isDownArrowOn = false;
        objectManager.GetPlayer()->Move(Direction::NODIRECTION);
    }
    if (button == KeyboardButtons::Escape)
    {
        objectManager.DestroyAllObjects();
        close_window();
    }
}

void Sketch::OnMousePressed(MouseButtons button) noexcept
{
    if (button == MouseButtons::Left)
    {
        isLeftMouseOn = true;
    }
}

void Sketch::OnMouseReleased(MouseButtons button) noexcept
{
    if (button == MouseButtons::Left)
    {
        isLeftMouseOn = false;
    }
}

void Sketch::InputActivate(void)
{
    if (isLeftMouseOn == true)
        objectManager.GetPlayer()->GunShot();

    if (isLeftArrowOn == true)
        objectManager.GetPlayer()->Move(Direction::LEFT);
    if (isRightArrowOn == true)
        objectManager.GetPlayer()->Move(Direction::RIGHT);
    if (isUpArrowOn == true)
        objectManager.GetPlayer()->Move(Direction::UP);
    if (isDownArrowOn == true)
        objectManager.GetPlayer()->Move(Direction::DOWN);
}

void Sketch::DrawAndUpdateBall(Ball& ball)
{
    push_settings();
    draw_ellipse(ball.x, ball.y, RADIUS << 1);
    pop_settings();

    if (ball.y + RADIUS > Height || ball.y < RADIUS)
    {
        ball.ySpeed *= -1;
    }
    else if (ball.x + RADIUS > Width || ball.x < RADIUS)
    {
        ball.xSpeed *= -1;
    }
}
