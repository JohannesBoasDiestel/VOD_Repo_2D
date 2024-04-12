#include "pch.h"
#include "Game.h"

Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize()
{
	int screenWidth = 1900.f;
	int screenHeight = 1000.f;
	// Set viewport width and height to match screen resolution
	float viewportWidth = static_cast<float>(screenWidth);
	float viewportHeight = static_cast<float>(screenHeight);

	m_Nyre = new Character("SourceImages/Deedlit_SpriteSheet_LARGE_V2.png", 14, 8, 1, 0.05f);
	m_Background = new Background("SourceImages/Dragon_Level_BackRound.png", *m_Nyre, 1.3f);
	m_Camera = new Camera(*m_Nyre, *m_Background, viewportWidth, viewportHeight);


	//Initalize position
	Point2f GetAbsolutePositionRef {m_Camera->GetAbsoluteReferenceX()+1000, m_Camera->GetAbsoluteReferenceY()};
	m_Nyre->SetPosition(GetAbsolutePositionRef);
	
}

void Game::Cleanup( )
{
}

void Game::Update( float elapsedSec )
{

	m_Nyre->update(elapsedSec);
	m_Background->Update(elapsedSec);
	// Check keyboard state
	//const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}

	const Uint8* pStates = SDL_GetKeyboardState(nullptr);

	if (!m_Nyre->IsCharDead())
	{
		// Check if the left arrow key is pressed
		if (pStates[SDL_SCANCODE_LEFT] && !m_Nyre->IsInConversation() /* && !testBackground->Check_Mid_PF_Border_Coll_Right_Side(camera->GetPositionPoint2F(), m_Nyre->getPosition())*/)
		{
			// Move the character and camera to the left
			m_Nyre->MoveLeft(elapsedSec);
			m_Camera->MoveLeft(elapsedSec);

		}
		// Check if the right arrow key is pressed
		else if (pStates[SDL_SCANCODE_RIGHT] && !m_Nyre->IsInConversation() /* && !testBackground->Check_PF_Left_Side_Collisions(camera->GetPositionPoint2F(), m_Nyre->getPosition())*/)
		{
			// Move the character and camera to the right			
			m_Nyre->MoveRight(elapsedSec);
		    m_Camera->MoveRight(elapsedSec);
		}
		else if (pStates[SDL_SCANCODE_DOWN] && !m_Nyre->IsInConversation())
		{
			m_Nyre->CrouchDown();
		}
		else if (pStates[SDL_SCANCODE_X] && !m_Nyre->IsInConversation())
		{
			m_Nyre->Jump();
		}


		else
		{
			m_Nyre->StopMoving();
		}
	}


	// Update the camera to adjust the background position
	m_Camera->update(elapsedSec);
}

void Game::Draw( ) const
{
	ClearBackground( );


	m_Background->Draw();
	m_Nyre->Draw();


}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
