/******************************************************************************
Copyright(C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name : EnemyBullet.hpp
Project Name: doodle
Course Name: CS225
Term: Summer 2020
Author
- Doyoung Lee doyoung413@gmail.com
Creation Date : 2020.07.30

Source file for enemy bullet
******************************************************************************/
#include "EnemyBullet.hpp"
#include "ObjectManager.hpp"

EnemyBullet::EnemyBullet(double positionX, double positionY, double speedX, double speedY, double width, double height,
                         DrawType drawType, BulletType bulletType, ObjectManager* objectManagerPointer)
    : Object(positionX, positionY, speedX, speedY, width, height, drawType), objectManager(objectManagerPointer)
{
    objectType       = ObjectType::ENEMYBULLET;
    this->bulletType = bulletType;
}

EnemyBullet::EnemyBullet(double positionX, double positionY, double speedX, double speedY, double width, double height,
                         const std::filesystem::path& imagePath, BulletType bulletType,
                         ObjectManager* objectManagerPointer)
    : Object(positionX, positionY, speedX, speedY, width, height, imagePath), objectManager(objectManagerPointer)
{
    objectType       = ObjectType::ENEMYBULLET;
    this->bulletType = bulletType;
}

void EnemyBullet::Update()
{
    Object::SetMinMax();
    if (bulletType == BulletType::SHOTGUN)
    {
        lifeTime -= DeltaTime;
    }

    Draw();
    // Check if bullets went out of camera range
    if (y > Height / 2 || y < -(Height / 2))
    {
        objectManager->Destroy(id);
    }
    else if (x > Width / 2 || x < -(Width / 2))
    {
        objectManager->Destroy(id);
    }
    if (lifeTime < 0.0)
    {
        objectManager->Destroy(id);
    }

    if (isCollideWithPlayer() == true)
    {
        Player* player = objectManager->GetPlayer();
        if ((player->GetState() & DAMAGE) != DAMAGE) // check player's damage state is on
        {
            player->SetHp(player->GetHp() - damage);
            player->SetState(player->GetState() | DAMAGE);
        }
        objectManager->Destroy(id);
    }
}

void EnemyBullet::Draw()
{
    x += xSpeed;
    y += ySpeed;

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
            draw_rectangle(0, -(height / 2.0), width, height);
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

bool EnemyBullet::isCollideWithPlayer() noexcept // function that check if collide with player
{
    Object& object = *objectManager->GetPlayer();
    if (&object != nullptr)
    {
        return !(maxX < object.GetMinX() || object.GetMaxX() < minX || maxY < object.GetMinY() ||
                 object.GetMaxY() < minY);
    }
    return false;
}
