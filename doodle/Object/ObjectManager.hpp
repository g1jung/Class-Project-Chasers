/******************************************************************************
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   ObjectManager.hpp
Project Name: doodle
Course Name: CS225
Term: Summer 2020
Author
    - Doyoung Lee doyoung413@gmail.com
Creation Date: 2020.07.22

    Header file for object manager
******************************************************************************/
#pragma once
#include "Object.hpp"
#include "Player.hpp"
#include <map>
#include <memory>
#include <vector>

class ObjectManager
{
public:
    ObjectManager()  = default;
    ~ObjectManager() = default;

    void Update();

    template <typename T, typename... Args>
    T& AddObject(Args... args) // add object into map
    {
        auto object = std::unique_ptr<T>(std::make_unique<T>(std::forward<Args>(args)...));
        if constexpr (std::is_base_of<Player, T>::value)
        {
            player = object.get();
        }
        T& objectRef = *object.get();
        static_cast<Object&>(objectRef).SetId(lastObjectID);

        objectMap[lastObjectID] = std::move(object);
        objectMap[lastObjectID].get()->SetId(lastObjectID++);

        return objectRef;
    }

    void                                    Destroy(int id);
    void                                    DestroyAllObjects();
    int                                     GetLastObjectID() { return lastObjectID; }
    Player*                                 GetPlayer() { return player; }
    std::map<int, std::unique_ptr<Object>>& GetObjectMap() { return objectMap; }
    void                                    CollideObjects();

private:
    int                                    lastObjectID = 0;
    std::map<int, std::unique_ptr<Object>> objectMap;
    std::vector<int>                       objectsToBeDeleted; // list of object id to be deleted
    Player*                                player = nullptr;
};