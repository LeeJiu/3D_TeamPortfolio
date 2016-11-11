#include "stdafx.h"
#include "cPlayer.h"
#include "cTerrain.h"
#include "cCamera.h"
#include "cInputHandler.h"


cPlayer::cPlayer()
{
	
}


cPlayer::~cPlayer()
{
	SAFE_DELETE(m_pInput);
}

void cPlayer::BaseObjectEnable()
{
	m_pInput = new cInputHandler;
	m_pInput->AddKey('1', new cTestCommand);
	m_pInput->AddKey('2', new cTestCommand2);

	//ĳ������ �׷��� ��ġ�� ����
	pTransform->SetWorldPosition(0, pTerrain->GetHeight(0, 0), 0);

	m_nIndex = 0;
}

void cPlayer::BaseObjectUpdate(float timeDelta)
{
	cCommand* command = m_pInput->HandleInput();
	if (command != NULL)
	{
		command->Execute();
	}

	if (KEY_MGR->IsOnceDown('P'))
	{
		//m_pInput->ChangeKey('3', new cTestCommand);	//������ �߰��ȴ�.
		//m_pInput->DeleteKey('1');
		m_pInput->SwapKey('1', '2');
	}

	KeyControl(timeDelta);

	MovePoint(timeDelta);
}

void cPlayer::BaseObjectRender()
{
	this->pSkinned->Render(this->pTransform);

	for (m_viWayPoint = m_vWayPoint.begin(); m_viWayPoint != m_vWayPoint.end(); ++m_viWayPoint)
	{
		GIZMO_MGR->WireSphere(D3DXVECTOR3(m_viWayPoint->x, m_viWayPoint->y, m_viWayPoint->z), 0.5f);
	}
}

void cPlayer::KeyControl(float timeDelta)
{
	if (KEY_MGR->IsOnceDown(VK_LBUTTON))
	{
		Ray ray;
		POINT ptMousePos = GetMousePos();
		D3DXVECTOR2 screenPos(ptMousePos.x, ptMousePos.y);
		m_camera->ComputeRay(&ray, &screenPos);

		D3DXVECTOR3 pos;
		pTerrain->IsIntersectRay(&pos, &ray);

		m_vWayPoint.push_back(pos);
	}

	if (KEY_MGR->IsOnceDown(VK_SPACE))
	{
		m_bMove = true;
	}
}

void cPlayer::MovePoint(float timeDelta)
{
	if (m_bMove == true)
	{
		D3DXVECTOR3 wayPoint(m_vWayPoint[m_nIndex].x, m_vWayPoint[m_nIndex].y, m_vWayPoint[m_nIndex].z);

		//�Ÿ��� ���Ѵ�.
		D3DXVECTOR3 dirToTarget = wayPoint - this->pTransform->GetWorldPosition();
		float dist = D3DXVec3Length(&dirToTarget);

		//��Ʈ ����Ʈ�� ��ġ�ϰ� �Ǹ� lookdirection�� ���� �ʴ´�.
		//�ڽ��� �ڽ��� ��ġ�� ���� �Ǹ� ���� �����������.
		//���� ��ġ�� �̵��ϰ� ������.
		if (dist <= 0.001)
		{
			if (m_nIndex < m_vWayPoint.size() - 1)
				m_nIndex++;
			else if(m_nIndex == m_vWayPoint.size() - 1)
				m_bMove = false;
			return;
		}


		//������ ���Ѵ�.
		this->pTransform->LookDirection(dirToTarget);

		//�̵���
		float deltaMove = 5.0f * timeDelta;
		float t = Clamp01(deltaMove / dist);

		//���� ��ġ���� ���� ����Ʈ��
		D3DXVECTOR3 pos = VecLerp(this->pTransform->GetWorldPosition(), wayPoint, t);

		//���� ��´�. / �ͷ����� ����
		pos.y = this->pTerrain->GetHeight(pos.x, pos.z);

		this->pTransform->SetWorldPosition(pos);
	}
}
