#include "pch.h"
#include "Background.h"

Background::Background(const std::string filename, Character& chrcter, float scale)
	:m_Scale{ scale }, m_Position{ -1200,0 }, m_ActFrame{ 0 }, m_AccuSec{ 0.f }, m_FrameSec{ 0.1f }, m_PositionFirestand{ -600,0 }, m_Character(chrcter)
{
	
	
	
	m_ColsFireStand = 9;
	m_RowsFireStand = 0;
	m_Background_Texture = new Texture(filename);

//	fireStand_Texture = new Texture("SourceImages/Small_Fire_Stand.png");
//	Lava_Texture = new Texture(filename);
	m_NrRows = 7;
	m_NrCols = 0;
	// Proper initialization of absolute firestand position
	m_AbsoluteFirestandPosX = m_Position.x - 1000;  // Assuming m_Position.x is appropriately set

}


void Background::Draw()
{
	m_NrRows = 7;
	m_NrCols = 0;

	//Width and height of background image itself
	   float Width = 6263;
	   float Height = 3372;

	//Width and height of firestand images
	   float fireStandsWidth = 2048/ m_ColsFireStand;
	   float fireStandsHeight = 512;

	//Width and height of the BasicSprites Images
	   float Lava_Texture_Width = 3600;
	   float Lava_Texture_Height = 800/m_NrRows;
	


	//Current row/col of firestand images
	int currentRowFireStand= m_ActFrame / m_ColsFireStand;
	int currentColFireStand = m_ActFrame % m_ColsFireStand;

	int currentRowLava = m_ActFrame % m_NrRows; // Considering 1 column for lava spritesheet
	//int currentColLava = m_ActFrame % m_NrRows;
	int currentColLava = 0;


	//Coordinate positions for the source rect of the firestand images
	float srcRectFirestandX = currentColFireStand * fireStandsWidth;
	float srcRectFirestandY = currentRowFireStand * fireStandsHeight;


	//Coordinate positions for the source rect of the lava images
	float srcRectLavaX = currentColLava * Lava_Texture_Width;
	float srcRectLavaY = currentRowLava * Lava_Texture_Height;

	//Draw Spritsheet Rects for background image
	Rectf SrcRect(0, 0, Width, Height);
	Rectf destRect(m_Position.x, m_Position.y, Width * m_Scale, Height*m_Scale);
//	Rectf destRect(0,0, Width * m_Scale, Height*m_Scale);
	m_Background_Texture->Draw(destRect, SrcRect);

	/*
	//Draw SpriteSheet rects for fireStand images
	Rectf srcRectFireStands(srcRectFirestandX, srcRectFirestandY, fireStandsWidth, fireStandsHeight);
	Rectf destRectFireStands(m_PositionFirestand.x +80, m_PositionFirestand.y, fireStandsWidth * float(0.4f), fireStandsHeight* float(0.4f));
	Rectf destRectFireStands2(m_PositionFirestand.x -750, 55, fireStandsWidth * float(0.4f), fireStandsHeight * float(0.4f));

	//Draw SpriteSheet Rect for BasicSprites Images
	Rectf srcRectLava(srcRectLavaX, srcRectLavaY, Lava_Texture_Width, Lava_Texture_Height);
	Rectf dstRectLava(m_Position.x, m_Position.y, Lava_Texture_Width * m_Scale, Lava_Texture_Height * m_Scale);  
	*/
//fireStand_Texture->Draw(destRectFireStands, srcRectFireStands);
//	fireStand_Texture->Draw(destRectFireStands2, srcRectFireStands);
//	Lava_Texture->Draw(dstRectLava, srcRectLava);
}


void Background::Update(float elapsedSec)
{
	// Update the accumulated time
	m_AccuSec += elapsedSec;

	// Check if enough time has passed to update the frame
	if (m_AccuSec >= m_FrameSec)
	{
		// Reset the accumulated time
		m_AccuSec -= m_FrameSec;

		// Increment the frame counter
		++m_ActFrame;

		// Check if the frame counter exceeds the total number of frames
		if (m_ActFrame >= m_ColsFireStand)
		{
			// Reset the frame counter to loop the animation
			m_ActFrame = 0;
		}
	}

	m_AbsoluteFirestandPosX = m_PositionFirestand.x - 850;
	

}

void Background::setPosition(const Point2f& newPosition) {
	
	m_Position = newPosition;

	//std::cout << "this is the background position:" << float(m_Position.x) << std::endl;
}

void Background::setPositionFireStand(const Point2f& newPosition)
{
	m_PositionFirestand = newPosition;
}

void Background::setPositionTest(const Point2f& newPosition)
{
	m_Colli_Pos_Test = newPosition;
}

bool Background::IsCharInPlatformCollision(Point2f Position, Point2f CharPos)
{
	 //Rectf PlatformMiddle{ m_PositionFirestand.x - 850, m_PositionFirestand.y /* + 50*/, 1115 , 100};
	const Point2f PF_MID_COORDS{ m_PositionFirestand.x - 3700 ,m_PositionFirestand.y - (2655) };
	const Point2f PF_RIGHT_COORDS{ m_Colli_Pos_Test.x  ,m_PositionFirestand.y -55};
	const Point2f PF_LEFT_COORDS{ m_Colli_Pos_Test.x - 3830, m_PositionFirestand.y - 55 };
	const float PF_WIDTH{ 2315 };
	const float L_PF_WIDTH{ 1047.5F };
	const float PF_HEIGHT{ 100 };


	 Rectf PlatformMiddle{ PF_MID_COORDS.x, PF_MID_COORDS.y, PF_WIDTH , PF_HEIGHT };
	 Rectf PlatformRight{ PF_RIGHT_COORDS.x, PF_RIGHT_COORDS.y , PF_WIDTH , PF_HEIGHT };
	 Rectf PlatformLeft{ PF_LEFT_COORDS.x, PF_LEFT_COORDS.y , L_PF_WIDTH, PF_HEIGHT };
	// Rectf PlatformMiddle{ m_PositionFirestand.x +850, m_PositionFirestand.y /* + 50*/, 1115 , 100};

	
	if (utils::IsPointInRect(Position, PlatformMiddle) || utils::IsPointInRect(CharPos, PlatformRight ) || utils::IsPointInRect(CharPos,PlatformLeft))
	{
		return true;
		
	}
	else
	{
	 utils::DrawRect(PlatformLeft, 10.F);
			return false;
		
	} 


}

bool Background::CharacterIsInsideOfPlatformMiddle(Point2f Position, Point2f CharPos)
{
	if (IsCharInPlatformCollision(Position, CharPos))
	{
		return true;
	}
	else
	{
		return false;
	}
		
}

bool Background::Check_Mid_PF_Border_Coll_Right_Side(Point2f CamPosition, Point2f CharPos)
{
	const Point2f PF_MID_COORDS{ m_PositionFirestand.x - 3700 ,m_PositionFirestand.y - (2655) };
	const Point2f PF_RIGHT_COORDS{ m_Colli_Pos_Test.x  ,m_PositionFirestand.y - 55 };
	const Point2f PF_LEFT_COORDS{ m_Colli_Pos_Test.x - 3830, m_PositionFirestand.y - 55 };
	const float PF_WIDTH{ 2315 };
	const float PF_HEIGHT{ 100 };
Rectf PlatformMiddle{ PF_MID_COORDS.x, PF_MID_COORDS.y, PF_WIDTH , PF_HEIGHT };
Rectf PlatformRight{ PF_RIGHT_COORDS.x, PF_RIGHT_COORDS.y , PF_WIDTH , PF_HEIGHT };



if (((CamPosition.x > PF_MID_COORDS.x + 3050 && CamPosition.x < PF_MID_COORDS.x + 3085) && CharPos.y <= 90) || ((CharPos.x > PF_LEFT_COORDS.x + 1010.F && CharPos.x < PF_LEFT_COORDS.x + 1045.F) && CharPos.y <= 90))
{
	return true;
}

else
{
	return false;

}
}

bool Background::Check_PF_Left_Side_Collisions(Point2f CamPosition, Point2f CharPos)
{
	//Coordinates (x,y) representing the collision rectangles:
	const Point2f PF_MID_COORDS{ m_PositionFirestand.x - 3700 ,m_PositionFirestand.y - (2655) };
	const Point2f PF_RIGHT_COORDS{ m_Colli_Pos_Test.x  ,m_PositionFirestand.y - 55 };
	//const Point2f PF_LEFT_COORDS{ m_PositionFirestand.x - 2830, m_PositionFirestand.y - 55};
	//width/height of the collision rectangles
	const float PF_WIDTH{ 2315 };
	const float PF_HEIGHT{ 100 };

	Rectf PlatformMiddle{ PF_MID_COORDS.x, PF_MID_COORDS.y, PF_WIDTH , PF_HEIGHT };
	Rectf PlatformRight{ PF_RIGHT_COORDS.x, PF_RIGHT_COORDS.y , PF_WIDTH , PF_HEIGHT };
	Rectf PlatformLeft{ m_PositionFirestand.x - 2830, m_PositionFirestand.y, 1115, 100 };

	if (((CamPosition.x > PF_MID_COORDS.x + 1880 && CamPosition.x < PF_MID_COORDS.x + 1905) && CharPos.y <= 90) || ((CharPos.x > PF_RIGHT_COORDS.x - 35 && CharPos.x < PF_RIGHT_COORDS.x) && CharPos.y<=90))
	{
		return true;
	}

	else
	{
		return false;

	}
}

float Background::GetAbsoluteReferenceX() const
{
	return m_AbsoluteFirestandPosX + 3100;
}

float Background::GetAbsoluteReferenceY() const
{
	return m_PositionFirestand.y + 90;
}

float Background::GetBackgroundWidth() const
{
	return m_Background_Texture_Width;
}

float Background::GetBackgroundHeight() const
{
	return m_Background_Texture_Height;
}

