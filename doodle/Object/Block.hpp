/******************************************************************************
Copyright(C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name : Block.hpp
Project Name: doodle
Course Name: CS225
Term: Summer 2020
Author
- Doyoung Lee doyoung413@gmail.com
Creation Date : 2020.07.31

Header file for block
******************************************************************************/
#pragma once
#include "Object.hpp"
#include <doodle/doodle.hpp>
#include <doodle/drawing.hpp>
#include <doodle/environment.hpp>

class Block : public Object
{
public:
    Block() = default;
    Block(double positionX, double positionY, double speedX, double speedY, double width, double height,
          DrawType drawType);
    Block(double positionX, double positionY, double speedX, double speedY, double width, double height,
          const std::filesystem::path& imagePath);
    void Update() override;

private:
};