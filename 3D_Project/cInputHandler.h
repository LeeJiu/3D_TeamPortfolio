#pragma once
#include "cCommand.h"

class cInputHandler
{
public:
	cInputHandler();
	~cInputHandler();

	cCommand* HandleInput();
	void AddKey(int nVKey, cCommand* command);		//VK값과 command를 등록한다.
	void ReSetKey(int nVKey, cCommand* command);		//VK값과 command를 변경.
	void DeleteKey(int nVKey);						//해당 키를 삭제한다.
	void ChangeKey(int nVKey, cCommand* command);	//키와 커맨드를 변경한다.
	void SwapKey(int nFromVKey, int nToVKey);

private:
	map<int, cCommand*>				m_mKey;			//int형-key, cCommand*형 command-value 을 저장한다.
	map<int, cCommand*>::iterator	m_miKey;
};
