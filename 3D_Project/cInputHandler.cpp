#include "stdafx.h"
#include "cInputHandler.h"


cInputHandler::cInputHandler()
{
}


cInputHandler::~cInputHandler()
{
}

void cInputHandler::HandleInput()
{
	
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
