/******************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Object.cpp
Project Name: doodle
Course Name: CS225
Term: Summer 2020
Author
    - Doyoung Lee doyoung413@gmail.com
Creation Date: 2020.07.22

    Source file for object
******************************************************************************/
#include "Object.hpp"

using namespace doodle;

Object::Object(double positionX, double positionY, double speedX, double speedY, double width, double height,
               DrawType drawType)
{
    x      = positionX;
    y      = positionY;
    xSpeed = speedX;
    ySpeed = speedY;

    this->width    = width;
    this->height   = height;
    this->drawType = drawType;
}

Object::Object(double positionX, double positionY, double speedX, double speedY, double width, double height,
               const std::filesystem::path& imagePath)
{
    x      = positionX;
    y      = positionY;
    xSpeed = speedX;
    ySpeed = speedY;

    this->width  = width;
    this->height = height;

    sprite     = Image::Image(imagePath, false);
    isImageHad = true;
}

void Object::Update()
{
    double halfWidth  = width / 2.0;
    double halfHeight = height / 2.0;
    minX              = x - halfWidth;
    maxX              = x + halfWidth;

    minY = y - halfHeight;
    maxY = y + halfHeight;

    Draw();
}

void Object::Draw()
{
    push_settings();
    apply_translate(x, y);
    apply_rotate(angle);
    switch (drawType)
    {
        case DrawType::ELLIPSE: draw_ellipse(0, 0, width, height); break;
        case DrawType::RECTANGLE: draw_rectangle(0, 0, width, height); break;
        default: break;
    }

    if (isImageHad == true)
    {
        set_image_mode(RectMode::Center);
        draw_image(sprite, 0, 0, width, height);
    }
    pop_settings();
}

void Object::SetMinMax()
{
    double halfWidth  = width / 2.0;
    double halfHeight = height / 2.0;
    minX              = x - halfWidth;
    maxX              = x + halfWidth;

    minY = y - halfHeight;
    maxY = y + halfHeight;
}

bool Object::isCollideWithObject(Object& object) noexcept
{
    if (&object != nullptr)
    {
        return !(maxX < object.GetMinX() || object.GetMaxX() < minX || maxY < object.GetMinY() ||
                 object.GetMaxY() < minY);
    }
    return false;
}
