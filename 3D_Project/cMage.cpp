#include "stdafx.h"
#include "cMage.h"
#include "cTerrain.h"
#include "cCamera.h"
#include "cInputHandler.h"

cMage::cMage()
{

}


cMage::~cMage()
{
	SAFE_DELETE(m_pInput);
	SAFE_DELETE(m_pMove);
}

void cMage::BaseObjectEnable()
{
	m_pInput = new cInputHandler;
	m_pInput->AddKey('1', new cTestCommand);
	m_pInput->AddKey('2', new cTestCommand2);
	
	//캐릭터의 그려진 위치를 세팅
	pTransform->SetWorldPosition(0, pTerrain->GetHeight(0, 0), 0);

	m_state = STF_IDLE;
	m_Aniname = SetAnimation(m_state);
	m_pMove = new moveClass;
	m_pMove->init(pTransform, pTerrain, m_camera);
}

void cMage::BaseObjectUpdate(float timeDelta)
{

	cCommand* command = m_pInput->HandleInput();
	if (command != NULL)
	{
		command->Execute();
	}

	//애니메이션셋
	m_current_Ani = pSkinned->GetNowPlaying();
	//m_isMove = m_pMove->GetIsMove();

	if ((KEY_MGR->IsOnceDown('W') || KEY_MGR->IsOnceDown('D')
		|| KEY_MGR->IsOnceDown('A')))
	{
		m_state = STF_WALK;
		m_Aniname = SetAnimation(m_state);
		if (m_current_Ani != SetAnimation(m_state))
		{
			this->pSkinned->Play(m_Aniname, 0.3);
		}
	}

	
	if (m_isMove && KEY_MGR->IsOnceDown('S'))
	{
		m_state = STF_WALK_BACK;
		m_Aniname = SetAnimation(m_state);
		if (m_current_Ani != SetAnimation(m_state))
		{
			this->pSkinned->Play(m_Aniname, 0.3);
		}
	}

	if ((KEY_MGR->IsOnceUp('W') || KEY_MGR->IsOnceUp('S')
		|| KEY_MGR->IsOnceUp('Q') || KEY_MGR->IsOnceUp('E')
		|| KEY_MGR->IsOnceUp('A') || KEY_MGR->IsOnceUp('D')))
	{
		m_state = STF_IDLE;
		m_Aniname = SetAnimation(m_state);
		if (m_current_Ani != SetAnimation(m_state))
		{
			this->pSkinned->Play(m_Aniname, 0.3);
		}
	}

	

	//===============무브==============================
	
	m_pMove->update(timeDelta, NULL, NULL, NULL);

	if (KEY_MGR->IsOnceDown('P'))
	{
		m_pInput->SwapKey('1', '2');
	}

}
