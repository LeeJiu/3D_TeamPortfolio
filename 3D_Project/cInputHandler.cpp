#include "stdafx.h"
#include "cInputHandler.h"


cInputHandler::cInputHandler()
{
}


cInputHandler::~cInputHandler()
{
	//for (m_miKey = m_mKey.begin(); m_miKey != m_mKey.end();)
	//{
	//	//나중에 커멘드 중에 릴리즈 할게 생기면
	//	//릴리즈 시켜야 한다.
	//}

	m_mKey.clear();
}

cCommand* cInputHandler::HandleInput()
{
	for (m_miKey = m_mKey.begin(); m_miKey != m_mKey.end(); ++m_miKey)
	{
		if (KEY_MGR->IsOnceDown(m_miKey->first)) return m_miKey->second;
	}

	//아무것도 눌리지 않았다면
	return NULL;
}

void cInputHandler::AddKey(int nVKey, cCommand * command)
{
	m_mKey.insert(pair<int, cCommand*>(nVKey, command));
}

void cInputHandler::DeleteKey(int nVKey)
{
	//해당 키값이 있다면
	if(m_mKey.find(nVKey) != m_mKey.end())
		m_mKey.erase(nVKey);
}

void cInputHandler::ChangeKey(int nVKey, cCommand * command)
{
	//해당 키값이 있다면
	if (m_mKey.find(nVKey) != m_mKey.end())
	{
		m_mKey[nVKey] = command;
	}
	//해당 키값이 없다면
	else
	{
		m_mKey.insert(pair<int, cCommand*>(nVKey, command));
	}
}

void cInputHandler::SwapKey(int nFromVKey, int nToVKey)
{
	//해당 키값이 있다면
	if (m_mKey.find(nFromVKey) != m_mKey.end())
	{
		cCommand* tempCommand = m_mKey.find(nFromVKey)->second;

		ChangeKey(nFromVKey, m_mKey.find(nToVKey)->second);
		ChangeKey(nToVKey, tempCommand);
	}
}
