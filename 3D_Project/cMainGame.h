#pragma once

class cImage;			//이런클래스가 있다
class cScene;

#define _WIN32_WINNT 0x400
#define _WIN32_WINDOWS 0x401

class cMainGame
{
private:	


public:
	cMainGame(void);
	~cMainGame(void);

	//셋팅
	HRESULT Init(void);

	//해제
	void Release();

	//업데이트
	void Update();

	//드로우
	void Draw();

	//휠
	void OnMouseWheel(HWND hWnd, WPARAM wParam, LPARAM lParam);
public:

	//프로시져
	LRESULT MainProc( HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam );

};
