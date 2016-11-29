#include "stdafx.h"
#include "cPlayer.h"
#include "cBerserker.h"
#include "cMonsterManager.h"
#include "cMonster.h"
#include "cCamera.h"
#include "cInven.h"
#include "cTrailRender.h"
#include "cShowDamage.h"

//#include "cViewDamage.h"

cBerserker::cBerserker()
{
}

cBerserker::~cBerserker()
{
	SAFE_DELETE(m_ShowDamage);
}

void cBerserker::BaseObjectEnable()
{
	m_UIContainer = new cUI_Container;
	m_UIContainer->UI_Init();


	SetBassClass();
	
	//ĳ������ �׷��� ��ġ�� ����
	pTransform->SetWorldPosition(0, pTerrain->GetHeight(0, 0), 0);
	BaseObjectBoundBox();

	BasixWeaponSet();

	m_state = IDLE;
	m_strName = MyUtil::SetAnimation(m_state);

	m_botton = false;

	m_fHP = 3000;					//�Ż�����
	m_currentHp = 3000;				//�Ż�����
	m_attackLength = 5;				//�Ż�����
	m_damage = 100;					//�Ż�����
	m_isAttack = false;				//�Ż�����
	m_invenOn = false;				//�Ż�����

	m_vMonster = m_pMonMgr->GetMonsters();	//�޾ƿ� ����������
	m_target = NULL;			//Ÿ���õ� ����
	
	m_pMove->init(pTransform, pTerrain, m_camera, NULL);

	m_camera->AttachTo(pTransform);			//ī�޶����
	m_camera->SetLocalPosition(0, 2, -5);

	m_atkCnt = 1;			//��Ÿ ���൵
	m_time = 0;				//��Ÿ ����
	m_testtime = 0;			//�׽�Ʈ�� �αש��½ð�
	m_Invintime = 0;		//�����ð�ü��ũ

	//skill
	SkillInit();
	SetTickCount();
	
	m_ShowDamage = new cShowDamage;
}

void cBerserker::BaseObjectUpdate(float timeDelta)
{
	m_UIContainer->UI_Update();

	m_ShowDamage->Update(timeDelta);
	CamControl(timeDelta);
	Move(timeDelta);

	//ƽ������Ʈ

	for (int i = 0; i < BK_TICKMAX; i++)
	{
		m_tick[i]->tickUpdate(TIME_MGR->GetFrameDeltaSec());
	}


	if (!m_invenOn)
	{
		Monster_pick();
	}
	UiUpdate(timeDelta, m_camera);
	if (this->pTrailRender != NULL)
		this->pTrailRender->Update(timeDelta);

	/*
	//======================�׽�Ʈ�� �ִ� Ȯ��==================================
	if (KEY_MGR->IsOnceDown(VK_NUMPAD1))
		this->pSkinned->PlayOneShotAFTERIDLE("SK_BUFF", 0.3, 0.15);

	if (KEY_MGR->IsOnceDown(VK_NUMPAD2))
		this->pSkinned->PlayOneShotAFTERIDLE("SK_ATKUP", 0.3, 0.15);

	if (KEY_MGR->IsOnceDown(VK_NUMPAD3))
		this->pSkinned->PlayOneShotAFTERIDLE("SK_CRASH", 0.3, 0.15);

	if (KEY_MGR->IsOnceDown(VK_NUMPAD4))
		this->pSkinned->PlayOneShotAFTERIDLE("SK_SWING", 0.3, 0.15);

	if (KEY_MGR->IsOnceDown(VK_NUMPAD5))
		this->pSkinned->PlayOneShotAFTERIDLE("SK_HOWL", 0.3, 0.15);

	if (KEY_MGR->IsOnceDown(VK_NUMPAD6))
		this->pSkinned->PlayOneShotAFTERIDLE("SK_ACCEL", 0.3, 0.15);

	if (KEY_MGR->IsOnceDown(VK_NUMPAD7))
		this->pSkinned->PlayOneShotAFTERIDLE("SK_JUMPATK", 0.3, 0.15);

	if (KEY_MGR->IsOnceDown(VK_NUMPAD8))
		this->pSkinned->PlayOneShotAFTERIDLE("SK_ESCAPE", 0.3, 0.15);
	
	//==============================================================
	*/
	
	m_time += timeDelta;
	m_Invintime += timeDelta;
	m_testtime += timeDelta;

	//
	//=================��Ÿ=================
	//
	
	if (LengthCheck() && !m_isAttack && KEY_MGR->IsOnceDown('1'))
	{
		m_isAttack = true;
		m_time = 0;
		switch (m_atkCnt)
		{
			case 1 : 
				m_state = ATK_01;
				Attack01();
				m_atkCnt++;
				break;
			case 2: 
				m_state = ATK_02;
				Attack02();
				m_atkCnt++;
				break;
			case 3: 
				pSkinned->ChangeBoneTransform("BN_Weapon_R", "BN_Weapon_L");// ��Ÿ�� ĥ�� BN_Weapon_L��
				m_state = ATK_03;
				Attack03();
				m_atkCnt = 1;
				break;
		}
		m_strName = MyUtil::SetAnimation(m_state);
		this->pSkinned->PlayOneShotAFTERIDLE(m_strName, 0.3, 0.15);
	}

	//��ų2 - ����
	if (!m_isAttack && KEY_MGR->IsOnceDown('2'))
	{
		m_isAttack = true;
		m_time = 0;

		RangeCheck(10);

		m_state = SK_CHARGE;
		m_strName = MyUtil::SetAnimation(m_state);
		this->pSkinned->Play(m_strName, 0.3);
		m_state = IDLE;
		m_ArmorCrash->SelectSkill();
		m_ArmorCrash->Effect_Init();
	}

	if (m_ArmorCrash->GetAtkCount() == 1)
	{
		m_state = SK_CHARGE_ATK;
		m_strName = MyUtil::SetAnimation(m_state);
		this->pSkinned->PlayOneShotAFTERIDLE(m_strName, 0.3, 0.15);
	}


	//��ų3 - ����
	if (!m_isAttack && KEY_MGR->IsOnceDown('3'))
	{
		m_isAttack = true;
		m_time = 0;
	
		m_state = SK_SWING;
		m_strName = MyUtil::SetAnimation(m_state);
		this->pSkinned->PlayOneShotAFTERIDLE(m_strName, 0.3, 0.15);
		m_state = IDLE;
		m_Swing->Effect_Init();
		m_Swing->StartCasting();
	}

	//��ų4 - ?
	if (!m_isAttack && KEY_MGR->IsOnceDown('4'))
	{
		
	}

	//��ų5 - ����ũ
	if (!m_isAttack && KEY_MGR->IsOnceDown('5'))
	{
		m_isAttack = true;
		m_time = 0;

		LOG_MGR->AddLog("����ȭ ����");
		m_damage += 100;

		m_state = SK_BUFF;
		m_strName = MyUtil::SetAnimation(m_state);
		this->pSkinned->PlayOneShotAFTERIDLE(m_strName, 0.3, 0.15);
		m_state = IDLE;
		m_Burserk->Effect_Init();
		m_Burserk->StartCasting();
	}

	SKILL01();			//�Ͽ︵
	SKILL02();			//����
	SKILL03();			//
	SKILL04();			//����

	
	m_Swing->BaseObjectUpdate(timeDelta, this->pTransform->GetWorldPosition());
	m_Swing->Effect_Update(timeDelta);

	m_Burserk->BaseObjectUpdate(timeDelta, this->pTransform->GetWorldPosition());
	m_Burserk->Effect_Update(timeDelta);

	Ray ray;
	POINT ptMousePos = GetMousePos();
	D3DXVECTOR2 screenPos(ptMousePos.x, ptMousePos.y);
	m_camera->ComputeRay(&ray, &screenPos);
	D3DXVECTOR3		mousePos;
	pTerrain->IsIntersectRay(&mousePos, &ray);

	m_ArmorCrash->BaseObjectUpdate(timeDelta, this->pTransform->GetWorldPosition(), mousePos);
	m_ArmorCrash->Effect_Update(timeDelta);


	

	//���� ��Ÿ�� 1.5��
	if (m_time > 1)
	{
		if (m_atkCnt != 1)
		{
			m_isAttack = false;
			m_state = IDLE;
		}
		else if (m_atkCnt == 1)
		{
			if (m_time > 1.5)
			{
				m_isAttack = false;
				m_state = IDLE;
			}
		}
	}

	if (pSkinned->GetTime() > 0.7)
	{
		if (pSkinned->IsCurrentBone("BN_Weapon_L"))
			pSkinned->ChangeBoneTransform("BN_Weapon_L", "BN_Weapon_R");
	}

	//��Ÿ �ʱ�ȭ�ð�
	if (m_time > 5)
		m_atkCnt = 1;

	//test�� �α� ����� 
	if (m_testtime > 1)
	{
		LOG_MGR->AddLog("hp : %d", m_currentHp);
		m_testtime = 0;
	}

	m_camera->ShakeUpdate(timeDelta);

	if (m_isHeat && m_Invintime > 1)
	{
		m_state = IDLE;
	}
}

void cBerserker::BaseObjectRender()
{
	this->pSkinned->Render(this->pTransform);
	
	this->BoundBox.RenderGizmo(this->pTransform);

	m_Weapon->Render();
	if (this->pTrailRender != NULL)
	{
		this->pTrailRender->RenderDistort(this->m_camera);
	}

	m_Swing->BaseObjectRender();
	m_Swing->Effect_Render();
	m_Burserk->Effect_Render();
	m_ArmorCrash->BaseObjectRender();
	m_ArmorCrash->Effect_Render();
	//m_ViewDamage->Render();
}

void cBerserker::BaseSpriteRender()
{
	UiURender();
	m_ShowDamage->Render();
	m_UIContainer->UI_Render();

	//char temp[32];
	//sprintf_s(temp, "../Resources/Textures/num_%d.tga", 2);
	//
	//RECT rc = RectMake(0, 0, 64, 64);
	//
	//SPRITE_MGR->DrawTexture(
	//	RESOURCE_TEXTURE->GetResource(temp),
	//	&rc,
	//	WINSIZE_X / 2, WINSIZE_Y / 2,
	//	0xffffffff,
	//	NULL
	//);
}

void cBerserker::BaseObjectBoundBox()
{
	BoundBox.SetBound(&D3DXVECTOR3(0, 1.5f, 0), &D3DXVECTOR3(0.5f, 1.5f, 0.5f));
}

void cBerserker::Damage(float damage)
{
	m_Invintime = 0;
	m_isHeat = true;

	m_currentHp -= damage;
	if (m_currentHp <= FEPSILON)
	{
		m_currentHp = 0.0f;
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
		pSkinned->PlayOneShotAfterOther(m_strName, "IDLE", 0.3f);
	}
}



void cBerserker::Attack01()
{	
	int damage = m_damage * 1;
	damage = 5; 
	//damage = RandomIntRange(damage - 10, damage + 10);

	m_ShowDamage->SetNumber(damage, m_target->pTransform);
	//m_ViewDamage->SetNumber(damage, m_target->pTransform);//���⼭ Ʈ�������Ѱ������ .

	LOG_MGR->AddLog("%d������ ��", damage);
	m_target->Damage(damage);
}

void cBerserker::Attack02()
{
	int damage = m_damage * 2;
	damage = 10;
	//damage = RandomIntRange(damage - 10, damage + 10);

	m_ShowDamage->SetNumber(damage, m_target->pTransform);
	//m_ViewDamage->SetNumber(damage, m_target->pTransform);

	LOG_MGR->AddLog("%d������ ��", damage);
	m_target->Damage(damage);
}

void cBerserker::Attack03()
{
	int damage = m_damage * 3;
	damage = 19;
	//damage = RandomIntRange(damage - 10, damage + 10);
	
	m_ShowDamage->SetNumber(damage, m_target->pTransform);
	//m_ViewDamage->SetNumber(damage, m_target->pTransform);

	LOG_MGR->AddLog("%d������ ��", damage);
	m_target->Damage(damage);
}


void  cBerserker::SkillInit()
{
	m_Swing = new cSkill_Swing;
	m_Swing->SetActive(true);
	m_Swing->BaseObjectEnable(pTransform->GetWorldPosition(), 10.f, 1, 200, 50);	//��ý����� ĳ���� ī��Ʈ 1

	m_Howling = new cSkill_Howling;
	m_Howling->SetActive(true);
	m_Howling->BaseObjectEnable(pTransform->GetWorldPosition(), 10.f, 1, 5, 60);
	
	m_Burserk = new cSkill_Burserk;
	m_Burserk->SetActive(true);
	m_Burserk->BaseObjectEnable(pTransform->GetWorldPosition(), 70, 600, 20);

	m_ArmorCrash = new cSkill_AmorCrash;
	m_ArmorCrash->SetActive(true);
	m_ArmorCrash->BaseObjectEnable(pTransform->GetWorldPosition(), 2, 10, 1, 100, 10);

	m_aniCount = 0;
}


void cBerserker::SKILL01()
{
}

void cBerserker::SKILL02()
{
	int damage = m_damage * 2;

	if (m_Swing->GetIsAttacking())
	{
		RangeCheck(10);
		int size = m_vMonster.size();

		for (int i = 0; i < size; i++)
		{
			if (!m_vMonster[i]->GetInRange()) continue;
			damage = RandomIntRange(damage - 10, damage + 10);

			if (m_tick[BK_SWING]->tickStart())
			{
				//�̰� ƽ�������ιٲ�
				//if (PHYSICS_MGR->IsOverlap(m_Weapon, m_vMonster[i]))
				{
					LOG_MGR->AddLog("%d ��������", damage);
					m_ShowDamage->SetNumber(damage, m_vMonster[i]->pTransform);
					m_vMonster[i]->Damage(damage);
				}
			}
		}
	}
}

void cBerserker::SKILL03()
{
	
}

void cBerserker::SKILL04()
{
	//if (m_Burserk->GetIsInBuff())
	//{
	//	if (m_Burserk->m_AttackingCount > m_Burserk->m_AttackingTime)
	//	{
	//		m_damage -= 100;
	//		LOG_MGR->AddLog("���� ��");
	//	}
	//}
}

void cBerserker::BasixWeaponSet()
{
	//���������� �������ٰ�
	m_Weapon = new cItem;

	m_Weapon = ITEM_MGR->getItem(2);
	m_Weapon->BoundBox.SetBound(&D3DXVECTOR3(0.f, 1.f, 0.f), &D3DXVECTOR3(-0.3f, -0.3f, -0.3f));
	pSkinned->AddBoneTransform("BN_Weapon_R", m_Weapon->pTransform);

	//Ʈ���Ϸ����׷��ٰ�
	this->pTrailRender->Transform.AttachTo(m_Weapon->pTransform);
	this->pTrailRender->Transform.SetLocalPosition(0, 1, 0);
	this->pTrailRender->Transform.RotateLocal(90 * ONE_RAD, 90 * ONE_RAD, 0);

}

void cBerserker::SetTickCount()
{
	for (int i = 0; i < TICKMAX; i++)
	{
		m_tick[i] = new cTickFunc;
		m_tick[i]->init(0.3f);
	}

	m_tick[BK_HOWL]->init(0.5f);
	m_tick[BK_SWING]->init(0.5f);
	m_tick[BK_ACCEL]->init(0.3f); //�;����𸣰پ�
}

void cBerserker::UiUpdate(float timeDelta, cCamera* camera)
{
	if (m_inven->GetWeapon() == NULL &&m_botton == true)
	{
		if (pTrailRender != NULL)
		{
			this->pTrailRender->Transform.ReleaseParent();
			pSkinned->RemoveBoneTransform("BN_Weapon_R");
		}

		pSkinned->RemoveBoneTransform("BN_Weapon_R");
		m_Weapon = ITEM_MGR->getItem(2);
		m_Weapon->BoundBox.SetBound(&D3DXVECTOR3(0.f, 1.f, 0.f), &D3DXVECTOR3(-0.3f, -0.3f, -0.3f));
		pSkinned->AddBoneTransform("BN_Weapon_R", m_Weapon->pTransform);

		//Ʈ���Ϸ����׷��ٰ�
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
			pSkinned->RemoveBoneTransform("BN_Weapon_R");
		}

		m_Weapon = m_inven->GetWeapon();
		m_Weapon->BoundBox.SetBound(&D3DXVECTOR3(0.f, 1.f, 0.f), &D3DXVECTOR3(-0.3f, -0.3f, -0.3f));
		pSkinned->AddBoneTransform("BN_Weapon_R", m_Weapon->pTransform);
		m_botton = true;

		//Ʈ���Ϸ����׷��ٰ�
		this->pTrailRender->Transform.AttachTo(m_Weapon->pTransform);
		this->pTrailRender->Transform.SetLocalPosition(0, 1, 0);
		this->pTrailRender->Transform.RotateLocal(90 * ONE_RAD, 90 * ONE_RAD, 0);
		
		//this->pTrailRender->Transform.AttachTo(m_inven->GetWeapon()->pTransform);
		//this->pTrailRender->Transform.SetLocalPosition(0, 1, 0);
		//this->pTrailRender->Transform.RotateLocal(90 * ONE_RAD, 90 * ONE_RAD, 0);
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
