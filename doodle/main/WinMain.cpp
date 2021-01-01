/******************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   WinMain.cpp
Project Name:   doodle
Course Name: CS225
Term: Summer 2020
Author
    - Rudy Castan

    Header file for main in release mode
******************************************************************************/
#include "../Sketch.h"
#include "../Window/Engine.h"
#include <doodle/window.hpp>
#include <exception>

#include <sdkddkver.h>
#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
#include <Windows.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine,
                      _In_ int nCmdShow)
try
{
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    Engine engine;
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
    MessageBox(nullptr, e.what(), "Error", MB_OK | MB_ICONERROR);
    return -1;
}
