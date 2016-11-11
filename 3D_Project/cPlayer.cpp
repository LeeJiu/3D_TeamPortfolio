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

	//캐릭터의 그려진 위치를 세팅
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
		//m_pInput->ChangeKey('3', new cTestCommand);	//없으면 추가된다.
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

		//거리를 구한다.
		D3DXVECTOR3 dirToTarget = wayPoint - this->pTransform->GetWorldPosition();
		float dist = D3DXVec3Length(&dirToTarget);

		//히트 포인트에 위치하게 되면 lookdirection을 하지 않는다.
		//자신이 자신의 위치를 보게 되면 모델이 사라져버린다.
		//다음 위치로 이동하게 만들자.
		if (dist <= 0.001)
		{
			if (m_nIndex < m_vWayPoint.size() - 1)
				m_nIndex++;
			else if(m_nIndex == m_vWayPoint.size() - 1)
				m_bMove = false;
			return;
		}


		//방향을 구한다.
		this->pTransform->LookDirection(dirToTarget);

		//이동량
		float deltaMove = 5.0f * timeDelta;
		float t = Clamp01(deltaMove / dist);

		//현재 위치에서 웨이 포인트로
		D3DXVECTOR3 pos = VecLerp(this->pTransform->GetWorldPosition(), wayPoint, t);

		//높이 얻는다. / 터레인의 높이
		pos.y = this->pTerrain->GetHeight(pos.x, pos.z);

		this->pTransform->SetWorldPosition(pos);
	}
}
