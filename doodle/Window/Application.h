/******************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Application.h
Project Name: doodle
Course Name: CS225
Term: Summer 2020
Author
    - jiwon.jung jjwon6218@gmail.com
Creation Date: 2020.07.22

    Header file for applicaiton
******************************************************************************/
#pragma once
#include "../Sketch.h"
#include <doodle/window.hpp>

class Application
{
public:
    Application() = default;
    void Init();
    void Update();
    void Clear();
    void Input();

private:
    Sketch sketch;
};