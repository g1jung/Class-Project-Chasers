/******************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   ConsoleMain.cpp
Project Name:   doodle
Course Name: CS225
Term: Summer 2020
Author
    - Rudy Castan

    Header file for main in debug mode
******************************************************************************/
#include "../Window/Engine.h"
#include <doodle/window.hpp>
#include <exception>
#include <iostream>

int main(void)
{
    Engine engine;

    try
    {
        engine.Init();

        while (!doodle::is_window_closed())
        {
            doodle::update_window();
            engine.Update();
        }

        engine.Clear();

        return 0;
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << "\n";
        return -1;
    }
}
