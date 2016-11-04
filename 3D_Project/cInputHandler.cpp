#include "stdafx.h"
#include "cInputHandler.h"


cInputHandler::cInputHandler()
{
}


cInputHandler::~cInputHandler()
{
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
