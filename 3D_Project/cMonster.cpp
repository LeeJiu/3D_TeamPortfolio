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
		//���� �߰�������.
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
	//���� ����
	D3DXVECTOR3 currentPos = pTransform->GetWorldPosition();
	Ray ray;
	ray.direction = D3DXVECTOR3(0, -1, 0);
	ray.origin = currentPos;
	ray.origin.y += 3;


	if (PHYSICS_MGR->IsOverlap(this, m_pPlayer))
	{
		return;
	}


	//�Ÿ��� ���Ѵ�. / �÷��̾�� ������ �Ÿ�
	D3DXVECTOR3 dirToTarget = m_pPlayer->pTransform->GetWorldPosition() - currentPos;
	float dist = D3DXVec3Length(&dirToTarget);
	dirToTarget.y = 0;


	//������ ���Ѵ�.
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


	//�̵���
	float deltaMove = 5.0f * TIME_MGR->GetFrameDeltaSec();
	float t = Clamp01(deltaMove / dist);

	//���� ��ġ���� ���� ����Ʈ�� ������ ��ġ���� ���̿� �ִ´�.
	ray.origin = VecLerp(currentPos, m_pPlayer->pTransform->GetWorldPosition(), t);
	ray.origin.y += 3;	//�Ӹ� ���� ���δ�.


	D3DXVECTOR3 pos;
	//���̶� �ͷ��� üũ����
	if (pTerrain->IsIntersectRay(&pos, &ray))
	{
		pTransform->SetWorldPosition(pos);
		currentPos = pos;
	}

	// ���̶� �ɸ��� �Ÿ��� �־����� ���̰� ���̻� �Ѿ�� ���ϰ� �����.
	float rayCheckDis = D3DXVec3Length(&(ray.origin - currentPos));
	if (rayCheckDis > t + 0.01f) // ��� ���� �ӷ� ���� ���� ���� ��.
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