#include "stdafx.h"
#include "cPlayer.h"
#include "cTerrain.h"
#include "cCamera.h"
#include "cMonster.h"
#include "cInputHandler.h"


cPlayer::cPlayer()
{

}


cPlayer::~cPlayer()
{
}

void cPlayer::BaseObjectEnable()
{
	//캐릭터의 그려진 위치를 세팅
	pTransform->SetWorldPosition(0, pTerrain->GetHeight(0, 0), 0);
}

void cPlayer::BaseObjectUpdate(float timeDelta)
{
	
}

void cPlayer::BaseObjectRender()
{
	this->pSkinned->Render(this->pTransform);
}

void cPlayer::Monster_pick()
{
	if (KEY_MGR->IsOnceDown(VK_LBUTTON))
	{
		Ray ray;
		POINT ptMousePos = GetMousePos();
		D3DXVECTOR2 screenPos(ptMousePos.x, ptMousePos.y);
		m_camera->ComputeRay(&ray, &screenPos);
	
	
		int size = m_vMonster.size();
		for (int i = 0; i < size; i++)
		{
			if (PHYSICS_MGR->IsRayHitBound(&ray, &m_vMonster[i]->BoundBox, m_vMonster[i]->pTransform, NULL, NULL))
			{
				LOG_MGR->AddLog("타겟팅됨");
				this->m_target = m_vMonster[i];
			}
			else this->m_target = NULL;
		}
	}
}

bool cPlayer::LengthCheck()
{
	return false;
}

void cPlayer::Attack01()
{
}

void cPlayer::Attack02()
{
}

void cPlayer::Attack03()
{
}

void cPlayer::Damage(float damage)
{
}
