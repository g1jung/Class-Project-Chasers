/******************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Engine.h
Project Name: doodle
Course Name: CS225
Term: Summer 2020
Author
    - jiwon.jung jjwon6218@gmail.com
Creation Date: 2020.07.22

    Header file for Engine
******************************************************************************/
#pragma once
#include "Application.h"
#include <doodle/doodle.hpp>

class Engine
{
public:
    Engine() = default;

    void Init();
    void Update();
    void Clear();

private:
    Application app;
};