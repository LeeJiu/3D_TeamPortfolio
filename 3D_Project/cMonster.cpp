#include "stdafx.h"
#include "cMonster.h"
#include "cWayPoint.h"
#include "cTransform.h"
#include "cTerrain.h"
#include "cPlayer.h"


cMonster::cMonster()
{

}


cMonster::~cMonster()
{
}

void cMonster::BaseObjectEnable()
{
	pTransform->SetWorldPosition(20, pTerrain->GetHeight(20, 3), 3);
	pSkinned->Play("IDLE");

	m_pWayPoint = new cWayPoint(pTerrain);
	m_pWayPoint->Init(pTransform, 10.0f);
}

void cMonster::BaseObjectUpdate(float timeDelta)
{
	m_pWayPoint->Update(pTransform);
	float distance = D3DXVec3Length(&(m_pPlayer->pTransform->GetWorldPosition() - pTransform->GetWorldPosition()));

	if (distance < m_fRange)
	{
		MoveToPlayer();
	}
	else
	{
		//조건 추가해주자.
		/*if (m_vObjects.empty() == false)
		{
		m_pWayPoint->SetBoundObjects(m_vObjects);
		}*/
		m_pWayPoint->Update(pTransform);
	}
}

void cMonster::BaseObjectBoundBox()
{

}

void cMonster::MoveToPlayer()
{
	//레이 세팅
	D3DXVECTOR3 currentPos = pTransform->GetWorldPosition();
	Ray ray;
	ray.direction = D3DXVECTOR3(0, -1, 0);
	ray.origin = currentPos;
	ray.origin.y += 3;


	if (PHYSICS_MGR->IsOverlap(this, m_pPlayer))
	{
		return;
	}


	//거리를 구한다. / 플레이어와 몬스터의 거리
	D3DXVECTOR3 dirToTarget = m_pPlayer->pTransform->GetWorldPosition() - currentPos;
	float dist = D3DXVec3Length(&dirToTarget);
	dirToTarget.y = 0;


	//방향을 구한다.
	D3DXVec3Normalize(&dirToTarget, &dirToTarget);
	dirToTarget.y = 0;
	D3DXVECTOR3 forward = pTransform->GetForward();
	forward.y = 0;
	D3DXVec3Normalize(&forward, &forward);

	float angle = acosf(D3DXVec3Dot(&forward, &dirToTarget));
	if (angle >= 160 * ONE_RAD)
	{
		pTransform->RotateSelf(0, 30 * ONE_RAD, 0);

		//LOG_MGR->AddLog("%.2f, %d", angle * 180 / 3.14, m_nIndex);
	}

	D3DXVECTOR3 lerp = pTransform->GetForward();
	D3DXVec3Lerp(&lerp, &lerp, &dirToTarget, 0.2);
	pTransform->LookDirection(lerp, pTransform->GetUp());


	//이동량
	float deltaMove = 5.0f * TIME_MGR->GetFrameDeltaSec();
	float t = Clamp01(deltaMove / dist);

	//현재 위치에서 웨이 포인트로 보간된 위치값을 레이에 넣는다.
	ray.origin = VecLerp(currentPos, m_pPlayer->pTransform->GetWorldPosition(), t);
	ray.origin.y += 3;	//머리 위에 붙인다.


	D3DXVECTOR3 pos;
	//레이랑 터레인 체크하자
	if (pTerrain->IsIntersectRay(&pos, &ray))
	{
		pTransform->SetWorldPosition(pos);
		currentPos = pos;
	}

	// 레이랑 케릭터 거리가 멀어지면 레이가 더이상 넘어가지 못하게 만든다.
	float rayCheckDis = D3DXVec3Length(&(ray.origin - currentPos));
	if (rayCheckDis > t + 0.01f) // 상수 값은 속력 보다 조금 높은 값.
	{
		ray.origin = currentPos;
		ray.origin.y += 3;
	}
}
void cMonster::BaseObjectRender()
{
	this->pSkinned->Render(this->pTransform);
	this->pTransform->RenderGimozo();
	this->BoundBox.RenderGizmo(this->pTransform);

}