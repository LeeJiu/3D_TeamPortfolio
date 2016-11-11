#include "stdafx.h"
#include "cPlayer.h"
#include "cTerrain.h"
#include "cCamera.h"
#include "cInputHandler.h"


cPlayer::cPlayer()
{

}


cPlayer::~cPlayer()
{
	SAFE_DELETE(m_pInput);
}

void cPlayer::BaseObjectEnable()
{
	m_pInput = new cInputHandler;
	m_pInput->AddKey('1', new cTestCommand);
	m_pInput->AddKey('2', new cTestCommand2);

	//캐릭터의 그려진 위치를 세팅
	pTransform->SetWorldPosition(0, pTerrain->GetHeight(0, 0), 0);
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

void cPlayer::BaseObjectRender()
{
	this->pSkinned->Render(this->pTransform);
}