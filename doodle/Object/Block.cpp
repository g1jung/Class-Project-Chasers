/******************************************************************************
Copyright(C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name : Block.cpp
Project Name: doodle
Course Name: CS225
Term: Summer 2020
Author
- Doyoung Lee doyoung413@gmail.com
Creation Date : 2020.07.31

Source file for block
******************************************************************************/
#include "Block.hpp"
#include "ObjectManager.hpp"

Block::Block(double positionX, double positionY, double speedX, double speedY, double width, double height,
             DrawType drawType)
    : Object(positionX, positionY, speedX, speedY, width, height, drawType)
{
    objectType = ObjectType::BLOCK;
}

Block::Block(double positionX, double positionY, double speedX, double speedY, double width, double height,
             const std::filesystem::path& imagePath)
    : Object(positionX, positionY, speedX, speedY, width, height, imagePath)
{
    objectType = ObjectType::BLOCK;
}

void Block::Update()
{
    Object::SetMinMax();
    Object::Update();
}
