#include "stdafx.h"
#include "cPlayer.h"
#include "cTerrain.h"
#include "cCamera.h"
#include "cMonster.h"
#include "cMonsterManager.h"

cPlayer::cPlayer()
{

}


cPlayer::~cPlayer()
{
	SAFE_DELETE(m_pMove);
	m_inven->release();
	SAFE_DELETE(m_inven);
}

void cPlayer::BaseObjectEnable()
{
	//캐릭터의 그려진 위치를 세팅
	pTransform->SetWorldPosition(0, pTerrain->GetHeight(0, 0), 0);

}

void cPlayer::BaseObjectUpdate(float timeDelta)
{
	Monster_pick();
}

void cPlayer::BaseObjectRender()
{
	this->pSkinned->Render(this->pTransform);
}

void cPlayer::BaseSpriteRender()
{

}

void cPlayer::BaseObjectBoundBox()
{
}

void cPlayer::UiUpdate(float timeDelta, cCamera* camera)
{
	
	if (m_inven->GetWeapon() == NULL &&m_botton == true)
	{
		m_botton = false;
	}
	else if (m_inven->GetWeapon() != NULL&& m_botton == false)
	{
		m_inven->GetWeapon()->BoundBox.SetBound(&m_inven->GetWeapon()->pTransform->GetWorldPosition(), &D3DXVECTOR3(-0.3f, -0.3f, -0.3f));
		pSkinned->AddBoneTransform("BN_Weapon_R", m_inven->GetWeapon()->pTransform);
		m_botton = true;
	}

	//m_Weapon = m_inven->GetWeapon();

	m_inven->update(timeDelta, m_camera);


	ITEM_MGR->update(timeDelta);
}

void cPlayer::UiURender()
{
	m_inven->render();
	ITEM_MGR->render();
}

void cPlayer::Move(float timeDelta)
{
	//애니메이션셋
	if (!m_isAttack && m_isMove && (KEY_MGR->IsOnceDown('W') || KEY_MGR->IsOnceDown('D')
		|| KEY_MGR->IsOnceDown('A')))
	{
		m_state = WALK;
		m_strName = MyUtil::SetAnimation(m_state);
		this->pSkinned->Play(m_strName, 0.3);
	}

	if (!m_isAttack && m_isMove && KEY_MGR->IsOnceDown('S'))
	{
		m_state = WALK_BACK;
		m_strName = MyUtil::SetAnimation(m_state);
		this->pSkinned->Play(m_strName, 0.3);
	}

	if ((!m_isMove && (KEY_MGR->IsOnceUp('W') || KEY_MGR->IsOnceUp('S')
		|| KEY_MGR->IsOnceUp('Q') || KEY_MGR->IsOnceUp('E')
		|| KEY_MGR->IsOnceUp('A') || KEY_MGR->IsOnceUp('D'))))
	{
		m_state = IDLE;
		m_strName = MyUtil::SetAnimation(m_state);
		this->pSkinned->Play(m_strName, 0.3);
	}

	//
	//===============무브==============================
	//

	if (KEY_MGR->IsStayDown('W'))
	{
		m_InputKeys.find('W')->second = true;
	}
	else m_InputKeys.find('W')->second = false;


	if (KEY_MGR->IsStayDown('S'))
	{
		m_InputKeys.find('S')->second = true;
	}
	else m_InputKeys.find('S')->second = false;

	if (KEY_MGR->IsStayDown('A'))
	{
		m_InputKeys.find('A')->second = true;
	}
	else m_InputKeys.find('A')->second = false;

	if (KEY_MGR->IsStayDown('D'))
	{
		m_InputKeys.find('D')->second = true;
	}
	else m_InputKeys.find('D')->second = false;


	m_pMove->update(timeDelta, NULL, NULL, NULL, m_InputKeys);
	m_isMove = m_pMove->GetIsMove();
}

void cPlayer::Monster_pick()
{
	if (KEY_MGR->IsOnceDown(VK_LBUTTON))
	{
		LOG_MGR->AddLog("타겟팅안됨");
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
				break;
			}
			else this->m_target = NULL;
		}
	}
}

bool cPlayer::LengthCheck()
{
	if (m_target != NULL)
	{
		D3DXVECTOR3 vDistance = this->pTransform->GetWorldPosition() - m_target->pTransform->GetWorldPosition();
		float distance;
		distance = D3DXVec3Length(&vDistance);

		if (distance < m_attackLength)
			return true;
		else return false;
	}
	else return false;
}

void cPlayer::RangeCheck(float range)
{
	int size = m_vMonster.size();

	for (int i = 0; i < size; i++)
	{
		m_vMonster[i]->SetInRange(PHYSICS_MGR->IsPointSphere(this->pTransform, range, m_vMonster[i]->pTransform));

		LOG_MGR->AddLog("vMon[%d] : %d", i, m_vMonster[i]->GetInRange());
	}
}

void cPlayer::SetBassClass()
{
	m_pMove = new moveClass;
	m_isMove = false;

	//무빙용으로 사용할 키값 세팅
	std::pair<int, bool> key_W('W', false);		//W키 안눌림	상태
	std::pair<int, bool> key_S('S', false);		//S키 안눌림  " 
	std::pair<int, bool> key_A('A', false);		//A키 안눌림  "
	std::pair<int, bool> key_D('D', false);		//D키 안눌림  "
	m_InputKeys.insert(key_W);
	m_InputKeys.insert(key_S);
	m_InputKeys.insert(key_A);
	m_InputKeys.insert(key_D);

	//인벤토리
	m_inven = new cInven;
	m_inven->init();
	m_invenOn = false;

	//웨폰
	m_Weapon = new cItem;
	m_Weapon = NULL;
	//D3DXMATRIXA16 matScale;
	//D3DXMatrixScaling(&matScale, 0.05f, 0.05f, 0.05f);
	//D3DXMATRIXA16 matCorrection = matScale;
	//cXMesh_Static* pSTF_Basic = RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Weapon/TAX_Basic.X", &matCorrection);
	//
	//m_Weapon->SetMesh(pSTF_Basic);
	//m_Weapon->SetActive(true);
	//
	//m_Weapon->BoundBox.SetBound(&m_Weapon->pTransform->GetWorldPosition(), &D3DXVECTOR3(-0.3f, -0.3f, -0.3f));
	//pSkinned->AddBoneTransform("BN_Weapon_R", m_Weapon->pTransform);


}
