#include "pch.h"
#include "Character.h"
#include <iostream>
#include <string>

Character::Character(const std::string& filename, const int nrCols,const int nrRows, float scale, float frameSec)
    :m_Cols{ nrCols }, m_Rows{ nrRows }, m_FrameSec{ frameSec }, m_AccuSec{ 0 }, m_ActFrame{ 0 }, m_Scale{ scale }, m_isJumping{ false }, jumpVelocity{1000}, gravity{500}
{
    //conversationOptions[16];
    m_ConvoBubbleX = 600;
    m_ConvoBubbleY = m_Position.y + 220;

    std::cout << m_ConvoBubbleY << std::endl;
    m_charHasFallenToLava = false;
    m_charIsTalking = false;
    m_isUsingAttackOne = false;
    m_isUsingAttackTwo = false;
    m_isUsingFlyingAttack = false;
    m_rdyAtckTwo = false;
    m_Position.x = 0;
    m_Position.y = 90;
    m_charReachedLeftBorder =false;
    m_charReachedRightBorder = false;
    m_isJumpingAndMoving = false;
    m_isFalling = false;
    m_isInLava = false;
    m_isDead = false;
    m_Nyre_Texture = new Texture{ filename };
    Deedlit_Conversation_Bubble = new Texture{ "SourceImages/ConversationBubbles.png" };
    Karla_Texture = new Texture{ "SourceImages/Karla_Sprite_Sheet.png" };

    InitConversation();

    // Check if texture creation failed
      if (!m_Nyre_Texture->IsCreationOk()) 
    {
        std::cerr << "Failed to load texture: " << filename << std::endl;
    }


      //initialise the HUD
   //HudRef =   new HUD(100.f, 100.f, 1);
}

Character::Character(const Character& other)
    : m_Cols(other.m_Cols),
    m_Rows(other.m_Rows),
    m_FrameSec(other.m_FrameSec),
    m_AccuSec(other.m_AccuSec),
    m_ActFrame(other.m_ActFrame),
    m_Scale(other.m_Scale),
    m_MoveSpeed(other.m_MoveSpeed),
    gravity(other.gravity),
    jumpVelocity(other.jumpVelocity),
    m_Position(other.m_Position),
    m_MoveDirection(other.m_MoveDirection),
    m_charHasFallenToLava(other.m_charHasFallenToLava),
    m_charIsTalking(other.m_charIsTalking),
    m_isUsingAttackOne(other.m_isUsingAttackOne),
    m_isUsingAttackTwo(other.m_isUsingAttackTwo),
    m_isUsingFlyingAttack(other.m_isUsingFlyingAttack),
    m_isJumpingAndMoving(other.m_isJumpingAndMoving),
    m_isJumping(other.m_isJumping),
    m_isFalling(other.m_isFalling),
    m_isInLava(other.m_isInLava),
    m_isDead(other.m_isDead),
    m_IsMovingLeft(other.m_IsMovingLeft)
{


}

Character::~Character()
{

   // CleanupTextures();
}



void Character::InitConversation()
{
    // Handle the loading of the font
    const int fontSize{ 21 };
    const Color4f fontColor{ 1.0f, 1.0f, 1.0f, 1.0f };

    // Split the conversation option into two lines
    std::string conversationOption1 = "and soon, all will be forgotten,";
    std::string conversationOption2 = "leaving only death and destruction.";

    conversationOptions = {
        "Karla!",                                                                             //0
        "This unending battle...",                                                            //1
        "I know you're behind all this.",                                                     //2
        "I warned you about the 'trials' you'd face.",                                        //3
        "The history of Lodoss is a history of war.",                                         //4
        "The people scream holy oaths, \n while murdering each other,",                          //5
        "and soon, all will be forgotten, leaving only death and destruction.",               //6
        "Is that not so, immortal high elf?",                                                 //7
        "Shooting Star...?",                                                                  //8
        "Looking upon me not with fear, but with surprise...",                                //9
        "How hated I must be, elf girl.",                                                     //10
        "Fear me! Lament your fate! Weep in Agony!",                                          //11
        "Know the hopelessness of you vow, and confront me!",                                 //12
        "Wait!",                                                                              //13
        "I have no intention of fighting you...",                                             //14
        "Attack me, elf girl!"                                                                //15
    };

    //
    options = {
        {1080, 1080 / 8, 0, {40}, {120}, 240, 0},    // index 0
        {1080, 135, 270, {-120}, {120}, 240, 0},       // index 1
        {1080, 135, 270, {-120}, {120}, 240, 0},       // index 2
        {1080, 135, 675, {-120}, {120}, 240, 0},    // index 3
        {1080, 135, 675, {-120}, {120}, 240, 0},    // index 4
        {1080, 135, 405, {-60, -60}, {155, 179}, 240, 0},                                  // index 5, two lines
        {1080, 135, 405, {-60, -60}, {155, 179}, 240, 0},                                  // index 6, two lines
        {1080, 135, 405, {-60}, {155, 131}, 240, 0},// index 8, with 2 line handling
        {1080, 135, 120, {-30}, {110}, 640, 0},     // index 9
        {1080, 135, 120, {-90}, {100}, 640, 340},   // index 10
        {1080, 135, 120, {-90}, {100}, 640, 340},   // index 11
        {1080, 135, 120, {-90}, {100}, 640, 340},   // index 12
        {1080, 135, 120, {-90}, {100}, 640, 340},   // index 13
        {1080, 135, 120, {-90}, {100}, 640, 340},   // index 14
        {1080, 135, 120, {-90}, {100}, 640, 340},   // index 15
        {1080, 135, 120, {-90}, {100}, 640, 340}    // index 16
    };

    // Initialize with multiline text for option 8
    options[8].textOffsetX = { -60, -60 };  // X offsets for each line
   options[8].textOffsetY = { 155, 131 };  // Y offsets for each line
    // Initialize Deedlit_Conversation_Text with the first conversation option
    Deedlit_Conversation_Text = new Texture(conversationOptions[m_ConversationOptionIndex], "C:/Prog2/GitRepo/RecordOfLodossWar_Diestel_Johannes/SourceImages/consola.ttf", fontSize, fontColor);
    
}




void Character::IncrementConversationOptionIndex()
{
    const int fontSize{ 21 };
    const Color4f fontColor{ 1.0f, 1.0f, 1.0f, 1.0f };

    if (m_ConversationOptionIndex < CONV_OPTION_SIZE - 1)
    {
        ++m_ConversationOptionIndex;

        delete Deedlit_Conversation_Text;
        Deedlit_Conversation_Text = new Texture(conversationOptions[m_ConversationOptionIndex], "SourceImages/consola.ttf", fontSize, fontColor);
    }

    if (m_ConversationOptionIndex == 8)
    {
        if (IsInConversation())
        {
            EndConversation();

        }
        else if (m_ConversationOptionIndex < 9)
        {
            IncrementConversationOptionIndex();

            /*
            if (m_ConversationOptionIndex >= 15)
            {
               if (IsInConversation())

                    EndConversation();

            }
            */
        }
    }
    if (m_ConversationOptionIndex >= 15) {
        EndConversation();
    }
}

void Character::ShakeConversationBubble(float elapsedSec)
{
    // Define a small offset for the shaking effect
    const float shakeOffset = 2.0f;

    // Increment/decrement the bubble position within a small range
    m_ConvoBubbleX += shakeOffset * std::sin(2 * m_ConvoBubbleX * elapsedSec);
    if (m_ConvoBubbleX >= m_ConvoBubbleX + 2)
    {
        m_ConvoBubbleX -= shakeOffset * std::sin(2 * m_ConvoBubbleX * elapsedSec);
    }
    else  if (m_ConvoBubbleX <= m_ConvoBubbleX - 2)
    {
        m_ConvoBubbleX += shakeOffset * std::sin(2 * m_ConvoBubbleX * elapsedSec);
    }
}

void Character::update(float elapsedSec)
{

    //shake conversation  bubble.
    ShakeConversationBubble(elapsedSec);
    //update m_accusec and calculate the next frame
    //m_AccusSec represents the accumulated time since the last frame change
    MoveJump(elapsedSec);
    
    m_AccuSec += elapsedSec;
    //only if character is not in conversation
   // if (!m_charIsTalking)

    if (m_AccuSec > m_FrameSec)
    {
        m_AccuSec -= m_FrameSec;

        // Check if moving right or left
        if (m_MoveDirection == Movement_States::LEFT || m_MoveDirection == Movement_States::RIGHT)
        {
            // Cycle through the first 3 frames of the second row
            m_ActFrame++;
            if (m_ActFrame > 13)
            {
                m_ActFrame = 0;
            }
        }
        else if (m_MoveDirection == Movement_States::CROUCH)
        {
            m_ActFrame++;
            if (m_ActFrame > 0)
            {
                m_ActFrame = 0;
            }
        }
        else if (m_MoveDirection == Movement_States::JUMPMOVE && m_MoveDirection != Movement_States::FLYINGATTACKAIR)
        {
            m_ActFrame++;
            
            if (m_ActFrame >= 56 || m_ActFrame <= 43) // Keep the range between the second column of the 4th row, and the end of the 4th row.
            {
                m_ActFrame = 43;
              
            }

            
        }
      
        else if (m_isUsingAttackOne)
        {
            if (m_ActFrame < 70)
            {
                m_ActFrame++;
            }
            else if (m_ActFrame >= 70)
            {
                m_ActFrame = 57;
                m_ActFrame++;
            }
            if ( m_ActFrame <= 57)
            {
                m_ActFrame = 57;
         
            }
            else if (m_ActFrame >= 60 && m_ActFrame < 61)
            {
                m_rdyAtckTwo = true;
                m_isUsingAttackOne = false;
            }
            
        }
        else if (m_isUsingAttackTwo)
        {
            if (m_ActFrame < 70)
            {

                m_ActFrame++;
            }
            if (m_ActFrame <= 61)
            {
                m_ActFrame = 61;
            }
            else if (m_ActFrame >=  69)
            {
                m_MoveDirection = Movement_States::NONE;
                m_rdyAtckTwo = false;
                m_isUsingAttackTwo = false;
            }
           

        }
        else if (m_isUsingFlyingAttack)
        {
            m_ActFrame++;
            if (m_ActFrame <= 70)
            {
                m_ActFrame = 70;

            }
            else if (m_ActFrame >= 76)
            {
                m_MoveDirection = Movement_States::NONE;
                m_isUsingFlyingAttack = false;
                
            }
        }
        else if (m_isDead)
        {
            m_ActFrame++;
            {
                if (m_ActFrame <= 84)
                {
                    m_FrameSec = 0.09;
                    m_ActFrame = 84;
                }
                else if (m_ActFrame >= 90)
                {
                    m_ActFrame = 90;
                }
            }
        }
        else if (m_MoveDirection == Movement_States::NONE)
        {
            m_ActFrame++;

            if (m_ActFrame >= m_Cols)
            {
                m_ActFrame = 13;
            }

        }

       
        else
        {


          m_ActFrame++;

            if (m_ActFrame >= m_Cols)
            {
                m_ActFrame = 13;
            }

        }
       // std::cout << m_ActFrame << std::endl;
    }

    //Take damage if character is inside of the lava
    if (m_isInLava)
    {
     //  HudRef->TakeDamageFromChar();
      // HUD::AnyDamage();
    }
}

void Character::Draw()
{
   
   
 
    float frameWidth = 9562.0f / m_Cols; 
    float frameHeight = 4096.0f / m_Rows; 

    float karlaFrameWidth = (1080 * 5) / 5;
    float karlaFrameHeight = 1080;



    int currentRow = m_ActFrame / m_Cols;
    int currentCol = m_ActFrame % m_Cols;

    

    // Adjust the row if moving right or left
    if (m_MoveDirection == Movement_States::LEFT && !m_isJumping || m_MoveDirection == Movement_States::RIGHT && !m_isJumping)
    {
        // Set the row to the second row
        if(!m_isDead)
        currentRow = 1;
    }

    else if (m_MoveDirection == Movement_States::CROUCH && !m_isJumping)
    {
        // Set the row to the second row
        currentRow = 2;
        
    }
    else if (m_MoveDirection == Movement_States::JUMP || m_Position.y > 90 && m_MoveDirection != Movement_States::LEFT && m_MoveDirection != Movement_States::RIGHT && m_MoveDirection != Movement_States::FLYINGATTACKAIR)
    {
        // Set the row to the second row
       // if (m_MoveDirection != Movement_States::FLYINGATTACKAIR)
        if(!m_isUsingFlyingAttack)
        {
            currentRow = 3;
            currentCol = 0;
        }
        else
        {
            currentRow = 5;
        }
    }
    
    else if ((m_isJumping && m_MoveDirection == Movement_States::LEFT) || m_MoveDirection == Movement_States::RIGHT && m_MoveDirection != Movement_States::FLYINGATTACKAIR)
    {
        m_MoveDirection = Movement_States::JUMPMOVE;
        // Set the row to the second row   
       // if (m_MoveDirection != Movement_States::FLYINGATTACKAIR)
        if(!m_isUsingFlyingAttack)
        {
            currentRow = 3;
        }
        else
            currentRow = 5;
    }
    else if (m_MoveDirection == Movement_States::ATTACKONE)
    {
       // currentRow = 4;
    }
    else if (m_MoveDirection == Movement_States::FLYINGATTACKAIR)
    {
        currentRow = 5;
       // currentCol = 0;
    }
    else if (m_MoveDirection == Movement_States::DEATH || IsCharDead())
    {
        currentRow = 6;
    }

   
    float srcRectX = currentCol * frameWidth;
    float srcRectY = currentRow * frameHeight;

    //For Deedlit character
     // Set the source rectangle to select the first frame in the first row
    Rectf SrcRect{ srcRectX,  srcRectY, frameWidth, frameHeight };
    //Rectf destRect{pos.x, pos.y , frameWidth * float(0.8), frameHeight * float(0.8) };
    // Destination rectangle for rendering the sprite
   Rectf destRect{ m_Position.x, m_Position.y , frameWidth * float(0.8), frameHeight * float(0.8) };

        //For the KarlaCharacter
    Rectf karlaSrcRect{ 0,0,karlaFrameWidth,karlaFrameHeight };
    Rectf karlaDestRect{ 200, 80, karlaFrameWidth * float(0.215), karlaFrameHeight * float(0.215) };

    //Handling the flipping of the sprite.
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

   glTranslatef(m_Position.x + destRect.width/2, 0.f, 0.f);
    //glTranslatef(pos.x + destRect.width/2, 0.f, 0.f);
     glRotatef(m_IsMovingLeft ? 180.0f : 0.0f, 0.f, 1.f, 0.f);
    glTranslatef(-m_Position.x -destRect.width/2, 0.f, 0.f);
   // glTranslatef(-pos.x -destRect.width/2, 0.f, 0.f);

    m_Nyre_Texture->Draw(destRect, SrcRect);
    
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);    


    if (m_charIsTalking) 
    {
        const auto& opt = options[m_ConversationOptionIndex];
        Rectf convoSrcRect{ 0, opt.srcRectY, opt.frameWidth, opt.frameHeight };
        Rectf convoDestRect{ opt.bubbleX - 440, m_ConvoBubbleY + 65, opt.frameWidth, opt.frameHeight };
        if (m_ConversationOptionIndex <= 8)
        {
            Karla_Texture->Draw(karlaDestRect, karlaSrcRect);
        }
      
        Deedlit_Conversation_Bubble->Draw(convoDestRect, convoSrcRect);
        // Draw each line at specified offsets
        for (size_t i = 0; i < opt.textOffsetX.size(); ++i)
        {
            Deedlit_Conversation_Text->Draw(Point2f(opt.bubbleX + opt.textOffsetX[i], m_ConvoBubbleY + opt.textOffsetY[i]));
            //    conversationOptions[m_ConversationOptionIndex + i]);  // Ensure conversationOptions aligns correctly
        }
    }

   
    

 
}


void Character::MoveLeft(float elapsedSec)
{
    // Check if the character has reached the left border
    if (!m_charReachedLeftBorder )
    {
        // Move the character to the left until it reaches the screen edge
        m_Position.x -= m_MoveSpeed * elapsedSec;
       // if (m_Position.x <= 600)
        //     m_Position.x = 600;
    }
    else
    {
        // If the character has reached the left border, allow it to move freely
        m_Position.x -= m_MoveSpeed * elapsedSec;
    }

    m_MoveDirection = Movement_States::LEFT;
    SetMovingLeft(true);
    m_charReachedRightBorder = false;

}


void Character::MoveRight(float elapsedSec)
{
    // Check if the character has reached the left border
    if (!m_charReachedRightBorder)
    {
        // Move the character to the left until it reaches the screen edge
        m_Position.x += m_MoveSpeed * elapsedSec;
     //   if (m_Position.x >= 600)
       //     m_Position.x = 600;
    }
    else
    {
        // If the character has reached the left border, allow it to move freely
        m_Position.x += m_MoveSpeed * elapsedSec;
    }

    m_MoveDirection = Movement_States::RIGHT;
    SetMovingLeft(false);
    m_charReachedLeftBorder = false;

}
void Character::MoveJump(float elapsedSec)
{

    // Decrease jump velocity over time to simulate gravity
    jumpVelocity -= gravity * elapsedSec;

        if(m_isJumping)
    {
        // Move character vertically based on jump velocity
        m_Position.y += jumpVelocity * elapsedSec;
        // Decrease jump velocity over time to simulate gravity
        jumpVelocity -= gravity * elapsedSec;
       

        if (m_Position.y <= 90)
            {
                if (!m_isFalling)
                {
                    //m_Position.y = 0;
                
                
                
                    m_Position.y = 90; // Set character on the ground
                }
               // jumpVelocity = 0; // Reset jump velocity           
                m_isJumping = false;

        }
        
        
    }
    else if(m_charHasFallenToLava && m_Position.y >= 0)
    {
        // Move character vertically based on jump velocity
        m_Position.y += jumpVelocity * elapsedSec;
        // Decrease jump velocity over time to simulate gravity
        jumpVelocity -= gravity * elapsedSec;
    }

   


}

void Character::Jump()
{
    //if m_isJumping is false, set m_isJumping to true, and set the velocity to 100.f
    m_MoveDirection = Movement_States::JUMP;
    if (!m_isJumping)
    {
        m_isJumping = true;
        jumpVelocity = 500.f;


    }

}

bool Character::IsJumping()
{
    if (m_isJumping)
    {
        return true;
    }
    else
    {
        return false;
    }
}


//Allow the character to fall, based on platform position.
void Character::fall(float elapsedSec)
{
   
    // Decrease jump velocity over time to simulate gravity
   // jumpVelocity -= gravity * elapsedSec;
    if (m_Position.y ==90)
    {
    jumpVelocity -= gravity;
    }
    else
    {
        jumpVelocity -= gravity * elapsedSec;
    }
    m_isFalling = true;


        // Move character vertically based on jump velocity
       m_Position.y += jumpVelocity * elapsedSec;
     
            if (m_Position.y <= 0)
            {
               m_Position.y = 0; // Set character on the ground
                jumpVelocity = 0; // Reset jump velocity
                m_isInLava = true;
             
            }
            else
            {
                m_isInLava = false;
            }
   
  
}

void Character::CrouchDown()
{
    m_MoveDirection = Movement_States::CROUCH;
}

void Character::StopMoving()
{
   
        m_MoveDirection = Movement_States::NONE;   

}

void Character::AttackOne()
{
    m_MoveDirection = Movement_States::ATTACKONE;
    m_isUsingAttackOne = true;
    
}

void Character::AttackTwo()
{

    m_MoveDirection = Movement_States::ATTACKTWO;
    m_isUsingAttackTwo = true;

}

void Character::AtackFlyingAir()
{
    if(!m_isUsingFlyingAttack)
    m_MoveDirection = Movement_States::FLYINGATTACKAIR;
    m_isUsingFlyingAttack = true;
}

void Character::LeftBorderReached()
{
    m_charReachedLeftBorder = true;
 
}

void Character::RightBorderReached()
{
    m_charReachedRightBorder = true;
}

void Character::InitiateConversation()
{
    
    m_charIsTalking = true;
    if (!m_charIsTalking)
    {
        m_charIsTalking = true;
    } 

}

bool Character::IsInConversation()
{
    if (m_charIsTalking)
    {
        return true;
    }
    else if(!m_charIsTalking)
    {
        return false;
    }
}

void Character::EndConversation()
{
    m_charIsTalking = false;
  

}

bool Character::canUseAttackTwo()
{
    if (m_rdyAtckTwo)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Character::IsCharDead()
{
    /*
    if (HudRef->GetHealth() <= 0)
    {
        m_MoveDirection = Movement_States::DEATH;
        m_isDead = true;
        return true;
    }
    else
    {
       
        return false;
    }
    */
    return false;
}

Point2f Character::SetPosition(const Point2f setPos)
{
    return m_Position = setPos;
}


Point2f Character::getPosition() const
{
    return m_Position;
}

Point2f Character::getPositionNonConst()
{
    return m_Position;
}

float Character::TakeDamageFromLava()
{
    return 35.f;
}


/*
void Character::CleanupTextures()
{
    for (Texture* texture : conversationTextures) {
        delete texture; // Delete each dynamically allocated Texture
    }
    conversationTextures.clear(); // Clear the vector after deleting all textures

}
*/