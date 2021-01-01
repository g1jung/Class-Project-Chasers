/******************************************************************************
Copyright(C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name : EnemyBullet.hpp
Project Name: doodle
Course Name: CS225
Term: Summer 2020
Author
- Doyoung Lee doyoung413@gmail.com
Creation Date : 2020.07.30

Header file for enemy bullet
******************************************************************************/
#pragma once
#include "Object.hpp"
#include <doodle/doodle.hpp>
#include <doodle/drawing.hpp>
#include <doodle/environment.hpp>

class ObjectManager;

enum class BulletType
{
    NORMAL,
    SHOTGUN,
    MACHINEGUN
};

class EnemyBullet : public Object
{
public:
    EnemyBullet() = default;
    EnemyBullet(double positionX, double positionY, double speedX, double speedY, double width, double height,
                DrawType drawType, BulletType bulletType, ObjectManager* objectManagerPointer);
    EnemyBullet(double positionX, double positionY, double speedX, double speedY, double width, double height,
                const std::filesystem::path& imagePath, BulletType bulletType, ObjectManager* objectManagerPointer);
    void Update() override;
    void Draw() override;
    bool isCollideWithPlayer() noexcept;

private:
    BulletType     bulletType = BulletType::NORMAL;
    double         lifeTime   = 0.3;
    int            damage     = 5;
    ObjectManager* objectManager;
};