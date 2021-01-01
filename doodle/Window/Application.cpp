/******************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Application.cpp
Project Name: doodle
Course Name: CS225
Term: Summer 2020
Author
    - jiwon.jung jjwon6218@gmail.com
Creation Date: 2020.07.22

    Source file for applicaiton
******************************************************************************/
#include "Application.h"

void Application::Init()
{
    doodle::create_window();

    sketch.setup();
}

void Application::Update()
{
    sketch.draw();
    Input();
}

void Application::Clear() { doodle::close_window(); }

void Application::Input() {}
