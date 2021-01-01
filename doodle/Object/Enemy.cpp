/******************************************************************************
Copyright(C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name : Enemy.cpp
Project Name: doodle
Course Name: CS225
Term: Summer 2020
Author
- Doyoung Lee doyoung413@gmail.com
Creation Date : 2020.07.30

Source file for enemy
******************************************************************************/
#include "Enemy.hpp"
#include "EnemyBullet.hpp"
#include "ObjectManager.hpp"

Enemy::Enemy(double positionX, double positionY, double speedX, double speedY, double width, double height,
             DrawType drawType, ObjectManager* objectManagerPointer)
    : Object(positionX, positionY, speedX, speedY, width, height, drawType), objectManager(objectManagerPointer)
{
    objectType = ObjectType::ENEMY;
}

Enemy::Enemy(double positionX, double positionY, double speedX, double speedY, double width, double height,
             const std::filesystem::path& imagePath, ObjectManager* objectManagerPointer)
    : Object(positionX, positionY, speedX, speedY, width, height, imagePath), objectManager(objectManagerPointer)
{
    objectType = ObjectType::ENEMY;
}

void Enemy::Update()
{
    Object::SetMinMax();

    if (objectManager->GetPlayer() != nullptr)
    {
        double playerX = objectManager->GetPlayer()->GetXPosition();
        double playerY = objectManager->GetPlayer()->GetYPosition();

        double dx = playerX - x;
        double dy = playerY - y;

        angle = atan2(dy, dx);

        double xVel = cos(angle) * xSpeed;
        double yVel = sin(angle) * ySpeed;

        // Check if enemy is attackable. If not, move enemy
        if (isObjectInAttackRange(*objectManager->GetPlayer()) == false)
        {
            x += xVel;
            y += yVel;
        }
        else
        {
            attackDelay -= DeltaTime;
            if (attackDelay < 0.0)
            {
                if (enemyType == EnemyType::MELEE) // attack method for melee enemy
                {
                    Player* player = objectManager->GetPlayer();
                    if ((player->GetState() & DAMAGE) != DAMAGE) // check player's damage state is on
                    {
                        player->SetHp(player->GetHp() - meleeDamage);
                        player->SetState(player->GetState() | DAMAGE);
                    }
                    attackDelay = 1.0;
                }
                else if (enemyType == EnemyType::RANGE) // attack method for range enemy
                {
                    double       bulletXSpeed = cos(angle) * 20;
                    double       bulletYSpeed = sin(angle) * 20;
                    EnemyBullet& bullet =
                        objectManager->AddObject<EnemyBullet>(x, y, bulletXSpeed, bulletYSpeed, 16.0, 16.0,
                                                              DrawType::ELLIPSE, BulletType::NORMAL, objectManager);
                    bullet.SetRotate(angle);
                    attackDelay = 1.0;
                }
            }
        }
        Draw();
    }

    if (hp <= 0)
    {
        objectManager->Destroy(id);
    }
}

void Enemy::Draw()
{
    push_settings();
    apply_translate(x, y);
    apply_rotate(angle);
    switch (drawType)
    {
        case DrawType::ELLIPSE:
            draw_ellipse(0, 0, width, width);
            draw_ellipse(0, -(height / 2.0), width, height);
            break;
        case DrawType::RECTANGLE:
            draw_ellipse(0, 0, width, width);
            if (enemyType == EnemyType::MELEE)
            {
                draw_rectangle(0, -height, width, height / 2);
                draw_rectangle(0, height / 2.0, width, height / 2);
            }
            else if (enemyType == EnemyType::RANGE)
            {
                draw_rectangle(0, -(height / 4.0), width, height / 2.0);
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
}

bool Enemy::isObjectInAttackRange(Object& object) noexcept // Check player is in attack range
{
    if (&object != nullptr)
    {
        return !(maxX + attackRange < object.GetMinX() || object.GetMaxX() < minX - attackRange ||
                 maxY + attackRange < object.GetMinY() || object.GetMaxY() < minY - attackRange);
    }
    return false;
}

void Enemy::SetAttackType(EnemyType type)
{
    switch (type)
    {
        case EnemyType::MELEE:
            enemyType = type;
            SetAttackRange(10.0);
            break;
        case EnemyType::RANGE:
            enemyType = type;
            SetAttackRange(256.0);
            break;
    }
}
