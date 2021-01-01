/******************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   ObjectManager.cpp
Project Name: doodle
Course Name: CS225
Term: Summer 2020
Author
    - Doyoung Lee doyoung413@gmail.com
Creation Date: 2020.07.22

    Source file for object manager
******************************************************************************/
#include "ObjectManager.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"

void ObjectManager::Update()
{
    std::for_each(objectMap.begin(), objectMap.end(), [&](auto& obj) { obj.second->Update(); });
    // Delete object from map if it is in the list to be deleted.
    std::for_each(objectsToBeDeleted.begin(), objectsToBeDeleted.end(), [&](int id) { objectMap.erase(id); });
    objectsToBeDeleted.clear();
    CollideObjects();
}

void ObjectManager::Destroy(int id) { objectsToBeDeleted.push_back(id); }

void ObjectManager::DestroyAllObjects()
{
    lastObjectID = 0;
    objectMap.clear();
}

void ObjectManager::CollideObjects()
{
    for (const auto& object : objectMap)
    {
        for (const auto& object1 : objectMap)
        {
            if (object.second.get()->GetObjectType() == ObjectType::BULLET) // bullet's collision
            {
                if (object1.second.get()->GetObjectType() == ObjectType::BLOCK &&
                    object.second.get()->isCollideWithObject(*object1.second.get()) == true)
                {
                    objectsToBeDeleted.push_back(object.second.get()->GetId());
                }
                else if (object1.second.get()->GetObjectType() == ObjectType::ENEMY &&
                         object.second.get()->isCollideWithObject(*object1.second.get()) == true)
                {
                    objectsToBeDeleted.push_back(object.second.get()->GetId());
                    Enemy*  enemy  = static_cast<Enemy*>(object1.second.get());
                    Bullet* bullet = static_cast<Bullet*>(object.second.get());

                    enemy->SetHp(enemy->GetHp() - bullet->GetDamage());
                }
            }
            else if (object.second.get()->GetObjectType() == ObjectType::ENEMYBULLET) // enemy bullet's collision
            {
                if (object1.second.get()->GetObjectType() == ObjectType::BLOCK &&
                    object.second.get()->isCollideWithObject(*object1.second.get()) == true)
                {
                    objectsToBeDeleted.push_back(object.second.get()->GetId());
                }
            }
        }
    }
}
