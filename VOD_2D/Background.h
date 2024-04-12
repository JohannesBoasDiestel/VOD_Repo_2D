#pragma once
#include "texture.h"
#include "utils.h"
#include "Character.h"
#include <iostream>
//#include "MeatBody.h"

class Background
{
public:

	//constructors
	Background(const std::string filename, Character& chrcter, float scale);
	Background(const std::string filename, Character& chrcter, int numRows, int numCols,  float scale);



	void Draw();
	void Update(float elapsedSec);

	// Method to set the position of the background
	void setPosition(const Point2f& newPosition);
	void setPositionFireStand(const Point2f& newPosition);
	void setPositionTest(const Point2f& newPosition);
	
	//Methods for Platform Collison Detection
	bool IsCharInPlatformCollision(Point2f Position, Point2f CharPos);
	bool CharacterIsInsideOfPlatformMiddle(Point2f Position, Point2f CharPos);
	bool Check_Mid_PF_Border_Coll_Right_Side(Point2f CamPosition, Point2f CharPos);  //When Char is in the middle of screen, position is tracked via the camera
	bool Check_PF_Left_Side_Collisions(Point2f CamPosition, Point2f CharPos); 

	float getAbsoluteFirestandPosX() const { return m_AbsoluteFirestandPosX; }


	//Due to most of the object positions being set in the background class, it is necerssary to create some functions that give us absolute references for object positions 
	//From which we can in turn create collision functionality.
	float GetAbsoluteReferenceX() const;
	float GetAbsoluteReferenceY() const;

	float GetBackgroundWidth() const;
	float GetBackgroundHeight() const;

	
private:
	Texture* m_Background_Texture;
	//Texture* fireStand_Texture;
	//Texture* Lava_Texture;

	Character&
		m_Character;

	float
	    m_Scale,
		m_AbsoluteFirestandPosX;

	Point2f
		m_Position, m_PositionFirestand, m_CharRelativePos{}, m_Colli_Pos_Test;


	int
		m_ColsFireStand, m_RowsFireStand;
	float
		m_FrameSec, m_AccuSec;
	int
		m_NrRows, m_NrCols,
		m_ActFrame;

	const float
		m_Background_Texture_Width{ 6263.f },
		m_Background_Texture_Height{ 3372.f};

//	bool m_CharIsOnPlatform;

};

