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

Source file for item
******************************************************************************/
#include "Item.hpp"
#include "ObjectManager.hpp"

Item::Item(double positionX, double positionY, double speedX, double speedY, double width, double height,
           DrawType drawType, ItemType itemType, ObjectManager* objectManagerPointer)
    : Object(positionX, positionY, speedX, speedY, width, height, drawType), objectManager(objectManagerPointer)
{
    objectType     = ObjectType::ITEM;
    this->itemType = itemType;
}

Item::Item(double positionX, double positionY, double speedX, double speedY, double width, double height,
           const std::filesystem::path& imagePath, ItemType itemType, ObjectManager* objectManagerPointer)
    : Object(positionX, positionY, speedX, speedY, width, height, imagePath), objectManager(objectManagerPointer)
{
    objectType     = ObjectType::ITEM;
    this->itemType = itemType;
}

void Item::Update()
{
    Object::SetMinMax();

    Object::Draw();
    if (isCollideWithPlayer() == true)
    {
        objectManager->GetPlayer()->GetItem(itemType);
        objectManager->Destroy(id);
    }
}

bool Item::isCollideWithPlayer() noexcept // function that check if player got item
{
    Object& object = *objectManager->GetPlayer();
    if (&object != nullptr)
    {
        return !(maxX < object.GetMinX() || object.GetMaxX() < minX || maxY < object.GetMinY() ||
                 object.GetMaxY() < minY);
    }
    return false;
}
