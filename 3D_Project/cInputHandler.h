#pragma once
#include "cCommand.h"
#include <map>

class cInputHandler
{
public:
	cInputHandler();
	~cInputHandler();

	void HandleInput();
	void AddKey(int nVKey, cCommand* command);		//VK���� command�� ����Ѵ�.
	void DeleteKey(int nVKey);						//�ش� Ű�� �����Ѵ�.
	void ChangeKey(int nVKey, cCommand* command);	//Ű�� Ŀ�ǵ带 �����Ѵ�.

private:
	map<int, cCommand*>		m_mKey;					//int��-key, cCommand*�� command-value �� �����Ѵ�.
};

