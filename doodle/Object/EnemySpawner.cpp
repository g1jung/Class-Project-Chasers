/******************************************************************************
Copyright(C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name : EnemySpawner.cpp
Project Name: doodle
Course Name: CS225
Term: Summer 2020
Author
- Doyoung Lee doyoung413@gmail.com
Creation Date : 2020.08.06

Source file for enemy spawner
******************************************************************************/
#include "EnemySpawner.hpp"
#include "Enemy.hpp"
#include "ObjectManager.hpp"

EnemySpawner::EnemySpawner(double positionX, double positionY, double speedX, double speedY, double width,
                           double height, DrawType drawType, ObjectManager* objectManagerPointer)
    : Object(positionX, positionY, speedX, speedY, width, height, drawType), objectManager(objectManagerPointer)
{
}

EnemySpawner::EnemySpawner(double positionX, double positionY, double speedX, double speedY, double width,
                           double height, const std::filesystem::path& imagePath, ObjectManager* objectManagerPointer)
    : Object(positionX, positionY, speedX, speedY, width, height, imagePath), objectManager(objectManagerPointer)
{
}

void EnemySpawner::Update()
{
    Object::Draw();
    delay -= DeltaTime;
    if (delay < 0.0) // if delay time is lower than 0
    {
        delay            = 5.0;
        int randomNumber = rand() % 2; // random value for spawn
        if (randomNumber == 0)         // spawn melee unit
        {
            Enemy& enemy = objectManager->AddObject<Enemy>(x, y, 3, 3, 48.0, 48.0, DrawType::RECTANGLE, objectManager);
            enemy.SetAttackType(EnemyType::MELEE);
        }
        else // spawn range unit
        {
            Enemy& enemy =
                objectManager->AddObject<Enemy>(x, y, 1.5, 1.5, 48.0, 48.0, DrawType::RECTANGLE, objectManager);
            enemy.SetAttackType(EnemyType::RANGE);
        }
    }
}
