//  *********************************************************************************
#pragma once
#include "errortype.h"
#include "windows.h"
#include "ObjectManager.h"
#include "event.h"
#include <list>


// For reading keyboard
#define KEYPRESSED(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

// For easier reading
typedef std::list<int> ScoreList ;


class Game
{
private:
	enum GameState{MENU, PAUSED, RUNNING, GAMEOVER, SCORESCREEN};
	GameState m_currentState;
	void ChangeState(GameState newState);
	int m_menuOption;
	Game();
	~Game();
	Game(Game& other);
 ScoreList list ;
 int m_latestScore ;
 bool m_scoreEnd ;

public:
	static Game instance;
	ObjectManager m_objects;
	ErrorType Setup(bool bFullScreen, HWND hwnd, HINSTANCE hinstance);
	void Shutdown();
	ErrorType Main();
	ErrorType PauseMenu();
	ErrorType MainMenu();
	ErrorType StartOfGame();
	ErrorType Update();
	ErrorType EndOfGame();
	void NotifyEvent(Event evt);
 void SetLatestScore(int score) ;
 int GetLatestScore() const ;
 void ScoreEnd(bool scoreEnd) ;
 int GetSize() const ;
 void ListBeginning() ;
};




