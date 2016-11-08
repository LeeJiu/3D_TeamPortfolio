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
	//================레이 추가. 아래 방향 바뀌지 않음 .
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
	// 레이 업데이트 
	m_currentPos = m_pCharTrans->GetWorldPosition(); // 현재 위치. 
	m_moveRay.origin.y = m_pCharTrans->GetWorldPosition().y + 5; // 머리위에 붙일예정

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

	// 터레인과 충돌 했다면. 
	if (m_pTerrain->IsIntersectRay(&m_prePos, &m_moveRay) == true)
	{
		if (m_lastPos.y > m_prePos.y)
		{
			m_prePos = m_lastPos;
		}
	}

	//=================================== 케릭터를 최종적으로 움직이게 하는 부분 
	if (fabs(m_prePos.y - m_currentPos.y) < 0.5f && m_bMove == true) // 숫자는 넘어갈 수 있는 높이. ( 아래에서 위로 갈떄. )
	{
		m_pCharTrans->SetWorldPosition(m_prePos);
		m_currentPos = m_prePos; // 좌표 갱신
	}
	// 레이랑 케릭터 거리가 멀어지면 레이가 더이상 넘어가지 못하게 만든다.
	float rayCheckDis = D3DXVec3Length(&(m_moveRay.origin - m_pCharTrans->GetWorldPosition()));
	if (rayCheckDis > 0.25f) // 상수 값은 속력 보다 조금 높은 값.
	{
		m_moveRay.origin = m_pCharTrans->GetWorldPosition();
		m_moveRay.origin.y = m_pCharTrans->GetWorldPosition().y + 5; // 머리위에 붙일예정
	}

	//m_bMove = false;
	//=================================== 케릭터를 최종적으로 움직이게 하는 부분  끗.
}

void cMoveState::Exit()
{
	*m_pState = AS_IDLE;
	m_bMove = false;
}
