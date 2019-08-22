 // GameCode.cpp		


// Version  13.03	Draw Engine no longer requires a height / width
// Version 13.0   Update to wchar_t and wstring

//Version 11			5/3/08	
// These three functions form the basis of a game loop in the window created in the
// wincode.cpp file

#include "gamecode.h"
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "myinputs.h"
#include <time.h>
#include "gametimer.h"
#include "errorlogger.h"
#include <math.h>
#include "shapes.h"
#include "ObjectManager.h"
#include "entities.h"
#include <list>

ErrorType Game::Main()
// Called repeatedly - the game loop
{
	//Flip and clear the back buffer
	MyDrawEngine* pTheDrawEngine= MyDrawEngine::GetInstance();
	pTheDrawEngine->Flip();
	pTheDrawEngine->ClearBackBuffer();

	ErrorType err;

	switch(m_currentState)
	{
	 case MENU:
  err = MainMenu() ;
  break ;

	 case PAUSED:
  err = PauseMenu() ;
	 break ;

	 case RUNNING:
	 err = Update() ;
	 break;

	 case GAMEOVER:
  err = FAILURE ;
  break;

	 default:
	 // Not a valid state
  err = FAILURE ;
	}

	return err;
}

void Game::ChangeState(GameState newState)
{
	// Very crude state system
	// Close old state
	switch(m_currentState)
	{
	 case MENU:
  break;

	 case PAUSED:
  break;

	 case RUNNING:
	 break;
	}

	// Change the state
	m_currentState = newState;
	m_menuOption = 0;

	// Transition to new state
	switch(m_currentState)
	{
	 case MENU:
		break;

	 case PAUSED:
		break;

	 case RUNNING:
		break;
	}
}

ErrorType Game::Setup(bool bFullScreen, HWND hwnd, HINSTANCE hinstance)
// Called once before entering game loop. 
{
	// Create the engines - this should be done before creating other DDraw objects
	if(FAILED(MyDrawEngine::Start(hwnd, bFullScreen)))
	{
		ErrorLogger::Writeln(L"Failed to start MyDrawEngine");
		return FAILURE;
	}
	if(FAILED(MySoundEngine::Start(hwnd)))
	{
		ErrorLogger::Writeln(L"Failed to start MySoundEngine");
		return FAILURE;
	}
	if(FAILED(MyInputs::Start(hinstance, hwnd)))
	{
		ErrorLogger::Writeln(L"Failed to start MyInputs");
		return FAILURE;
	}
	return (SUCCESS);
}

void Game::Shutdown()
// Called once before entering game loop. 
{
	m_objects.DeleteAllObjects();

	// (engines must be terminated last)
	MyDrawEngine::Terminate();
	MySoundEngine::Terminate();
	MyInputs::Terminate();
}
// **********************************************************************************************
// The game !!! *********************************************************************************
// **********************************************************************************************



ErrorType Game::PauseMenu()
{
	// Code for a basic pause menu
 MyDrawEngine::GetInstance()->theCamera.PlaceAt(Vector2D(0,0));
 MyDrawEngine::GetInstance()->DrawAt(Vector2D(0,0), 1, 1.0f, 0.0f, 0.0f);


	const int NUMOPTIONS = 2;
	wchar_t options[NUMOPTIONS][11] = {L"Resume", L"Main menu"};

	for(int i = 0; i < NUMOPTIONS; i++)
	{
		int colour = MyDrawEngine::GREY;
		if(i == m_menuOption)
		{
			colour = MyDrawEngine::WHITE;
		}

		MyDrawEngine::GetInstance()->WriteText(825,585+50*i, options[i], colour, 1);
	}

	MyInputs* pInputs = MyInputs::GetInstance();

	pInputs->SampleKeyboard() ;
	if(pInputs->NewKeyPressed(DIK_UP))
	{
		m_menuOption--;
	}
	if(pInputs->NewKeyPressed(DIK_DOWN))
	{
		m_menuOption++;
	}
	if(m_menuOption < 0)
	{
		m_menuOption=0;
	}
	else if(m_menuOption>=NUMOPTIONS)
	{
		m_menuOption = NUMOPTIONS - 1;
	}

	if(pInputs->NewKeyPressed(DIK_RETURN))
	{
		if(m_menuOption == 0)
		{
			ChangeState(RUNNING);
		}
		if(m_menuOption == 1)
		{
			EndOfGame();
			ChangeState(MENU);
		}

	}

	return SUCCESS;
}

ErrorType Game::MainMenu()
{
	// Code for a basic main menu
 MyDrawEngine* pDrawEngine = MyDrawEngine::GetInstance() ;
 pDrawEngine->theCamera.PlaceAt(Vector2D(0,0)) ;
 pDrawEngine->AddFont(L"Calibri", 35, false, false) ;
 pDrawEngine->AddFont(L"Calibri", 60, false, false) ;
 pDrawEngine->LoadPicture(L"title.bmp") ;
 pDrawEngine->LoadPicture(L"gameover.bmp") ;
 pDrawEngine->DrawAt(Vector2D(0,0), 1, 1.0f, 0.0f, 0.0f) ;

	const int NUMOPTIONS = 3 ;
	wchar_t options[NUMOPTIONS][20] = {L"Start Game", L"Go Fullscreen", L"Quit to Desktop"} ;

	if(MyDrawEngine::GetInstance()->IsWindowFullScreen())
 {
	 wcscpy_s(options[1], 20, L"Go Windowed") ;
	}

	for(int i = 0; i < NUMOPTIONS; i++)
	{
	 int colour = MyDrawEngine::GREY ;

  if(i == m_menuOption)
  {
	  colour = MyDrawEngine::WHITE ;
	 }

	MyDrawEngine::GetInstance()->WriteText(825,585+50*i, options[i], colour, 1) ;
	}

	MyInputs* pInputs = MyInputs::GetInstance() ;

	pInputs->SampleKeyboard() ;

	if(pInputs->NewKeyPressed(DIK_UP))
	{
		m_menuOption-- ;
	}
	if(pInputs->NewKeyPressed(DIK_DOWN))
	{
		m_menuOption++ ;
	}
	if(m_menuOption < 0)
	{
		m_menuOption = 0 ;
	}
	else if(m_menuOption >= NUMOPTIONS)
	{
		m_menuOption = NUMOPTIONS - 1 ;
	}

	if(pInputs->NewKeyPressed(DIK_RETURN))
	{
		if(m_menuOption == 0)
		{
			StartOfGame() ;
			ChangeState(RUNNING) ;
		}

		if(m_menuOption == 1)
		{
			if(MyDrawEngine::GetInstance()->IsWindowFullScreen())
			{
				MyDrawEngine::GetInstance()->GoWindowed() ;
			}
			else
			{
				MyDrawEngine::GetInstance()->GoFullScreen() ;
			}
		}
		if(m_menuOption == 2)
		{
			ChangeState(GAMEOVER) ;
		}
	}

	return SUCCESS;
}

ErrorType Game::StartOfGame()
{
 // Make sure the game can access the scoreboard.
 ScoreEnd(false) ;

 // Create objects
 SoundFX* pSound = new SoundFX() ;
 m_objects.AddItem(pSound, false) ;

	Health* pHealth = new Health ;
	pHealth->Initialise(Vector2D(-1235, 800), 876.0f) ;
	m_objects.AddItem(pHealth, false) ;

	Fuel* pFuel = new Fuel ;
	pFuel->Initialise(Vector2D(-1235, 800), 876.0f, pSound) ;
	m_objects.AddItem(pFuel, false) ;

	Ammunition* pAmmunition = new Ammunition ;
	pAmmunition->Initialise(Vector2D(-1235, 800), 876.0f) ;
	m_objects.AddItem(pAmmunition, false) ;

	Fragments* pFragments = new Fragments();
	m_objects.AddItem(pFragments, false);

	Ship* pShip = new Ship ;
	GameManager* pGameManager = new GameManager;
	pShip->Initialise(Vector2D(0, 0), pHealth, pFuel, pAmmunition, pSound, pGameManager) ;
	pGameManager->Initialise(pShip, pSound);
	m_objects.AddItem(pShip, true) ;
	m_objects.AddItem(pGameManager, false);

	return SUCCESS;
} 

ErrorType Game::Update()
{
	m_objects.UpdateAll();
	m_objects.ProcessCollisions();
	m_objects.DrawAll();

	// Garbage collect any objects. Possibly slow
	m_objects.DeleteInactiveItems();

	// Check for entry to pause menu
	static bool escapepressed = true ;

	if(KEYPRESSED(VK_ESCAPE))
	{
		if(!escapepressed)
  {
			ChangeState(PAUSED) ;
  }
		escapepressed = true ;
	}
	else
 {
		escapepressed = false ;
 }








	// Ended the scoreboard and started new game etc.
	static bool scoreboard = true ;

	if(m_scoreEnd)
	{
		if(!scoreboard)
  {
			ChangeState(MENU) ;
  }
		scoreboard = true ;
	}
	else
 {
		scoreboard = false ;
 }

	// Any code here to run the game,
	// but try to do this within a game object if possible

	return SUCCESS;
}

ErrorType Game::EndOfGame()
// called when the game ends by returning to main menu
{
	// Add code here to tidy up ********************************
	
	m_objects.DeleteAllObjects();

	return SUCCESS;
}

Game::Game()
{
 // No-op
}

Game::~Game()
{
 // No-op
}

void Game::NotifyEvent(Event evt)
{
	m_objects.HandleEvent(evt);
}

void Game::SetLatestScore(int score)
{
 m_latestScore = score ;
 list.push_back(score) ;
}

int Game::GetLatestScore() const 
{
 return m_latestScore ;
}

void Game::ScoreEnd(bool scoreEnd)
{
 m_scoreEnd = scoreEnd ;
}

int Game::GetSize() const
{
 return list.size() ;
}

void Game::ListBeginning() 
{
 list.sort() ;
 list.reverse() ;
 MyDrawEngine* pDrawEngine = MyDrawEngine::GetInstance() ;
 int iterate = 0 ;

 for (std::list<int>::const_iterator i = list.begin(), end = list.end(); i != end; ++i)
 {
  pDrawEngine->WriteInt(Vector2D(-285,-360-45*iterate), *i, _XRGB(246, 255, 144), 0) ;
  iterate++ ;
 }
}

Game Game::instance;