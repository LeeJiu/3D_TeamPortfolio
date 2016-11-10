#include "stdafx.h"
#include "cMoveState.h"
#include "cTransform.h"
#include "cTerrain.h"


cMoveState::cMoveState(cBaseObject* pActor, ACTOR_STATE* pState)
{
	m_pState = pState;
	m_pAnim = pActor->GetSkinnedAnim();
	m_pCharTrans = pActor->pTransform;
	m_pTerrain = pActor->GetTerrain();

	m_bMove = false;
	//================���� �߰�. �Ʒ� ���� �ٲ��� ���� .
	m_moveRay.direction = D3DXVECTOR3(0, -1, 0);
	m_moveRay.origin = m_pCharTrans->GetWorldPosition();
	//isClick = false;
}


cMoveState::~cMoveState()
{
}

void cMoveState::Enter(int nNum)
{
	m_VKey = nNum;
	m_pAnim->Play("Walk", 0.3f);
}

void cMoveState::Execute()
{
	// ���� ������Ʈ 
	m_currentPos = m_pCharTrans->GetWorldPosition(); // ���� ��ġ. 
	m_moveRay.origin.y = m_pCharTrans->GetWorldPosition().y + 5; // �Ӹ����� ���Ͽ���

	switch (m_VKey)
	{
	case 'W':
		m_bMove = true;
		m_moveRay.origin += m_pCharTrans->GetForward() * 0.2f;
		break;
	case 'S':
		m_bMove = true;
		m_moveRay.origin -= m_pCharTrans->GetForward() * 0.2f;
		break;
	case 'Q':
		m_bMove = true;
		m_moveRay.origin -= m_pCharTrans->GetRight() * 0.2f;
		break;
	case 'E':
		m_bMove = true;
		m_moveRay.origin += m_pCharTrans->GetRight() * 0.2f;
		break;
	case 'A':
		m_pCharTrans->RotateSelf(0, -2 * ONE_RAD, 0);
		break;
	case 'D':
		m_pCharTrans->RotateSelf(0, 2 * ONE_RAD, 0);
		break;
	default:
		Exit();
		return;
	}

	// �ͷ��ΰ� �浹 �ߴٸ�. 
	if (m_pTerrain->IsIntersectRay(&m_prePos, &m_moveRay) == true)
	{
		if (m_lastPos.y > m_prePos.y)
		{
			m_prePos = m_lastPos;
		}
	}

	//=================================== �ɸ��͸� ���������� �����̰� �ϴ� �κ� 
	if (fabs(m_prePos.y - m_currentPos.y) < 0.5f && m_bMove == true) // ���ڴ� �Ѿ �� �ִ� ����. ( �Ʒ����� ���� ����. )
	{
		m_pCharTrans->SetWorldPosition(m_prePos);
		m_currentPos = m_prePos; // ��ǥ ����
	}
	// ���̶� �ɸ��� �Ÿ��� �־����� ���̰� ���̻� �Ѿ�� ���ϰ� �����.
	float rayCheckDis = D3DXVec3Length(&(m_moveRay.origin - m_pCharTrans->GetWorldPosition()));
	if (rayCheckDis > 0.25f) // ��� ���� �ӷ� ���� ���� ���� ��.
	{
		m_moveRay.origin = m_pCharTrans->GetWorldPosition();
		m_moveRay.origin.y = m_pCharTrans->GetWorldPosition().y + 5; // �Ӹ����� ���Ͽ���
	}

	//m_bMove = false;
	//=================================== �ɸ��͸� ���������� �����̰� �ϴ� �κ�  ��.
}

void cMoveState::Exit()
{
	*m_pState = AS_IDLE;
	m_bMove = false;
}
