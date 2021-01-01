/******************************************************************************
Copyright(C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name : Vector2.hpp
Project Name:   doodle
Course Name: CS225
Term: Summer 2020
Author
- Jiwon Jung jjwon6218@gmail.com
Creation Date : 2020.08.07

Source file for vector2 and operator overloading (dot product)
******************************************************************************/
#pragma once

struct vector2
{
    double x, y;
};

double operator*(const vector2& v, const vector2& u) noexcept { return v.x * u.x + v.y * u.y; }