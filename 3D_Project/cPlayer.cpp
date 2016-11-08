#include "stdafx.h"
#include "cPlayer.h"
#include "cTerrain.h"
#include "cCamera.h"
#include "cInputHandler.h"


cPlayer::cPlayer()
{
	m_pInput = new cInputHandler;
	m_pInput->AddKey('1', new cTestCommand);
	m_pInput->AddKey('2', new cTestCommand2);
}


cPlayer::~cPlayer()
{
	SAFE_DELETE(m_pInput);
}

void cPlayer::BaseObjectUpdate(float timeDelta)
{
	cCommand* command = m_pInput->HandleInput();
	if (command != NULL)
	{
		command->Execute();
	}


	if (KEY_MGR->IsOnceDown('P'))
	{
		//m_pInput->ChangeKey('3', new cTestCommand);	//없으면 추가된다.
		//m_pInput->DeleteKey('1');
		m_pInput->SwapKey('1', '2');
	}
}
