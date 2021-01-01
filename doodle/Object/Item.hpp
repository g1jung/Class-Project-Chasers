/******************************************************************************
Copyright(C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name : Item.hpp
Project Name: doodle
Course Name: CS225
Term: Summer 2020
Author
- Doyoung Lee doyoung413@gmail.com
Creation Date : 2020.08.02

Header file for item
******************************************************************************/
#pragma once
#include "Object.hpp"
#include <doodle/doodle.hpp>
#include <doodle/drawing.hpp>
#include <doodle/environment.hpp>

class ObjectManager;

enum class ItemType
{
    NOTHING,
    MEDKIT,
    AMMO
};

class Item : public Object
{
public:
    Item() = default;
    Item(double positionX, double positionY, double speedX, double speedY, double width, double height,
         DrawType drawType, ItemType itemType, ObjectManager* objectManagerPointer);
    Item(double positionX, double positionY, double speedX, double speedY, double width, double height,
         const std::filesystem::path& imagePath, ItemType itemType, ObjectManager* objectManagerPointer);
    void Update() override;

    bool isCollideWithPlayer() noexcept;

private:
    ItemType       itemType = ItemType::NOTHING;
    ObjectManager* objectManager;
};