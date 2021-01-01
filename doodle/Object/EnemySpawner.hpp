/******************************************************************************
Copyright(C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name : EnemySpawner.hpp
Project Name: doodle
Course Name: CS225
Term: Summer 2020
Author
- Doyoung Lee doyoung413@gmail.com
Creation Date : 2020.08.06

Header file for enemy spawner
******************************************************************************/
#pragma once
#include "Object.hpp"
#include <doodle/doodle.hpp>
#include <doodle/drawing.hpp>
#include <doodle/environment.hpp>

class ObjectManager;

class EnemySpawner : public Object
{
public:
    EnemySpawner() = default;
    EnemySpawner(double positionX, double positionY, double speedX, double speedY, double width, double height,
                 DrawType drawType, ObjectManager* objectManagerPointer);
    EnemySpawner(double positionX, double positionY, double speedX, double speedY, double width, double height,
                 const std::filesystem::path& imagePath, ObjectManager* objectManagerPointer);
    void Update() override;

private:
    double         delay         = 5.0;
    ObjectManager* objectManager = nullptr;
};