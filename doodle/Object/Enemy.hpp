/******************************************************************************
Copyright(C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name : Enemy.hpp
Project Name: doodle
Course Name: CS225
Term: Summer 2020
Author
- Doyoung Lee doyoung413@gmail.com
Creation Date : 2020.07.30

Header file for enemy
******************************************************************************/
#pragma once
#include "Object.hpp"
#include <doodle/doodle.hpp>
#include <doodle/drawing.hpp>
#include <doodle/environment.hpp>

class ObjectManager;

enum class EnemyType
{
    MELEE,
    RANGE
};

class Enemy : public Object
{
public:
    Enemy() = default;
    Enemy(double positionX, double positionY, double speedX, double speedY, double width, double height,
          DrawType drawType, ObjectManager* objectManagerPointer);
    Enemy(double positionX, double positionY, double speedX, double speedY, double width, double height,
          const std::filesystem::path& imagePath, ObjectManager* objectManagerPointer);

    void Update() override;
    void Draw() override;
    bool isObjectInAttackRange(Object& object) noexcept;
    void SetAttackRange(double value) { attackRange = value; }
    void SetAttackType(EnemyType type);

    void SetHp(int value) { hp = value; }
    int  GetHp() { return hp; }

private:
    double         attackDelay   = 1.0;
    double         attackRange   = 0;
    int            meleeDamage   = 7;
    ObjectManager* objectManager = nullptr;
    EnemyType      enemyType     = EnemyType::MELEE;

    int hp = 10;
};