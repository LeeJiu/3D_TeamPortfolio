#include "stdafx.h"
#include "cPet.h"
#include "cTerrain.h"
#include "cCamera.h"


cPet::cPet()
{
}


cPet::~cPet()
{
	SAFE_DELETE(m_pMove);
}

void cPet::BaseObjectEnable()
{
	//캐릭터의 그려진 위치를 세팅
	pTransform->SetWorldPosition(0, pTerrain->GetHeight(0, 0), 0);
	D3DXVECTOR3	minPos(-1, 0, -1);
	D3DXVECTOR3	maxPos(1, 3, 1);
	BoundBox.Init(minPos, maxPos);

	m_state = IDLE;
	m_Aniname = SetAnimation(m_state);

	m_pMove = new moveClass;
	m_isMove = false;

	//무빙용으로 사용할 키값 세팅
	std::pair<int, bool> key_W('W', false);
	std::pair<int, bool> key_S('S', false);
	std::pair<int, bool> key_A('A', false);
	std::pair<int, bool> key_D('D', false);
	m_InputKeys.insert(key_W);
	m_InputKeys.insert(key_S);
	m_InputKeys.insert(key_A);
	m_InputKeys.insert(key_D);

	m_pMove->init(pTransform, pTerrain, m_camera, NULL);

}


void cPet::BaseObjectUpdate(float timeDelta)
{
	//애니메이션셋
	if ((KEY_MGR->IsOnceDown('W') || KEY_MGR->IsOnceDown('D')
		|| KEY_MGR->IsOnceDown('A')))
	{
		m_state = RUN;
		m_Aniname = SetAnimation(m_state);
		this->pSkinned->Play(m_Aniname, 0.3);
	}


	if (m_isMove && KEY_MGR->IsOnceDown('S'))
	{
		m_state = WALK;
		m_Aniname = SetAnimation(m_state);
		this->pSkinned->Play(m_Aniname, 0.3);
	}

	if (!m_isMove && (KEY_MGR->IsOnceUp('W') || KEY_MGR->IsOnceUp('S')
		|| KEY_MGR->IsOnceUp('Q') || KEY_MGR->IsOnceUp('E')
		|| KEY_MGR->IsOnceUp('A') || KEY_MGR->IsOnceUp('D')))
	{
		m_state = WAIT;
		m_Aniname = SetAnimation(m_state);
		this->pSkinned->Play(m_Aniname, 0.3);
	}


	LOG_MGR->AddLog("%s", m_Aniname.c_str());


	//===============무브==============================

	if (KEY_MGR->IsStayDown('W'))
	{
		m_InputKeys.find('W')->second = true;
	}
	else m_InputKeys.find('W')->second = false;


	if (KEY_MGR->IsStayDown('S'))
	{
		m_InputKeys.find('S')->second = true;
	}
	else m_InputKeys.find('S')->second = false;

	if (KEY_MGR->IsStayDown('A'))
	{
		m_InputKeys.find('A')->second = true;
	}
	else m_InputKeys.find('A')->second = false;

	if (KEY_MGR->IsStayDown('D'))
	{
		m_InputKeys.find('D')->second = true;

	}
	else m_InputKeys.find('D')->second = false;


	m_pMove->update(timeDelta, NULL, NULL, NULL, m_InputKeys);
	m_isMove = m_pMove->GetIsMove();
}
