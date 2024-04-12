#pragma once
#include "utils.h"
#include "Camera.h"
#include "Character.h"
#include "Background.h"
#include <iostream>
class Camera
{
public:

    Camera(Character& character, Background& background, float viewportWidth, float viewportHeight);
    Camera(Point2f CameraPosition);

    void update(float elapsedSec);
    void Draw();
    void MoveLeft(float elapsedSec);
    void MoveRight(float elapsedSec);
    void IniateFall();
  
    bool IsCharOnPlatform();


    float GetPositionX() const;

    float GetPositionY() const;
    Point2f GetPositionPoint2F();

    float GetAbsoluteReferenceX() const;
    float GetAbsoluteReferenceY() const;

   
private:

    //Private instance references
    Character& m_Character;
    Background& m_Background;

    float
        m_ViewportWidth,
        m_ViewportHeight,
        m_Camera_X,
        m_Camera_Y;
    
    Point2f
        m_BackGround_Position;
   
     
    bool
        m_CharCanFall;

};

