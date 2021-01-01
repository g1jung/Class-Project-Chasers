/******************************************************************************
Copyright(C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name : Player.hpp
Project Name: doodle
Course Name: CS225
Term: Summer 2020
Author
- Doyoung Lee doyoung413@gmail.com
Creation Date : 2020.07.25

Header file for player
******************************************************************************/
#pragma once
#include "Item.hpp"
#include "Object.hpp"
#include <doodle/doodle.hpp>
#include <doodle/drawing.hpp>
#include <doodle/environment.hpp>
#include <iostream>

constexpr int DAMAGE = 4;
constexpr int MOVE   = 2;
constexpr int ATTACK = 1;

class ObjectManager;

enum class WeaponType
{
    NORMAL,
    SHOTGUN,
    MACHINEGUN
};

enum class Direction
{
    NODIRECTION,
    UP,
    LEFT,
    DOWN,
    RIGHT
};

class Player : public Object
{
public:
    Player() = default;
    Player(double positionX, double positionY, double speedX, double speedY, double width, double height,
           DrawType drawType, ObjectManager* objectManagerPointer);
    Player(double positionX, double positionY, double speedX, double speedY, double width, double height,
           const std::filesystem::path& imagePath, ObjectManager* objectManagerPointer);
    void Update() override;
    void Draw() override;

    void Move(Direction direction);
    void GunShot();

    void NormalShot();
    void SpreadShot();
    void MachineGunShot();

    bool   Collision();
    double ShortestDistanceSqr(double circleX, double circleY, double onesideX, double onesideY, double theotherX,
                               double theotherY);

    void SetWeapon(WeaponType type);
    void GetItem(ItemType itemType);

    void SetState(int value) { state = value; }
    int  GetState() { return state; }

    void SetHp(int value) { hp = value; }
    int  GetHp() { return hp; }

private:
    Direction  direction  = Direction::NODIRECTION;
    WeaponType weaponType = WeaponType::NORMAL;

    double shotDelay        = 0.0;
    double normalShotDelay  = 0.3;
    double spreadShotDelay  = 1.0;
    double machineShotDelay = 0.1;

    bool isShootAble = true;

    ObjectManager* objectManager = nullptr;

    int    state          = 0;
    int    maxHp          = 100;
    int    hp             = 100;
    double invisibleDelay = 1.0;
};