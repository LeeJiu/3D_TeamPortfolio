#include "stdafx.h"
#include "cWayPoint.h"
#include "cTransform.h"
#include "cTerrain.h"


cWayPoint::cWayPoint(cTerrain*	pTerrain)
{
	m_pTerrain = pTerrain;
	m_nIndex = 0;
	m_ray.direction = D3DXVECTOR3(0, -1, 0);
}


cWayPoint::~cWayPoint()
{
}

void cWayPoint::Init(cTransform * trans, float fRadius)
{
	m_nPointNum = RandomIntRange(3, 5);

	float tX = trans->GetWorldPosition().x;
	float tZ = trans->GetWorldPosition().z;

	for (int i = 0; i < m_nPointNum; ++i)
	{
		float x, z;
		x = RandomFloatRange(tX - fRadius, tX + fRadius);
		z = RandomFloatRange(tZ - fRadius, tZ + fRadius);

		D3DXVECTOR3 pos(x, m_pTerrain->GetHeight(x, z), z);
		m_vWayPoint.push_back(pos);
	}
	
	m_bStart = true;
	m_bEnd = false;
}

void cWayPoint::Update(cTransform * trans)
{
	//레이 세팅
	m_currentPos = trans->GetWorldPosition();
	m_ray.origin = m_currentPos;
	m_ray.origin.y += 3;


	//거리를 구한다.
	D3DXVECTOR3 dirToTarget = m_vWayPoint[m_nIndex] - m_currentPos;
	float dist = D3DXVec3Length(&dirToTarget);
	dirToTarget.y = 0;


	//히트 포인트에 위치하게 되면 lookdirection을 하지 않는다.
	//자신이 자신의 위치를 보게 되면 모델이 사라져버린다.
	//다음 위치로 이동하게 만들자.
	if (dist <= 0.001)
	{
		if (m_bStart == true && m_bEnd == false)
		{
			m_nIndex++;
			if (m_nIndex == m_vWayPoint.size())
			{
				m_nIndex = m_vWayPoint.size() - 2;
				m_bStart = false;
				m_bEnd = true;
			}
		}
		else if (m_bStart == false && m_bEnd == true)
		{
			m_nIndex--;
			if (m_nIndex < 0)
			{
				m_nIndex = 1;
				m_bStart = true;
				m_bEnd = false;
			}
		}
		return;
	}


	//방향을 구한다.
	D3DXVec3Normalize(&dirToTarget, &dirToTarget);
	dirToTarget.y = 0;
	D3DXVECTOR3 forward = trans->GetForward();
	forward.y = 0;
	D3DXVec3Normalize(&forward, &forward);

	float angle = acosf(D3DXVec3Dot(&forward, &dirToTarget));
	if (angle >= 160 * ONE_RAD)
	{
		trans->RotateSelf(0, 30 * ONE_RAD, 0);

		LOG_MGR->AddLog("%.2f, %d", angle * 180 / 3.14, m_nIndex);
	}

	D3DXVECTOR3 lerp = trans->GetForward();
	D3DXVec3Lerp(&lerp, &lerp, &dirToTarget, 0.2);
	trans->LookDirection(lerp, trans->GetUp());


	//이동량
	float deltaMove = 5.0f * TIME_MGR->GetFrameDeltaSec();
	float t = Clamp01(deltaMove / dist);

	//현재 위치에서 웨이 포인트로 보간된 위치값을 레이에 넣는다.
	m_ray.origin = VecLerp(m_currentPos, m_vWayPoint[m_nIndex], t);
	m_ray.origin.y += 3;	//머리 위에 붙인다.

	//레이랑 터레인 체크하자
	if (m_pTerrain->IsIntersectRay(&m_prePos, &m_ray))
	{
		trans->SetWorldPosition(m_prePos);
		m_currentPos = m_prePos;
	}

	// 레이랑 케릭터 거리가 멀어지면 레이가 더이상 넘어가지 못하게 만든다.
	float rayCheckDis = D3DXVec3Length(&(m_ray.origin - m_currentPos));
	if (rayCheckDis > t + 0.01f) // 상수 값은 속력 보다 조금 높은 값.
	{
		m_ray.origin = m_currentPos;
		m_ray.origin.y += 3;
	}
}
