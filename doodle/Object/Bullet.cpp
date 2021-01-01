/******************************************************************************
Copyright(C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name : Bullet.hpp
Project Name: doodle
Course Name: CS225
Term: Summer 2020
Author
- Doyoung Lee doyoung413@gmail.com
Creation Date : 2020.07.28

Source file for bullet
******************************************************************************/
#include "Bullet.hpp"
#include "ObjectManager.hpp"

Bullet::Bullet(double positionX, double positionY, double speedX, double speedY, double width, double height,
               DrawType drawType, BulletType bulletType, ObjectManager* objectManagerPointer)
    : Object(positionX, positionY, speedX, speedY, width, height, drawType), objectManager(objectManagerPointer)
{
    objectType       = ObjectType::BULLET;
    this->bulletType = bulletType;
}

Bullet::Bullet(double positionX, double positionY, double speedX, double speedY, double width, double height,
               const std::filesystem::path& imagePath, BulletType bulletType, ObjectManager* objectManagerPointer)
    : Object(positionX, positionY, speedX, speedY, width, height, imagePath), objectManager(objectManagerPointer)
{
    objectType       = ObjectType::BULLET;
    this->bulletType = bulletType;
}

void Bullet::Update()
{
    Object::SetMinMax();
    if (bulletType == BulletType::SHOTGUN)
    {
        lifeTime -= DeltaTime;
    }

    Draw();
    // Check if bullet went out of the camera range
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
}

void Bullet::Draw()
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