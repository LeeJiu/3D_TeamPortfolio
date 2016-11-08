#include "stdafx.h"
#include "cInputHandler.h"


cInputHandler::cInputHandler()
{
}


cInputHandler::~cInputHandler()
{
	//for (m_miKey = m_mKey.begin(); m_miKey != m_mKey.end();)
	//{
	//	//���߿� Ŀ��� �߿� ������ �Ұ� �����
	//	//������ ���Ѿ� �Ѵ�.
	//}

	m_mKey.clear();
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

void cInputHandler::SwapKey(int nFromVKey, int nToVKey)
{
	//�ش� Ű���� �ִٸ�
	if (m_mKey.find(nFromVKey) != m_mKey.end())
	{
		cCommand* tempCommand = m_mKey.find(nFromVKey)->second;

		ChangeKey(nFromVKey, m_mKey.find(nToVKey)->second);
		ChangeKey(nToVKey, tempCommand);
	}
}
