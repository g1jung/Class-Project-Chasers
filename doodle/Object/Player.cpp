/******************************************************************************
Copyright(C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name : Player.cpp
Project Name: doodle
Course Name: CS225
Term: Summer 2020
Author
- Doyoung Lee doyoung413@gmail.com
- Jiwon Jung jjwon6218@gmail.com
Creation Date : 2020.07.25

Source file for player
******************************************************************************/
#include "Player.hpp"
#include "../Math/Vector2.hpp"
#include "Bullet.hpp"
#include "ObjectManager.hpp"
#include <iostream>
#include <string>

Player::Player(double positionX, double positionY, double speedX, double speedY, double width, double height,
               DrawType drawType, ObjectManager* objectManagerPointer)
    : Object(positionX, positionY, speedX, speedY, width, height, drawType), objectManager(objectManagerPointer)
{
    objectType = ObjectType::PLAYER;
}

Player::Player(double positionX, double positionY, double speedX, double speedY, double width, double height,
               const std::filesystem::path& imagePath, ObjectManager* objectManagerPointer)
    : Object(positionX, positionY, speedX, speedY, width, height, imagePath), objectManager(objectManagerPointer)
{
    objectType = ObjectType::PLAYER;
}

void Player::Update()
{
    Object::SetMinMax();

    if (isShootAble == false)
    {
        shotDelay += DeltaTime;
        switch (weaponType)
        {
            case WeaponType::NORMAL:
                if (shotDelay > normalShotDelay)
                {
                    isShootAble = true;
                    shotDelay   = 0.0;
                }
                break;
            case WeaponType::SHOTGUN:
                if (shotDelay > spreadShotDelay)
                {
                    isShootAble = true;
                    shotDelay   = 0.0;
                }
                break;
            case WeaponType::MACHINEGUN:
                if (shotDelay > machineShotDelay)
                {
                    isShootAble = true;
                    shotDelay   = 0.0;
                }
                break;
        };
    }
    Draw();

    if (hp < 0)
    {
        objectManager->DestroyAllObjects();
        close_window();
    }
    if (hp >= maxHp)
    {
        hp = maxHp;
    }
}

void Player::Draw()
{
    const int mouseX = get_mouse_x();
    const int mouseY = get_mouse_y();

    double dx = mouseX - x;
    double dy = mouseY - y;

    double gunAngle = atan2(dy, dx);

    angle = gunAngle;

    push_settings();
    apply_translate(x, y);
    apply_rotate(angle);

    if ((state & MOVE) == MOVE)
    {
        if ((state & DAMAGE) == DAMAGE)
        {
            set_fill_color(Color{0, 255, 0, 100});
            invisibleDelay -= DeltaTime;
        }
        else
        {
            set_fill_color(Color{0, 255, 0, 255});
        }
    }
    else if ((state & DAMAGE) == DAMAGE)
    {
        set_fill_color(100);
        invisibleDelay -= DeltaTime;
    }
    else
    {
        set_fill_color(Color{255, 255, 255, 255});
    }

    if (invisibleDelay < 0.0)
    {
        invisibleDelay = 1.0;
        set_fill_color(Color{0, 0, 0, 255});
        state = state & (MOVE | ATTACK);
    }

    switch (drawType)
    {
        case DrawType::ELLIPSE:
            draw_ellipse(0, 0, width, width);
            draw_ellipse(0, -(height / 2.0), width, height);
            break;
        case DrawType::RECTANGLE:
            draw_ellipse(0, 0, width, width);
            draw_rectangle(0, -(height / 2.0), width, height);

            if ((state & ATTACK) == ATTACK)
            {
                draw_ellipse(width, -(height / 2.0), width, width);
            }

            break;
        default: break;
    }

    if (isImageHad == true)
    {
        set_image_mode(RectMode::Center);
        draw_image(sprite, 0, -(height / 2.0), width, height);
    }
    pop_settings();

    push_settings(); // draw UI
    set_font_size(48);
    set_outline_color(0);
    set_fill_color(255);
    const std::string hpText = "HP:" + std::to_string(hp);
    draw_text(hpText, -(Width / 2.0) + 48, (Height / 2.0) - 96);
    pop_settings();
}

void Player::Move(Direction direction_)
{
    this->direction = direction_;

    if (this->direction != Direction::NODIRECTION)
    {
        if (this->direction == Direction::LEFT)
        {
            state = state | MOVE;
            x -= xSpeed;
            if (Collision() == true || x > Width / 2 ||
                x < -(Width / 2)) // Check collision with other object or player is in the screen
                x += xSpeed;      // if collision happened, cancel previous movement
        }
        if (this->direction == Direction::RIGHT)
        {
            state = state | MOVE;
            x += xSpeed;
            if (Collision() == true || x > Width / 2 || x < -(Width / 2))
                x -= xSpeed;
        }
        if (this->direction == Direction::UP)
        {
            state = state | MOVE;
            y += ySpeed;
            if (Collision() == true || y > Height / 2 || y < -(Height / 2))
            {
                y -= ySpeed;
            }
        }
        if (this->direction == Direction::DOWN)
        {
            state = state | MOVE;
            y -= ySpeed;
            if (Collision() == true || y > Height / 2 || y < -(Height / 2))
            {
                y += ySpeed;
            }
        }
    }
    else
    {
        state = state & (DAMAGE | ATTACK);
    }
}

void Player::GunShot()
{
    if (isShootAble == true)
    {
        state = state | ATTACK;
        switch (weaponType)
        {
            case WeaponType::NORMAL:
                NormalShot();
                shotDelay = 0.0;
                break;
            case WeaponType::SHOTGUN:
                SpreadShot();
                shotDelay = 0.0;
                break;
            case WeaponType::MACHINEGUN:
                MachineGunShot();
                shotDelay = 0.0;
                break;
        };
        isShootAble = false;
        state       = state & (DAMAGE | MOVE);
    }
}


void Player::NormalShot()
{
    const int mouseX = get_mouse_x();
    const int mouseY = get_mouse_y();

    double dx = mouseX - x;
    double dy = mouseY - y;

    double gunAngle = atan2(dy, dx);

    dx = cos(gunAngle) * 20;
    dy = sin(gunAngle) * 20;

    objectManager->AddObject<Bullet>(x, y, dx, dy, 16.0, 16.0, DrawType::ELLIPSE, BulletType::NORMAL, objectManager);
}

void Player::SpreadShot()
{
    for (int i = 0; i < 7; i++)
    {
        const int mouseX = get_mouse_x();
        const int mouseY = get_mouse_y();
        // Used bitwise operation instead of arithmetic calculation
        double dx = mouseX - x + (rand() & 0x15) - (rand() & 0x15);
        double dy = mouseY - y + (rand() & 0x15) - (rand() & 0x15);

        double gunAngle = atan2(dy, dx);

        dx = cos(gunAngle) * 20 + (static_cast<double>(rand() % 10) - static_cast<double>(rand() % 10));
        dy = sin(gunAngle) * 20 + (static_cast<double>(rand() % 10) - static_cast<double>(rand() % 10));

        objectManager->AddObject<Bullet>(x, y, dx, dy, 16.0, 16.0, DrawType::ELLIPSE, BulletType::SHOTGUN,
                                         objectManager);
    }
}

void Player::MachineGunShot()
{
    const int mouseX = get_mouse_x();
    const int mouseY = get_mouse_y();

    double dx = mouseX - x;
    double dy = mouseY - y;

    double gunAngle = atan2(dy, dx);

    dx = cos(gunAngle) * 20 + (static_cast<double>(rand() % 3) - static_cast<double>(rand() % 3));
    dy = sin(gunAngle) * 20 + (static_cast<double>(rand() % 3) - static_cast<double>(rand() % 3));

    objectManager->AddObject<Bullet>(x, y, dx, dy, 16.0, 16.0, DrawType::ELLIPSE, BulletType::MACHINEGUN,
                                     objectManager);
}

bool Player::Collision()
{
    double playerPosX  = x;
    double playerPosY  = y;
    double playerScale = width;

    double objectPosX, objectPosY, objectScaleX, objectScaleY;

    for (const auto& obj : objectManager->GetObjectMap())
    {
        if (obj.second->GetObjectType() != ObjectType::PLAYER &&
            obj.second->GetObjectType() == ObjectType::BLOCK) // check object is block
        {
            objectPosX   = obj.second->GetXPosition();
            objectPosY   = obj.second->GetYPosition();
            objectScaleX = obj.second->GetXScale();
            objectScaleY = obj.second->GetYScale();
            // If ellipse object collided with player
            if (obj.second->GetDrawType() == DrawType::ELLIPSE)
            {
                double squareDistance, compareStandard;

                squareDistance = (playerPosX - objectPosX) * (playerPosX - objectPosX) +
                                 (playerPosY - objectPosY) * (playerPosY - objectPosY);

                compareStandard = ((playerScale / 2) + (objectScaleX / 2)) * ((playerScale / 2) + (objectScaleX / 2));

                if (compareStandard >= squareDistance)
                {
                    std::cout << "Collision Detected" << std::endl;
                    return true;
                }
            }
            else if (obj.second->GetDrawType() == DrawType::RECTANGLE)
            {
                // 4 edge points of the rectangle

                double objectScaleHelperX = objectScaleX / 2;
                double objectScaleHelperY = objectScaleY / 2;

                double rectTopLeftX     = objectPosX - objectScaleHelperX;
                double rectTopLeftY     = objectPosY + objectScaleHelperY;
                double rectBottomRightX = objectPosX + objectScaleHelperX;
                double rectBottomRightY = objectPosY - objectScaleHelperY;
                double rectTopRightX    = objectPosX + objectScaleHelperX;
                double rectTopRightY    = objectPosY + objectScaleHelperY;
                double rectBottomLeftX  = objectPosX - objectScaleHelperX;
                double rectBottomLeftY  = objectPosY - objectScaleHelperY;

                double r = playerScale / 2;
                // check if circle is bordered with square
                if ((ShortestDistanceSqr(playerPosX, playerPosY, rectTopLeftX, rectTopLeftY, rectBottomLeftX,
                                         rectBottomLeftY) <= r * r) ||
                    (ShortestDistanceSqr(playerPosX, playerPosY, rectTopRightX, rectTopRightY, rectBottomRightX,
                                         rectBottomRightY) <= r * r) ||
                    (ShortestDistanceSqr(playerPosX, playerPosY, rectTopLeftX, rectTopLeftY, rectTopRightX,
                                         rectTopRightY) <= r * r) ||
                    (ShortestDistanceSqr(playerPosX, playerPosY, rectBottomLeftX, rectBottomLeftY, rectBottomRightX,
                                         rectBottomRightY) <= r * r))
                {
                    return true; // collision check is true
                }
                else
                {
                    return false; // collision check is false
                }
            }
        }
    }

    return false;
}

double Player::ShortestDistanceSqr(double circleX, double circleY, double onesideX, double onesideY, double theotherX,
                                   double theotherY)
{
    double distanceSqr;

    // Vector between point p and the start point of the edge
    double minusRPX = circleX - onesideX;
    double minusRPY = circleY - onesideY;
    // Vector between start point of the edge and end point of the edge
    double minusQPX = theotherX - onesideX;
    double minusQPY = theotherY - onesideY;
    // Vector between point p and the end point of the edge
    double minusRQX = circleX - theotherX;
    double minusRQY = circleY - theotherY;

    vector2 minusRP = {minusRPX, minusRPY};
    vector2 minusQP = {minusQPX, minusQPY};
    vector2 minusRQ = {minusRQX, minusRQY};

    // distance between line and the point
    if ((minusRP * minusQP) < 0) // When edgeStart is the closest point on line to point R
    {
        distanceSqr = minusRP * minusRP;
    }
    // When edgeEnd is the closest point on line to point R
    else if ((minusRP * minusQP) > (minusQP * minusQP))
    {
        distanceSqr = minusRQ * minusRQ;
    }
    // When closest point from point R is on the edge
    else
    {
        distanceSqr = (minusRP * minusRP) - ((minusRP * minusQP) * (minusRP * minusQP)) / (minusQP * minusQP);
    }

    return distanceSqr;
}

void Player::SetWeapon(WeaponType type)
{
    weaponType  = type;
    shotDelay   = 0.0;
    isShootAble = false;
}

void Player::GetItem(ItemType itemType)
{
    switch (itemType)
    {
        case ItemType::MEDKIT:
            std::cout << "Get MedKit" << std::endl;
            hp += 50;
            break;
        case ItemType::AMMO: std::cout << "Get Ammo" << std::endl; break;
        default: break;
    }
}
