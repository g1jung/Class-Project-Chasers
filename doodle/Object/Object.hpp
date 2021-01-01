/******************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Object.hpp
Project Name: doodle
Course Name: CS225
Term: Summer 2020
Author
    - Doyoung Lee doyoung413@gmail.com
Creation Date: 2020.07.22

    Header file for object
******************************************************************************/
#pragma once
#include <doodle/doodle.hpp>
#include <doodle/drawing.hpp>
#include <doodle/environment.hpp>

using namespace doodle;

enum class DrawType
{
    NONE,
    ELLIPSE,
    RECTANGLE,
};

enum class ObjectType
{
    NORMAL,
    PLAYER,
    ENEMY,
    BULLET,
    ENEMYBULLET,
    BLOCK,
    ITEM
};

class Object
{
public:
    Object() = default;
    Object(double positionX, double positionY, double speedX, double speedY, double width, double height,
           DrawType drawType);
    Object(double positionX, double positionY, double speedX, double speedY, double width, double height,
           const std::filesystem::path& imagePath);
    virtual ~Object() = default;
    virtual void Update();
    virtual void Draw();

    int        GetId() { return id; }
    void       SetId(int value) { id = value; }
    void       SetRotate(double value) { angle = value; }
    double     GetXPosition() { return x; }
    double     GetYPosition() { return y; }
    double     GetXScale() { return width; }
    double     GetYScale() { return height; }
    ObjectType GetObjectType() { return objectType; }
    DrawType   GetDrawType() { return drawType; }

    double GetMinX() { return minX; }
    double GetMinY() { return minY; }
    double GetMaxX() { return maxX; }
    double GetMaxY() { return maxY; }
    void   SetMinMax();

    bool isCollideWithObject(Object& object) noexcept;

protected:
    double x      = 0;
    double y      = 0;
    double xSpeed = 0;
    double ySpeed = 0;
    double angle  = 0;
    double width  = 0;
    double height = 0;

    double minX = 0;
    double minY = 0;
    double maxX = 0;
    double maxY = 0;

    int        id         = 0;
    bool       isImageHad = false;
    DrawType   drawType   = DrawType::NONE;
    ObjectType objectType = ObjectType::NORMAL;
    Image      sprite;
};