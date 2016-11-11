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
	SAFE_DELETE(m_pState);
}

void cMage::BaseObjectEnable()
{
	m_pInput = new cInputHandler;
	m_pInput->AddKey('1', new cTestCommand);
	m_pInput->AddKey('2', new cTestCommand2);

	m_pMove = new moveClass;
	//m_pMove->init(pSkinned, pTransform, pTerrain, m_camera);

	//캐릭터의 그려진 위치를 세팅
	pTransform->SetWorldPosition(0, pTerrain->GetHeight(0, 0), 0);

	m_state = STF_IDLE;
}

void cMage::BaseObjectUpdate(float timeDelta)
{
	cCommand* command = m_pInput->HandleInput();
	if (command != NULL)
	{
		command->Execute();
	}

	if (KEY_MGR->IsOnceDown('W'))
	{
		m_state = STF_WALK;
		m_current_Ani = SetAnimation(m_state);
		this->pSkinned->Play(m_current_Ani, 0.3);
	}
	if (KEY_MGR->IsStayDown('W'))
	{

	}
	if (KEY_MGR->IsOnceUp('W'))
	{
		m_state = STF_IDLE;
		m_current_Ani = SetAnimation(m_state);
		this->pSkinned->Play(m_current_Ani, 0.3);
	}


	if (KEY_MGR->IsOnceDown('S'))
	{
		m_state = STF_WALK_BACK;
		m_current_Ani = SetAnimation(m_state);
		this->pSkinned->Play(m_current_Ani, 0.3);
	}
	if (KEY_MGR->IsStayDown('S'))
	{

	}
	if (KEY_MGR->IsOnceUp('S'))
	{
		m_state = STF_IDLE;
		m_current_Ani = SetAnimation(m_state);
		this->pSkinned->Play(m_current_Ani, 0.3);
	}

	//if (KEY_MGR->IsStayDown('Q'))
	//{

	//}
	//if (KEY_MGR->IsStayDown('E'))
	//{

	//}

	if (KEY_MGR->IsOnceDown('A'))
	{
		m_state = STF_WALK;
		m_current_Ani = SetAnimation(m_state);
		this->pSkinned->Play(m_current_Ani, 0.3);
	}
	if (KEY_MGR->IsStayDown('A'))
	{
		
	}
	if (KEY_MGR->IsOnceUp('A'))
	{
		m_state = STF_IDLE;
		m_current_Ani = SetAnimation(m_state);
		this->pSkinned->Play(m_current_Ani, 0.3);
	}

	if (KEY_MGR->IsOnceDown('D'))
	{
		m_state = STF_WALK;
		m_current_Ani = SetAnimation(m_state);
		this->pSkinned->Play(m_current_Ani, 0.3);
	}
	if (KEY_MGR->IsStayDown('D'))
	{
		
	}
	if (KEY_MGR->IsOnceUp('D'))
	{
		m_state = STF_IDLE;
		m_current_Ani = SetAnimation(m_state);
		this->pSkinned->Play(m_current_Ani, 0.3);
	}
	
	//if (KEY_MGR->IsOnceUp('W') || KEY_MGR->IsOnceUp('S')
	//	|| KEY_MGR->IsOnceUp('Q') || KEY_MGR->IsOnceUp('E')
	//	|| KEY_MGR->IsOnceUp('A') || KEY_MGR->IsOnceUp('D'))
	//{
	//}
	
	if (KEY_MGR->IsOnceDown('P'))
	{
		m_pInput->SwapKey('1', '2');
	}
	//if (m_pMove)
	//	m_pMove->update(timeDelta, NULL);
}
