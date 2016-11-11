#include "stdafx.h"
#include "cWayPoint.h"
#include "cTransform.h"
#include "cTerrain.h"


cWayPoint::cWayPoint(cTerrain*	pTerrain)
{
	m_pTerrain = pTerrain;
	m_nIndex = 0;
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
	D3DXVECTOR3 wayPoint(m_vWayPoint[m_nIndex].x, m_vWayPoint[m_nIndex].y, m_vWayPoint[m_nIndex].z);

	//�Ÿ��� ���Ѵ�.
	D3DXVECTOR3 dirToTarget = wayPoint - trans->GetWorldPosition();
	float dist = D3DXVec3Length(&dirToTarget);


	//��Ʈ ����Ʈ�� ��ġ�ϰ� �Ǹ� lookdirection�� ���� �ʴ´�.
	//�ڽ��� �ڽ��� ��ġ�� ���� �Ǹ� ���� �����������.
	//���� ��ġ�� �̵��ϰ� ������.
	if (dist <= 0.001)
	{
		if (m_bStart == true && m_bEnd == false)
		{
			m_nIndex++;
			if (m_nIndex >= m_vWayPoint.size())
			{
				m_nIndex = m_vWayPoint.size() - 1;
				m_bStart = false;
				m_bEnd = true;
			}
		}
		else if (m_bStart == false && m_bEnd == true)
		{
			m_nIndex--;
			if (m_nIndex < 0)
			{
				m_nIndex = 0;
				m_bStart = true;
				m_bEnd = false;
			}
		}
		return;
	}


	//������ ���Ѵ�.
	/*D3DXVec3Normalize(&dirToTarget, &dirToTarget);
	D3DXVECTOR3 dir = VecLerp(trans->GetForward(), dirToTarget, 0.3);
	dir.y = 0;
	trans->LookDirection(dir);*/
	

	//�̵���
	float deltaMove = 5.0f * TIME_MGR->GetFrameDeltaSec();
	float t = Clamp01(deltaMove / dist);

	//���� ��ġ���� ���� ����Ʈ��
	D3DXVECTOR3 pos = VecLerp(trans->GetWorldPosition(), wayPoint, t);

	//���� ��´�. / �ͷ����� ����
	pos.y = m_pTerrain->GetHeight(pos.x, pos.z);

	trans->SetWorldPosition(pos);
}
