#pragma once

#include <utils.h>
#include <Texture.h>
#include <algorithm>


//#include "Camera.h"
class Character
{
	

//Added an enumeration class to keep track of the directions
	enum class Movement_States
	{
		NONE,
		ATTACKONE, 
		ATTACKTWO,
		FLYINGATTACKAIR,
		JUMPMOVE,
		CROUCH,
		JUMP,
		LEFT,
		RIGHT,
		DEATH
	};

public:

	//constructors
	Character(const std::string& filename, const int nrCols, const int nrRows, float scale, float frameSec);
	Character(const Character& other);
	Character& operator=(const Character& other);

	//destructors
	~Character();

	

	//initalise the conversation
	void InitConversation();
	void IncrementConversationOptionIndex();
	void ShakeConversationBubble(float elapsedSec);
	void HandleConvoBubbleAndTextOffsets();

	void update(float elapsedSec);

	void Draw();

	void MoveLeft(float elapsedSec);
	void MoveRight(float elapsedSec);
	void MoveJump(float elapsedSec);
	void Jump();
	bool IsJumping();
	void fall(float elapsedSec);
	void CrouchDown();
	void StopMoving();
	void AttackOne();
	void AttackTwo();
	void AtackFlyingAir();
    
	//Methods for checking the camera borders
	void LeftBorderReached();
	void RightBorderReached();

	//Initiate conversation based on camera position
	void InitiateConversation();
	bool IsInConversation();
	void EndConversation();

	//Function for leftward movement
	void SetMovingLeft(bool isMovingLeft) 
	   { m_IsMovingLeft = isMovingLeft; }

	bool canUseAttackTwo();

	//Method for character death
	bool IsCharDead();

	// Method to get the position of the character


	Point2f getPosition() const;

	Point2f getPositionNonConst();

	float getFrameWidth();

	float GetFrameHeight();

	//method for taking dame
	float TakeDamageFromLava();


	Point2f SetPosition(const Point2f setPos);



private:

	Texture* m_Nyre_Texture;
	Texture* Deedlit_Conversation_Bubble;
	Texture* Karla_Texture;
	Texture* Deedlit_Conversation_Text;
	

	float
		m_ConvoBubbleX,
		m_ConvoBubbleY;

	int
		m_Cols, m_Rows;	
	float
		m_FrameSec, m_AccuSec;
	int
		m_ActFrame;
	float
		m_Scale, m_MoveSpeed=400, gravity, jumpVelocity;
    Point2f
		m_Position;

	Movement_States m_MoveDirection; // New member variable of type EnumClassMovedirection to store the current movement direction

	bool
		m_charHasFallenToLava,
		m_charIsTalking,
		m_isUsingAttackOne,
		m_isUsingAttackTwo,
		m_isUsingFlyingAttack,
		m_isJumpingAndMoving,
		m_isJumping,
		m_isFalling,
		m_isInLava,
		m_isDead,
		m_IsMovingLeft; // Boolean to let me know wether the character is moving left or not

	bool
		m_rdyAtckTwo,
		m_charReachedLeftBorder,
		m_charReachedRightBorder;


	//Use a vecvtor container to hold the conversation
	const int CONV_OPTION_SIZE{ 16 };
	std::vector<std::string> conversationOptions;
	std::string ConversationText;
	size_t m_ConversationOptionIndex = 0;

	//Struct has been created for the sake of refactoring the extremely redunt conversation code in the cpp file
	struct ConversationOption {
		 float frameWidth;
		float frameHeight;
		float srcRectY;
		std::vector<float> textOffsetX;
		std::vector<float> textOffsetY;
		float bubbleX;
		float bubbleY;
	};

		std::vector<ConversationOption> options;  //Conversation options
	std::vector<Texture*> conversationTextures; // Store pointers to Texture objects
	//	void CleanupTextures(); // Helper function to deallocate textures
};



