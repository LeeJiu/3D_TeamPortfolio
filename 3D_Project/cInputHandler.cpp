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

	//�ƹ��͵� ������ �ʾҴٸ�
	return NULL;
}

void cInputHandler::AddKey(int nVKey, cCommand * command)
{
	m_mKey.insert(pair<int, cCommand*>(nVKey, command));
}

void cInputHandler::DeleteKey(int nVKey)
{
	//�ش� Ű���� �ִٸ�
	if(m_mKey.find(nVKey) != m_mKey.end())
		m_mKey.erase(nVKey);
}

void cInputHandler::ChangeKey(int nVKey, cCommand * command)
{
	//�ش� Ű���� �ִٸ�
	if (m_mKey.find(nVKey) != m_mKey.end())
	{
		m_mKey[nVKey] = command;
	}
	//�ش� Ű���� ���ٸ�
	else
	{
		m_mKey.insert(pair<int, cCommand*>(nVKey, command));
	}
}
