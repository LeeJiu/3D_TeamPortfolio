#include "stdafx.h"
#include "moveClass.h"
#include "cTransform.h"
#include "cSkinnedAnimation.h"
#include "cTerrain.h"

moveClass::moveClass()
{
}


moveClass::~moveClass()
{
}

void moveClass::init(cSkinnedAnimation* pSkinned, cTransform* trans, cTerrain* terrain)
{
	pChar = pSkinned;
	pCharTrans = trans;
	m_pTerrain = terrain;
	isMove = false;
	//================레이 추가. 아래 방향 바뀌지 않음 .
	moveRay.direction = D3DXVECTOR3(0, -1, 0);
	moveRay.origin = pCharTrans->GetWorldPosition();
	//isClick = false;

}
void moveClass::update(float timeDelta, cBaseObject* collObj)
{
	// 레이 업데이트 
	m_currentPos = pCharTrans->GetWorldPosition(); // 현재 위치. 
	//cRay.direction = D3DXVECTOR3(0, -1, 0);
	moveRay.origin.y = pCharTrans->GetWorldPosition().y + 5; // 머리위에 붙일예정


	if (KEY_MGR->IsStayDown('W'))
	{
		isMove = true;
		moveRay.origin += pCharTrans->GetForward()*0.2f;
	}
	if (KEY_MGR->IsStayDown('S'))
	{
		isMove = true;
		moveRay.origin -= pCharTrans->GetForward()*0.2f;

	}
	if (KEY_MGR->IsStayDown('Q'))
	{
		isMove = true;
		moveRay.origin -= pCharTrans->GetRight()*0.2f;

	}
	if (KEY_MGR->IsStayDown('E'))
	{
		isMove = true;
		moveRay.origin += pCharTrans->GetRight()*0.2f;
	}
	if (KEY_MGR->IsStayDown('A'))
	{
		pCharTrans->RotateSelf(0, -2 * ONE_RAD, 0);
	}

	if (KEY_MGR->IsStayDown('D'))
	{
		pCharTrans->RotateSelf(0, 2 * ONE_RAD, 0);
	}



	// 오브젝트와 충돌했다면. ( 걸러 낼려면 반지름 값을 넣어놔야 한다. )

	//m_lastPos = this->pSkinnedTrans->GetWorldPosition();
	//m_lastPos.y = -1000;
	// 추후에 거리 값을 이용해서 2,3번째 인자 값을 걸러 낼꺼임.
	//if ((
	//	PHYSICS_MGR->IsRayHitStaticMeshObject(
	//	&this->moveRay,
	//	collObj,
	//	collObj->pTransform,
	//	&this->m_prePos,
	//	NULL)) == true)
	//{
	//	m_lastPos = m_prePos; // 오브젝트 충돌 값이 더 클 경우 Last 값을 갱신한다. 
	//}
	//else
	//{
	//	m_lastPos.y = pCharTrans->GetWorldPosition().y - 10;
	//}

	// 터레인과 충돌 했다면. 
	if (m_pTerrain->IsIntersectRay(&m_prePos, &moveRay) == true)
	{
		if (m_lastPos.y > m_prePos.y)
		{
			m_prePos = m_lastPos;
		}
	}



	//=================================== 케릭터를 최종적으로 움직이게 하는 부분 
	if (fabs(m_prePos.y - m_currentPos.y) < 0.5f && isMove == true) // 숫자는 넘어갈 수 있는 높이. ( 아래에서 위로 갈떄. )
	{
		this->pCharTrans->SetWorldPosition(m_prePos);
		m_currentPos = m_prePos; // 좌표 갱신
	}
	// 레이랑 케릭터 거리가 멀어지면 레이가 더이상 넘어가지 못하게 만든다.
	float rayCheckDis = D3DXVec3Length(&(moveRay.origin - pCharTrans->GetWorldPosition()));
	if (rayCheckDis > 0.25f) // 상수 값은 속력 보다 조금 높은 값.
	{
		moveRay.origin = pCharTrans->GetWorldPosition();
		moveRay.origin.y = pCharTrans->GetWorldPosition().y + 5; // 머리위에 붙일예정

	}

	isMove = false;
	//=================================== 케릭터를 최종적으로 움직이게 하는 부분  끗.

}

void moveClass::render()
{
	pChar->Render(pCharTrans);
}