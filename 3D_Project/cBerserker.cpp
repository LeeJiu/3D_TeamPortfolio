#include "stdafx.h"
#include "cBerserker.h"
#include "cTerrain.h"
#include "cCamera.h"
#include "cInputHandler.h"


cBerserker::cBerserker()
{
}

cBerserker::~cBerserker()
{
	SAFE_DELETE(m_pInput);
	SAFE_DELETE(m_pMove);
	SAFE_DELETE(m_attak1);
	SAFE_DELETE(m_attak2);
	SAFE_DELETE(m_attak3);
}


void cBerserker::BaseObjectEnable()
{
	m_pInput = new cInputHandler;

	//ĳ������ �׷��� ��ġ�� ����
	pTransform->SetWorldPosition(0, pTerrain->GetHeight(0, 0), 0);
	D3DXVECTOR3	minPos(-1, 0, -1);
	D3DXVECTOR3	maxPos(1, 3, 1);

	m_state = IDLE;
	m_Aniname = SetAnimation(m_state);

	m_pMove = new moveClass;
	m_isMove = false;

	m_attak1 = new cBerserKer_Attack;
	m_attak2 = new cBerserKer_Attack2;
	m_attak3 = new cBerserKer_Attack3;
	m_isAttack = false;

	//���������� ����� Ű�� ����
	std::pair<int, bool> key_W('W', false);		//WŰ �ȴ���	����
	std::pair<int, bool> key_S('S', false);		//SŰ �ȴ���  " 
	std::pair<int, bool> key_A('A', false);		//AŰ �ȴ���  "
	std::pair<int, bool> key_D('D', false);		//DŰ �ȴ���  "
	std::pair<int, bool> key_1('1', false);
	m_InputKeys.insert(key_W);
	m_InputKeys.insert(key_S);
	m_InputKeys.insert(key_A);
	m_InputKeys.insert(key_D);
	m_InputKeys.insert(key_1);


	m_pMove->init(pTransform, pTerrain, m_camera, NULL);

	m_atkCnt = 1;
	m_time = 0;
	m_testtime = 0;
}

void cBerserker::BaseObjectUpdate(float timeDelta)
{

	cCommand* command = m_pInput->HandleInput();
	if (command != NULL)
	{
		command->Execute();
	}

	//�ִϸ��̼Ǽ�
	m_fadeOut = pSkinned->GetTime();

	if (m_isMove && (KEY_MGR->IsOnceDown('W') || KEY_MGR->IsOnceDown('D')
		|| KEY_MGR->IsOnceDown('A')))
	{
		m_state = WALK;
		m_Aniname = SetAnimation(m_state);
		this->pSkinned->Play(m_Aniname, 0.3);
	}


	if (m_isMove && KEY_MGR->IsOnceDown('S'))
	{
		m_state = WALK_BACK;
		m_Aniname = SetAnimation(m_state);
		this->pSkinned->Play(m_Aniname, 0.3);
	}

	if ((!m_isMove && (KEY_MGR->IsOnceUp('W') || KEY_MGR->IsOnceUp('S')
		|| KEY_MGR->IsOnceUp('Q') || KEY_MGR->IsOnceUp('E')
		|| KEY_MGR->IsOnceUp('A') || KEY_MGR->IsOnceUp('D'))))
	{
		m_state = IDLE;
		m_Aniname = SetAnimation(m_state);
		this->pSkinned->Play(m_Aniname, 0.3);
	}	

	m_time += timeDelta;
	m_testtime += timeDelta;

	if (!m_isAttack && KEY_MGR->IsOnceDown('1'))
	{
		m_InputKeys.find('1')->second = true;
		m_isAttack = true;
		m_time = 0;
		switch (m_atkCnt)
		{
			case 1 : 
				m_state = ATK_01;
				m_attak1->Execute();
				m_atkCnt++;
				break;
		
			case 2: 
				m_state = ATK_02;
				m_attak2->Execute();
				m_atkCnt++;
				break;
			case 3: 
				m_state = ATK_03;
				m_attak3->Execute();
				m_atkCnt = 1;
				break;
		}
		m_Aniname = SetAnimation(m_state);
		this->pSkinned->PlayOneShotAFTERIDLE(m_Aniname, 0.3);
	}
	
	//���� 1��
	if (m_time > 1)
		m_isAttack = false;

	//��Ÿ �ʱ�ȭ�ð�
	if (m_time > 5)
		m_atkCnt = 1;

	if (m_testtime > 1)
	{
		LOG_MGR->AddLog("%f, %d, %d", (1 - m_fadeOut), m_isAttack, m_isAttack);
		m_testtime = 0;
	}
	
	//===============����==============================

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

	//if (KEY_MGR->IsOnceDown('P'))
	//{
	//	m_pInput->SwapKey('1', '2');
	//}

}
