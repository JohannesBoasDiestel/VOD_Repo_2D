#include "pch.h"
#include "Camera.h"


Camera::Camera(Character& character, Background& background, float viewportWidth, float viewportHeight)
:m_Character(character), m_Background(background), m_ViewportWidth(viewportWidth), m_ViewportHeight(viewportHeight), m_BackGround_Position(0, 0)
{

    m_Camera_X = 0;
    m_Camera_Y = 0;
    m_CharCanFall = false;

}

void Camera::update(float elapsedSec)
{
  
    //In relation to the setting of the background position
    m_BackGround_Position.x = -m_Camera_X - m_Background.GetBackgroundWidth()/2;
    m_BackGround_Position.y = -m_Camera_Y -180;
   m_Background.setPosition(Point2f(m_BackGround_Position.x, m_BackGround_Position.y));
  // Draw the background 
   m_Background.Draw();







   /////////////////////////////////////////////////////////////////////////////////////
   m_Background.setPositionFireStand(Point2f(m_Camera_X, m_Camera_Y));
 
   m_Background.setPositionTest(Point2f{ m_Camera_X, m_Camera_Y });

    if (m_CharCanFall)
    {

        m_Character.fall(elapsedSec);
    }

}

void Camera::Draw()
{
   
}

void Camera::MoveLeft(float elapsedSec)
{
    m_Camera_X -= 600 * elapsedSec;
   
    if (m_Camera_X <= -m_Background.GetBackgroundWidth() / 2)
    {
        m_Camera_X = -m_Background.GetBackgroundWidth() / 2;
        
        m_Character.LeftBorderReached();
        
    }

    /*
    if (m_Camera_X <= -1400)
    {
       // m_Camera_X = -1400;
      //  m_Character.InitiateConversation();
    }

/*
    float backgroundX = -m_Camera_X + (500);
    float firestandPosX = backgroundX - 1000;
 */   
    if (m_Background.IsCharInPlatformCollision(Point2f{ m_Camera_X,m_Camera_Y },Point2f{m_Character.getPosition()}))
    {
       
    }
    else
    {
     
    }
}
void Camera::MoveRight(float elapsedSec)
{

    const float SCREEN_BORDER_TO_MID_OF_SCREEN{ (1920 / 2) -600 };
    m_Camera_X += 600 * elapsedSec;
    
    if (m_Camera_X >= -SCREEN_BORDER_TO_MID_OF_SCREEN)
    {
        m_Camera_X = -SCREEN_BORDER_TO_MID_OF_SCREEN;
        m_Character.RightBorderReached();

    }
}



float Camera::GetPositionX() const
{
    return m_Camera_X;
}

float Camera::GetPositionY() const
{
    return m_Camera_Y;
}
float Camera::GetAbsoluteReferenceX() const
{
    return m_Camera_X;
}
float Camera::GetAbsoluteReferenceY() const
{
    return m_Camera_Y;
}
/*
Point2f Camera::GetPositionPoint2F()
{
    return CameraLeftSideStartPos;
}
*/