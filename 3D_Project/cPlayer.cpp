#include "stdafx.h"
#include "cPlayer.h"
#include "cTerrain.h"
#include "cCamera.h"
#include "cMonster.h"
#include "cMonsterManager.h"
#include "cTrailRender.h"

cPlayer::cPlayer()
{

}


cPlayer::~cPlayer()
{
	SAFE_DELETE(m_pMove);
	m_inven->release();
	SAFE_DELETE(m_inven);
	if (this->pTrailRender != NULL)
	{
		this->pTrailRender->Release();
		SAFE_DELETE(this->pTrailRender);
	}
}

void cPlayer::BaseObjectEnable()
{
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

void cPlayer::BaseFontRender()
{
}

void cPlayer::BaseObjectBoundBox()
{
}

void cPlayer::CamControl(float timeDelta)
{
	//D3DXVECTOR3 m_LookAt(this->pTransform->GetWorldPosition().x, this->pTransform->GetWorldPosition().y + 2, this->pTransform->GetWorldPosition().z);
	//this->m_camera->LookPosition(m_LookAt, D3DXVECTOR3(0, 1, 0));
	//
	//int screenCenterX = WINSIZE_X / 2;
	//int screenCenterY = WINSIZE_Y / 2;
	//POINT mousePos = GetMousePos();
	//
	////이동량 ( 중앙에서 멀어진 량 )
	//float deltaX = mousePos.x - screenCenterX;
	//float deltaY = mousePos.y - screenCenterY;
	//float delta = 5;
	//
	//D3DXVECTOR3 VecChar(this->pTransform->GetWorldPosition());
	//D3DXVECTOR3 VecCam(this->m_camera->GetWorldPosition());
	//
	//m_Angle = acos(D3DXVec3Dot(D3DXVec3Normalize(&VecChar, &VecChar), D3DXVec3Normalize(&VecCam, &VecCam)));
	//
	//D3DXVECTOR3 inputVector(0, 0, 0);
	//
	//if (KEY_MGR->IsStayDown(VK_RBUTTON))
	//{
	//	SetMousePos(screenCenterX, screenCenterY);
	//}
	//
	//if (KEY_MGR->IsStayDown(VK_RBUTTON))
	//{
	//	//this->m_camera->SetLocalPosition(0, m_Distance * cos(nowAngleV), -m_Distance * sin(nowAngleV));
	//	if (mousePos.x > screenCenterX)
	//	{ 
	//		inputVector.x = 1;
	//	}
	//	
	//	if (mousePos.x < screenCenterX)
	//	{
	//		inputVector.x = -1;
	//	}
	//
	//	if (mousePos.y < screenCenterY&& m_Angle / ONE_RAD < 60)
	//	{
	//		inputVector.y = 1;
	//	}
	//
	//	if (mousePos.y > screenCenterY && m_Angle / ONE_RAD > 20)
	//	{
	//		inputVector.y = -1;
	//	}
	//}
	//
	//if (KEY_MGR->IsOnceUp(VK_RBUTTON))
	//{
	//	SetMousePos(screenCenterX, screenCenterY);
	//}
	//
	////줌인 줌아웃
	//if (Zoom <= MaxZoomIn && ex_wheelUp) {
	//	inputVector.z = 1;
	//	Zoom += 1.0f;
	//	//this->m_camera->MovePositionSelf(0, 0, 1);
	//}
	//
	//if (Zoom >= MaxZoomOut && ex_wheelDown) {
	//	inputVector.z = -1;
	//	Zoom -= 1.0f;
	//	//this->m_camera->MovePositionSelf(0, 0, -1);
	//}
	//
	//if (VECTORZERO(inputVector) == false)
	//	D3DXVec3Normalize(&inputVector, &inputVector);
	//
	//D3DXVECTOR3 target = inputVector * delta;
	//this->m_camera->MovePositionSelf(target * timeDelta);
	this->m_camera->DefaultControl3(timeDelta, this->pTransform);
}

void cPlayer::UiUpdate(float timeDelta, cCamera* camera)
{
}

void cPlayer::UiURender()
{
	m_inven->render();
	ITEM_MGR->render();
}

void cPlayer::Move(float timeDelta)
{
	//애니메이션셋
	if (!m_InputKeys.find('S')->second && !m_pMove->GetIsJump() && !m_isAttack && m_isMove && (KEY_MGR->IsOnceDown('W') || KEY_MGR->IsOnceDown('D')
		|| KEY_MGR->IsOnceDown('A')))
	{
		SOUND_MGR->play("walk", 0.8f);
		m_isIdle = false;
		m_state = RUN;
		m_strName = MyUtil::SetAnimation(m_state);
		this->pSkinned->Play(m_strName, 0.3);
	}

	if (!m_pMove->GetIsJump() && !m_isAttack && m_isMove && KEY_MGR->IsOnceDown('S'))
	{
		m_isIdle = false;
		m_state = WALK_BACK;
		m_strName = MyUtil::SetAnimation(m_state);
		this->pSkinned->Play(m_strName, 0.3);
	}

	if (!m_pMove->GetIsJump() && !m_isAttack && !m_isMove && (KEY_MGR->IsOnceUp('W') || KEY_MGR->IsOnceUp('S')
		|| KEY_MGR->IsOnceUp('Q') || KEY_MGR->IsOnceUp('E')
		|| KEY_MGR->IsOnceUp('A') || KEY_MGR->IsOnceUp('D')))
	{
		m_isIdle = true;
		m_state = IDLE;
		m_strName = MyUtil::SetAnimation(m_state);
		this->pSkinned->Play(m_strName, 0.3);
	}
	

	if (!m_pMove->GetIsJump() && KEY_MGR->IsOnceDown(VK_SPACE))
	{
		m_state = JUMP;
		m_strName = MyUtil::SetAnimation(m_state);
		this->pSkinned->PlayOneShotAFTERIDLE(m_strName, 0.3,0.3);

		m_InputKeys.find(VK_SPACE)->second = true;
	}
	if (KEY_MGR->IsOnceUp(VK_SPACE))
	{
		m_InputKeys.find(VK_SPACE)->second = false;
	}
	

	//
	//===============무브==============================
	//

	if (!m_isMove) SOUND_MGR->pause("walk");

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
			else if (m_vMonster[i]->monType == DRAGON)
			{
				if (PHYSICS_MGR->IsRayHitBound(&ray, &m_vMonster[i]->BoundBox, m_vMonster[i]->pTransform, NULL, NULL))
				{
					LOG_MGR->AddLog("타겟팅됨");
					this->m_target = m_vMonster[i];
					break;
				}
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
	}
}

void cPlayer::RangeCircleCheck(D3DXVECTOR3 & pos, float range)
{
	int size = m_vMonster.size();

	for (int i = 0; i < size; i++)
	{
		m_vMonster[i]->SetInRange(PHYSICS_MGR->IsPointSphere(m_vMonster[i]->pTransform, range, pos));

		LOG_MGR->AddLog("vMon[%d] : %d", i, m_vMonster[i]->GetInRange());
	}
}

void cPlayer::SkillInit()
{
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
	std::pair<int, bool> key_Space(VK_SPACE, false);		//space키 안눌림  "
	m_InputKeys.insert(key_W);
	m_InputKeys.insert(key_S);
	m_InputKeys.insert(key_A);
	m_InputKeys.insert(key_D);
	m_InputKeys.insert(key_Space);

	//인벤토리
	m_inven = new cInven;
	m_inven->init();
	m_invenOn = false;

	//웨폰
	m_Weapon = new cItem;
	m_Weapon = NULL;

	m_Angle = 0;
}

