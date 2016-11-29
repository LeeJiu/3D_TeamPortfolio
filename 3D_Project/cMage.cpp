#include "stdafx.h"
#include "cPlayer.h"
#include "cMage.h"
#include "cMonsterManager.h"
#include "cMonster.h"
#include "cCamera.h"
#include "cInven.h"
#include "cTrailRender.h"

//파티클
#include "cPartcleEmitter.h"
#include "cParticleQuad.h""
#include "cParticle.h"
#include "cQuadParticleEmitter.h"

//스킬

cMage::cMage()
{

}


cMage::~cMage()
{
	SAFE_DELETE(m_ATKBox);
	SAFE_DELETE(m_pSkill_SnowStorm);
	SAFE_DELETE(m_pSurroundSkill);
	SAFE_DELETE(m_pSkill_DarkRain);
	SAFE_DELETE(m_pSkill_Front);
	SAFE_DELETE(m_pSkill_magicShild);
	SAFE_DELETE(m_pSkill_Escape);
	SAFE_DELETE(m_pSkill_FlameRoad);
}



void cMage::BaseObjectEnable()
{




	m_fHP = 2000;
	m_currentHp = 2000;
	m_fSP = 1500;
	m_currentSp = 1500;

	m_attackLength = 5;
	m_damage = 100;
	m_isAttack = false;
	m_invenOn = false;				//인벤

	m_UIContainer = new cUI_Container;
	m_UIContainer->UI_Init(m_fHP, m_fSP, MAGE);

	SetBassClass();

	//캐릭터의 그려진 위치를 세팅
	pTransform->SetWorldPosition(0, pTerrain->GetHeight(0, 0), 0);
	BaseObjectBoundBox();

	BasicWeaponSet();

	m_botton = false;
	m_isPetOn = false;

	//평타 박스
	m_ATKBox = new cBaseObject;
	m_ATKBox->BoundBox.Init(D3DXVECTOR3(-0.3f, -0.3f, -0.3f), D3DXVECTOR3(0.3f, 0.3f, 0.3f));

	m_ATKBox->BoundBox.SetBound(&m_ATKBox->pTransform->GetWorldPosition(), &D3DXVECTOR3(-0.3f, -0.3f, -0.3f));
	pSkinned->AddBoneTransform("Bip01-L-Hand", m_ATKBox->pTransform);

	m_vMonster = m_pMonMgr->GetMonsters();
	m_target = NULL;

	m_pMove->init(pTransform, pTerrain, m_camera, NULL);

	m_state = IDLE;
	m_strName = MyUtil::SetAnimation(m_state);

	m_camera->AttachTo(pTransform);
	m_camera->SetLocalPosition(0, 3, -5);

	//SetMoveKeys();

	//스킬 관련
	SkillInit();
}

void cMage::BaseObjectUpdate(float timeDelta)
{
	CamControl(timeDelta);
	Move(timeDelta);

	if (m_invenOn || m_pSkill_DarkRain->GetIsSelecting())
	{
		
	}
	else	Monster_pick();

	UiUpdate(timeDelta, m_camera);
	if (this->pTrailRender != NULL)
		this->pTrailRender->Update(timeDelta);
	
	//펫에 타고 있냐
	//if (KEY_MGR->IsOnceDown('9'))
	//{
	//	if (m_isPetOn) m_isPetOn = false;
	//	else
	//	{
	//		m_state = PET_RUN;
	//		m_strName = SetAnimation(m_state);
	//		this->pSkinned->Play(m_strName, 0.3);
	//		m_isPetOn = true;
	//	}
	//}
	//
	//
	//if (m_isPetOn)
	//{
	//
	//}
	//else
	//{

	if (m_target != NULL)
	{
		D3DXVECTOR3 magicATKLegth = pTransform->GetWorldPosition() - m_target->pTransform->GetWorldPosition();
		D3DXVECTOR3 magicATKCollision = m_ATKBox->pTransform->GetWorldPosition() - m_target->pTransform->GetWorldPosition();


		if (!m_pMagicShot->GetIsAttacking())
		{

			if (KEY_MGR->IsOnceDown('1'))
			{
				m_state = ATK_01;
				m_strName = MyUtil::SetAnimation(m_state);
				pSkinned->PlayOneShotAfterOther(m_strName, "WAIT", 0.3);

				m_pMagicShot->Effect_Init();
				m_pMagicShot->MakeAtk();
			}

		}
		
		if (m_pMagicShot->GetIsAttacking())
		{
			RangeCircleCheck(m_ATKBox->pTransform->GetWorldPosition(), 3);

			int size = m_vMonster.size();
			for (int i = 0; i < size; i++)
			{
				LOG_MGR->AddLog("vector[%d] = %d", i, m_vMonster[i]->GetInRange());

				if (!m_vMonster[i]->GetInRange()) continue;

				m_vMonster[i]->Damage(100);
				LOG_MGR->AddLog("데미지 받는중");
				m_pMagicShot->SetHit();
			}

			pSkinned->RemoveBoneTransform("Bip01-L-Hand");
			m_ATKBox->pTransform->LookPosition(m_target->pTransform->GetWorldPosition() + D3DXVECTOR3(0, 2, 0));
			m_ATKBox->pTransform->MovePositionSelf(0, 0, 30.0f * timeDelta);
		}
		else
		{
			pSkinned->AddBoneTransform("Bip01-L-Hand", m_ATKBox->pTransform);
		}


	}

	if (!m_pSkill_FlameRoad->GetIsAttacking())
	{

		if (KEY_MGR->IsOnceDown('2'))
		{
			m_state = STF_FROZEN;
			m_strName = MyUtil::SetAnimation(m_state);
			this->pSkinned->PlayOneShotAfterOther(m_strName, "WAIT", 0.3);

			//캐스팅 120초
			//시전시간 200초
			m_pSkill_FlameRoad->Effect_Init();
			m_pSkill_FlameRoad->StartCasting();
		}
	}
	

	if (!m_pSkill_SnowStorm->GetIsAttacking())
	{
		if (KEY_MGR->IsOnceDown('3'))
		{
			m_state = STF_TYFUNG;
			m_strName = MyUtil::SetAnimation(m_state);
			this->pSkinned->PlayOneShotAfterOther(m_strName, "WAIT", 0.3);
			m_pSkill_SnowStorm->Effect_Init();
			m_pSkill_SnowStorm->StartCasting();
	
		}
	}

	if (!m_pSkill_DarkRain->GetIsAttacking())
	{
		if (KEY_MGR->IsOnceDown('4'))
		{
			m_pSkill_DarkRain->Effect_Init();
			m_pSkill_DarkRain->SelectSkill();
		}

		if (m_pSkill_DarkRain->GetCastCount() == 1) //캐스팅 시작시에 모션을 바꿔주기 위해서
		{
			m_state = STF_BUMB;
			m_strName = MyUtil::SetAnimation(m_state);
			this->pSkinned->PlayOneShotAfterOther(m_strName, "WAIT", 0.3);
		}
	}

	if (!m_pSkill_magicShild->GetIsInBuff())
	{
		if (KEY_MGR->IsOnceDown('5'))
		{
			m_state = STF_BUFF;
			m_strName = MyUtil::SetAnimation(m_state);
			this->pSkinned->PlayOneShotAfterOther(m_strName, "WAIT", 0.3);
			m_pSkill_magicShild->Effect_Init();
			m_pSkill_magicShild->StartCasting();

		}
	}



	if (KEY_MGR->IsOnceDown('7'))
	{
		m_state = STF_BLINK;
		m_strName = MyUtil::SetAnimation(m_state);
		this->pSkinned->PlayOneShotAfterOther(m_strName, "WAIT", 0.3);
		m_pSkill_Escape->StartCasting();
	}

	if (KEY_MGR->IsOnceDown('8'))
	{
		m_pSurroundSkill->StartCasting();
		LOG_MGR->AddLog("캐스팅중");
	}

	if (KEY_MGR->IsOnceDown('9'))
	{
		m_pSkill_Front->SelectSkill();
	}

	Ray ray;
	POINT ptMousePos = GetMousePos();
	D3DXVECTOR2 screenPos(ptMousePos.x, ptMousePos.y);
	m_camera->ComputeRay(&ray, &screenPos);
	D3DXVECTOR3		mousePos;
	pTerrain->IsIntersectRay(&mousePos, &ray);

	m_pRoundSkill->BaseObjectUpdate(timeDelta, pTransform->GetWorldPosition(), mousePos);

	m_pSkill_SnowStorm->BaseObjectUpdate(timeDelta, pTransform->GetWorldPosition());
	m_pSkill_SnowStorm->Effect_Update(timeDelta);

	m_pSkill_DarkRain->BaseObjectUpdate(timeDelta, pTransform->GetWorldPosition(), mousePos);
	m_pSkill_DarkRain->Effect_Update(timeDelta);

	m_pSkill_Front->BaseObjectUpdate(timeDelta, pTransform->GetWorldPosition(), pTransform->GetForward());

	m_pSurroundSkill->BaseObjectUpdate(timeDelta, pTransform->GetWorldPosition());

	m_pSkill_magicShild->BaseObjectUpdate(timeDelta, pTransform->GetWorldPosition());
	m_pSkill_magicShild->Effect_Update(timeDelta);

	m_pSkill_Escape->BaseObjectUpdate(timeDelta, pTransform->GetWorldPosition(), pTransform->GetForward());
	
	m_pSkill_FlameRoad->BaseObjectUpdate(timeDelta, pTransform->GetWorldPosition(), pTransform->GetForward());
	m_pSkill_FlameRoad->Effect_Update(timeDelta);



	if (m_pSkill_Escape->GetBuffCount() == 100)
	{
		pTransform->SetWorldPosition(D3DXVECTOR3(m_pSkill_Escape->GetEscapePos().x, pTransform->GetWorldPosition().y, m_pSkill_Escape->GetEscapePos().z));
	}

	SKILL03();

	m_pMagicShot->BaseObjectUpdate(timeDelta, m_ATKBox->pTransform->GetWorldPosition(), pTransform->GetForward());
	m_pMagicShot->Effect_Update(timeDelta);

	m_UIContainer->UI_Update(m_currentHp, m_currentSp);
}


void cMage::BaseObjectRender()
{
	this->pSkinned->Render(this->pTransform);

	//m_ATKBox->BoundBox.RenderGizmo(m_ATKBox->pTransform);

	m_Weapon->Render();
	if (this->pTrailRender != NULL)
	{
		this->pTrailRender->RenderDistort(this->m_camera);
	}


	m_pSurroundSkill->BaseObjectRender();
	m_pRoundSkill->BaseObjectRender();
	m_pSkill_SnowStorm->BaseObjectRender();
	m_pSkill_SnowStorm->Effect_Render();
	m_pSkill_DarkRain->BaseObjectRender();
	m_pSkill_DarkRain->Effect_Render();
	m_pSkill_Front->BaseObjectRender();
	m_pSkill_magicShild->Effect_Render();
	m_pSkill_Escape->BaseObjectRender();
	m_pSkill_FlameRoad->BaseObjectRender();
	m_pSkill_FlameRoad->Effect_Render();
	m_pMagicShot->BaseObjectRender();
	m_pMagicShot->Effect_Render();
}

void  cMage::BaseSpriteRender()
{
	UiURender();
	m_UIContainer->UI_Render();
}

void cMage::BaseFontRender()
{
	m_UIContainer->UI_fontRender();
}

void  cMage::SkillInit()
{
	m_pSkill_SnowStorm = new cSkill_SnowStorm;
	m_pSkill_SnowStorm->SetActive(true);
	m_pSkill_SnowStorm->BaseObjectEnable(pTransform->GetWorldPosition(), 5.0f, 1, 400, 300);

	m_pSurroundSkill = new cSkill_Surround;
	m_pSurroundSkill->BaseObjectEnable(pTransform->GetWorldPosition(), 6.0f, 100, 20, 20);

	m_pRoundSkill = new cSkill_Round;
	m_pRoundSkill->BaseObjectEnable(pTransform->GetWorldPosition(), 6.0f, 20, 20, 100, 30);

	m_pSkill_DarkRain = new cSkill_DarkRain;
	m_pSkill_DarkRain->SetActive(true);
	m_pSkill_DarkRain->BaseObjectEnable(pTransform->GetWorldPosition(), 6.0f, 40, 100, 200, 300);

	m_pSkill_Front = new cSkill_Front;
	m_pSkill_Front->SetActive(true);
	m_pSkill_Front->BaseObjectEnable(pTransform->GetWorldPosition(), 20.0f, 3.0f, 1, 400, 300);

	m_pSkill_magicShild = new cSkill_MagicShild;
	m_pSkill_magicShild->SetActive(true);
	m_pSkill_magicShild->BaseObjectEnable(pTransform->GetWorldPosition(), 1, 600, 300);

	m_pSkill_Escape = new cSkill_Escape;
	m_pSkill_Escape->SetActive(true);
	m_pSkill_Escape->BaseObjectEnable(pTransform->GetWorldPosition(), 25.0f, 1, 200, 100);


	m_pSkill_FlameRoad = new cSkill_FlameRoad;
	m_pSkill_FlameRoad->SetActive(true);
	m_pSkill_FlameRoad->BaseObjectEnable(pTransform->GetWorldPosition(), 20.0f, 3.0f, 130, 250, 100);

	m_pMagicShot = new cSkill_MagicShot;
	m_pMagicShot->SetActive(true);
	m_pMagicShot->BaseObjectEnable(m_ATKBox->pTransform->GetWorldPosition(), 30.0f, 100);


	m_aniCount = 0;
	

}

void cMage::BaseObjectBoundBox()
{
	BoundBox.SetBound(&D3DXVECTOR3(0, 1.5f, 0), &D3DXVECTOR3(0.5f, 1.5f, 0.5f));
}

void cMage::BasicWeaponSet()
{
	//베이직무기 셋팅해줄거
	m_Weapon = new cItem;

	//TrailRenderSet
	this->pTrailRender = new cTrailRender();
	this->pTrailRender->Init(
		1.0f,					//꼬리 라이브 타임 ( 이게 크면 환영큐 사이즈가 커지고 꼬리가 오랬동안 남아있다 )
		0.2f,					//폭
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/TrailTest.png"),	//메인 Texture
		D3DXCOLOR(0, 0, 0.5, 0.8),												//메인 Texture 로 그릴때 컬러
		NULL
	);

	m_Weapon = ITEM_MGR->getItem(3);
	m_Weapon->BoundBox.SetBound(&D3DXVECTOR3(0.f, 1.f, 0.f), &D3DXVECTOR3(-0.3f, -0.3f, -0.3f));
	pSkinned->AddBoneTransform("Bip01-R-Hand", m_Weapon->pTransform);

	//트레일렌더그려줄거
	this->pTrailRender->Transform.AttachTo(m_Weapon->pTransform);
	this->pTrailRender->Transform.SetLocalPosition(0, 1, 0);
	this->pTrailRender->Transform.RotateLocal(90 * ONE_RAD, 90 * ONE_RAD, 0);

}

void cMage::UiUpdate(float timeDelta, cCamera * camera)
{
	if (m_inven->GetWeapon() == NULL &&m_botton == true)
	{
		if (pTrailRender != NULL)
		{
			this->pTrailRender->Transform.ReleaseParent();
			pSkinned->RemoveBoneTransform("Bip01-R-Hand");
		}

		pSkinned->RemoveBoneTransform("Bip01-R-Hand");
		m_Weapon = ITEM_MGR->getItem(3);
		m_Weapon->BoundBox.SetBound(&D3DXVECTOR3(0.f, 1.f, 0.f), &D3DXVECTOR3(-0.3f, -0.3f, -0.3f));
		pSkinned->AddBoneTransform("Bip01-R-Hand", m_Weapon->pTransform);

		//트레일렌더그려줄거
		this->pTrailRender->Transform.AttachTo(m_Weapon->pTransform);
		this->pTrailRender->Transform.SetLocalPosition(0, 1, 0);
		this->pTrailRender->Transform.RotateLocal(90 * ONE_RAD, 45 * ONE_RAD, 0);

		m_botton = false;
	}
	else if (m_inven->GetWeapon() != NULL&& m_botton == false)
	{
		if (pTrailRender != NULL)
		{
			this->pTrailRender->Transform.ReleaseParent();
			pSkinned->RemoveBoneTransform("Bip01-R-Hand");
		}

		m_Weapon = m_inven->GetWeapon();
		m_Weapon->BoundBox.SetBound(&D3DXVECTOR3(0.f, 1.f, 0.f), &D3DXVECTOR3(-0.3f, -0.3f, -0.3f));
		pSkinned->AddBoneTransform("Bip01-R-Hand", m_Weapon->pTransform);
		m_botton = true;

		//트레일렌더그려줄거
		this->pTrailRender->Transform.AttachTo(m_Weapon->pTransform);
		this->pTrailRender->Transform.SetLocalPosition(0, 1, 0);
		this->pTrailRender->Transform.RotateLocal(90 * ONE_RAD, 90 * ONE_RAD, 0);
	}


	if (KEY_MGR->IsOnceDown('I'))
	{
		m_invenOn = !m_invenOn;
		m_inven->SetInvenOn(m_invenOn);
	}

	if (m_invenOn)
	{
		m_inven->update(timeDelta, m_camera, this->pTransform->GetWorldPosition());
		ITEM_MGR->update(timeDelta);
	}

}


void  cMage::Damage(float damage)
{
	m_fHP -= damage;
	if (m_fHP <= FEPSILON)
	{
		m_fHP = 0.0f;
		m_state = DEAD;
		m_strName = MyUtil::SetAnimation(m_state);
		pSkinned->PlayOneShotAfterHold(m_strName);
		return;
	}

	if (m_state == DMG || m_state == DEAD)
	{
		return;
	}


	if (m_state != DMG)
	{
		m_state = DMG;
		m_strName = MyUtil::SetAnimation(m_state);
		pSkinned->PlayOneShotAfterOther(m_strName, "WAIT", 0.3f);
		m_state = IDLE;
	}

}

void cMage::Attack01()
{

}
void cMage::Attack02()
{

}
void cMage::Attack03()
{
	

}

void cMage::SKILL01()
{

}
void cMage::SKILL02()
{

}
void cMage::SKILL03()
{

	if (m_pSkill_SnowStorm->GetIsAttacking())
	{
		RangeCheck(10);

		int size = m_vMonster.size();
		for (int i = 0; i < size; i++)
		{
			LOG_MGR->AddLog("vector[%d] = %d",i, m_vMonster[i]->GetInRange());

			if (!m_vMonster[i]->GetInRange()) continue;
			
			m_vMonster[i]->Damage(100);
			LOG_MGR->AddLog("데미지 받는중");
		}
	}

	//LOG_MGR->AddLog(" %d", m_pSkill_SnowStorm->GetIsAttacking());

}
void cMage::SKILL04()
{

	//if (m_pSkill_DarkRain->GetIsAttacking())
	//{
	//	
	//
	//	int size = m_vMonster.size();
	//	for (int i = 0; i < size; i++)
	//	{
	//		LOG_MGR->AddLog("vector[%d] = %d", i, m_vMonster[i]->GetInRange());
	//
	//		if (!m_vMonster[i]->GetInRange()) continue;
	//
	//		m_vMonster[i]->Damage(100);
	//		LOG_MGR->AddLog("데미지 받는중");
	//	}
	//}

}