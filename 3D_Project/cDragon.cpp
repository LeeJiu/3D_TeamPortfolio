#include "stdafx.h"
#include "cDragon.h"
#include "cPlayer.h"
#include "cTrailRender.h"

cDragon::cDragon()
{
	m_collCount = COLLISION;
	m_fHP = 5500.f;
	dieAniTime = 0.f;
	//TIME_MGR->GetFrameDeltaSec();
}


cDragon::~cDragon()
{
	for (int i = 1; i < COLLISION; i++)
	{
		SAFE_DELETE(m_pBoneTrans[i]);
	}

	for (int i = 1; i < 5; i++)
	{
		SAFE_DELETE(m_pCollTrans[i]);
	}

	for (int i = 0; i < TICKMAX; i++)
	{
		SAFE_DELETE(m_tick[i]);
	}

	m_pBreathParticle->Release();
	SAFE_DELETE(m_pBreathParticle);

	for (int i = 0; i < COLLCIRCLE; i++)
	{
		SAFE_DELETE(m_Skill_Meteo[i]);
		SAFE_DELETE(m_Skill_Thunder[i]);

	}

	SAFE_DELETE(m_pTrailLEye);
	SAFE_DELETE(m_pTrailREye);
}

void cDragon::BaseObjectEnable()
{
	m_pBoneTrans[BODY] = pTransform;     // pTrans ���� 0 ���� �Է�
	m_pCollTrans[0] = pTransform;

	// ���� ���� Ʈ���� �ʱ�ȭ
	for (int i = 1; i < COLLISION; i++)
	{
		m_pBoneTrans[i] = new cTransform; //���� �Ҵ� ���ִ°�. 
	}

	for (int i = 1; i < 5; i++)
	{
		m_pCollTrans[i] = new cTransform; //���� �Ҵ� ���ִ°�. 
	}
	for (int i = 0; i < TICKMAX; i++)
	{
		m_tick[i] = new cTickFunc;
		m_tick[i]->init(0.3f);
	}
	m_tick[BasicAtt]->init(1.f);
	m_tick[HeadAtt]->init(0.3f);
	m_tick[Breath]->init(0.3f);
	m_tick[Earthquake]->init(0.8f);
	m_tick[Pattern]->init(10.f);

	//=================== �ʱ�ȭ ================
	//pTransform , ���� �����϶� ���� trans 


	pSkinned->AddBoneTransform("Bip01-HeadNub", m_pBoneTrans[HEAD]);
	pSkinned->AddBoneTransform("Bip01-L-Hand_Bone", m_pBoneTrans[LHANAD]);
	pSkinned->AddBoneTransform("Bip01-R-Hand_Bone", m_pBoneTrans[RHAND]);

	//0����
	BoundBox.Init(D3DXVECTOR3(-4, 0, -4), D3DXVECTOR3(4, 8, 4.5));
	m_bound[BODY].Init(D3DXVECTOR3(-4, 0, -4), D3DXVECTOR3(4, 8, 4.5));
	//�Ӹ�
	m_bound[HEAD].Init(D3DXVECTOR3(-2, -1, -2), D3DXVECTOR3(0, 1, 0.5));
	//����
	m_bound[LHANAD].Init(D3DXVECTOR3(0, -1, -1), D3DXVECTOR3(2, 1, 1));
	//������
	m_bound[RHAND].Init(D3DXVECTOR3(0, -1, -1), D3DXVECTOR3(2, 1, 1));

	//ó�� ���۽� �÷��� �ִϸ��̼�
	this->pSkinned->Play("Spawn", 0.3f);
	this->pSkinned->Stop();
	collPosUpdate();
	// ���� ���� ���� ���� �� 
	m_spone.worldCenter = pTransform->GetWorldPosition();
	m_spone.radius = 100.f;
	// ��Ÿ �����Ÿ�
	m_basicAttack.radius = m_bound[BODY].radius;

	//�ִϸ��̼� ���°�
	isBattle = false;         //������?
	isMove = false;           // �����̴���?
	isBasicAttack = false;    // �⺻ ������?
	isBreath = false;         // �극����?
	isEarthquake = false;     // ������?
	isHeadAtt = false;         // �Ӹ� ġ��
	isNoneBasicAttack = false;// �극�� , ���� ,�Ӹ� ġ�� �� �̴�?
	//��ų ����� ����. 
	skillChance = 0;          // max 3 �� 1,2,3 ���
	//�׾���?
	isDie = false;



	// ���� ���� 
	for (int i = 0; i < COLLCIRCLE; i++)
	{
		m_circle[i].radius = 10.f;
		m_Skill_Meteo[i] = new cSkill_Meteo;
		m_Skill_Meteo[i]->BaseObjectEnable(pTransform->GetWorldPosition(), 10, 100, 100, 200, 1);
		m_Skill_Meteo[i]->Effect_Init();
		m_Skill_Thunder[i] = new cSkill_Thunder;
		m_Skill_Thunder[i]->BaseObjectEnable(pTransform->GetWorldPosition(), 10, 100, 100, 200, 1);
		m_Skill_Thunder[i]->Effect_Init();

	}

	TrailSetting();
	initParticle();

	renderGizimo = false;
}

void cDragon::BaseObjectUpdate(float timeDelta)
{
	//�׽�Ʈ��
	//if (KEY_MGR->IsOnceDown('B'))
	//{
	//	m_fHP = -500.f;
	//	LOG_MGR->AddLog("��������: %f", dieAniTime);
	//}

	if (m_fHP < 0.f)
	{
		dieUpdate(timeDelta);
	}
	else if (m_fHP > 0.f)
	{
		m_nowAni = pSkinned->GetNowPlayingAni();
		int chance = MyUtil::RandomIntRange(0, 10);

		// ���� ������ ������ 
		if (battleRange() == true && isBattle == true)
		{
			//ó�� ���ܳ����� �ִϸ��̼� ������~
			//�÷��̾� �������� �����
			if (isBasicAttack == false && isNoneBasicAttack == false)
			{
				MoveToPlayer();
			}
			// �浹 üũ�� �ʿ��� Trans������ ���� ����. 
			collPosUpdate();

			// ��Ÿ ���� �ȿ� ������ ��Ÿ ������ �Ѵ�. 
			if (basicRange() == true)
			{
				if (chance == 5 && isBasicAttack != true)  // 1/10 Ȯ���� �Ӹ�ġ�� /
				{
					isHeadAtt = true;
					isNoneBasicAttack = true;
					if (SOUND_MGR->isPlaySound("dra_HeadATK") == false)
					{
						SOUND_MGR->play("dra_HeadATK", 0.8f);
					}
				}
				else if (chance == 3 && isBasicAttack != true)
				{
					isEarthquake = true;     // ������?
					isNoneBasicAttack = true;// �극�� , ���� ,�Ӹ� ġ�� �� �̴�?
					LOG_MGR->AddLog("��Ÿ�� �ߵ�: %d", skillChance);
					makeCircleQuad();
					if (SOUND_MGR->isPlaySound("dra_Meteo") == false)
					{
						SOUND_MGR->play("dra_Meteo", 0.8f);
					}
				}
				else
				{
					//�⺻ ������ �ϱ� ���ؼ��� ����� �Ѵ�. 
					isMove = false;
					isBasicAttack = true;     // �⺻ ���� 
					if (SOUND_MGR->isPlaySound("dra_BasicATK")==false)
					{
						SOUND_MGR->play("dra_BasicATK", 0.8f);
					}
				}

			}
			else // �⺻ ���� ���� ���� ������. 
			{
				//��ų ������ �ʱ� �ؾ� �� ��
				//skillChance =0, isNoneBasicAttack = false, ��ų�� ����� ��
				if (m_tick[Pattern]->tickStart())
				{

					if (skillChance == 0)
					{
						skillChance = MyUtil::RandomIntRange(1, 3);
						isMove = false;
						isBasicAttack = false;
						//LookPos(m_pPlayer->pTransform->GetWorldPosition());
						MoveToPlayer();
						switch (skillChance)
						{
						case 1:
							if (isBreath == true)break;
							isBreath = true;         // �극����?
							isNoneBasicAttack = true;// �극�� , ���� ,�Ӹ� ġ�� �� �̴�?
							if (SOUND_MGR->isPlaySound("dra_Breath") == false)
							{
								SOUND_MGR->play("dra_Breath", 0.8f);
							}
							break;
						case 2:
							if (isEarthquake == true)break;
							isEarthquake = true;     // ������?
							isNoneBasicAttack = true;// �극�� , ���� ,�Ӹ� ġ�� �� �̴�?
							LOG_MGR->AddLog("����: %d", skillChance);
							makeCircleQuad();
							for (int i = 0; i < COLLCIRCLE; i++)
							{
								m_Skill_Meteo[i]->Effect_Init();
								m_Skill_Meteo[i]->StartCasting();
								m_Skill_Thunder[i]->Effect_Init();
								m_Skill_Thunder[i]->StartCasting();
							}
							if (SOUND_MGR->isPlaySound("dra_Thunder") == false)
							{
								SOUND_MGR->play("dra_Thunder", 0.8f);
							}

							break;

						}
					}
				}

			}
		}
		else if (battleRange() == true && isBattle == false)
		{
			spawn();
		}
		// �÷��̾ ����ĥ�� ���� ������ �ڵ�
		else
		{
			MoveToSpone(m_spone.worldCenter);
		}

		if (isBattle == true)
		{
			if (isBasicAttack == true)
			{
				basicAttackUpdate();
			}
			if (isBreath == true)
			{
				breathUpdate();
			}
			if (isEarthquake == true)
			{
				earthUpate();
			}
			if (isHeadAtt == true)
			{
				HeadAttUpate();
			}
			aniManager();

			// �������϶� ������Ʈ �ƴϸ� ���� �ʰ� �Ѵ�. 
			for (int i = 0; i < TICKMAX; i++)
			{
				m_tick[i]->tickUpdate(TIME_MGR->GetFrameDeltaSec());
			}
			m_pBreathParticle->Update(TIME_MGR->GetFrameDeltaSec());

			for (int i = 0; i < COLLCIRCLE; i++)
			{
				m_Skill_Meteo[i]->BaseObjectUpdate(timeDelta, pTransform->GetWorldPosition(), m_circle[i].worldCenter);
				m_Skill_Meteo[i]->Effect_Update(timeDelta);
				m_Skill_Thunder[i]->BaseObjectUpdate(timeDelta, pTransform->GetWorldPosition(), m_quadPos[i]);
				m_Skill_Thunder[i]->Effect_Update(timeDelta);
			}

			m_pTrailLEye->Update(timeDelta);					//Ʈ���Ϸ��� ������Ʈ
			m_pTrailREye->Update(timeDelta);					//Ʈ���Ϸ��� ������Ʈ
		}


		// if (KEY_MGR->IsStayDown('L'))
		// {
		// 	m_pBreathParticle->pTransform->SetWorldPosition(0, 9, 0);
		// 	m_pBreathParticle->StartEmission();
		// 
		// }
		// else
		// {
		// 	*m_pBreathParticle->pTransform = *pTransform;
		// 	m_pBreathParticle->StopEmission();
		// }


		//=================== ������Ʈ ==============
	}




}

void cDragon::BaseObjectBoundBox()
{
	//=================== �ٿ�� �ڽ� �߰� ======
}

void cDragon::Damage(float fDamage)
{
	//=================== ������ ���� �Լ� ======
	m_fHP -= fDamage;
}
void cDragon::BaseObjectRender()
{
	//=================== ���� �Լ� =============
	//�� �̸� 
	// �Ӹ� Bip01-HeadNub
	// ���� Bip01-L-Hand_Bone
	// ���� Bip01-R-Hand_Bone
	// ���� Bip01-R-Foot_Bone
	// �޹� Bip01-L-Foot_Bone
	// ������ BN_Wing_R003,007
	// �޳��� BN_Wing_L003,007
	m_pTrailLEye->Render();							//Ʈ���Ϸ��� ������
	m_pTrailREye->Render();							//Ʈ���Ϸ��� ������

	pSkinned->Render(m_pBoneTrans[0]);

	if (renderGizimo == true)
	{
		for (int i = 0; i < COLLISION; i++)
		{
			m_bound[i].RenderGizmo(m_pBoneTrans[i]);
		}

		for (int i = 0; i < 5; i++)
		{
			m_pCollTrans[i]->RenderGimozo(true);
		}

		GIZMO_MGR->WireSphere(m_basicAttack.worldCenter, m_basicAttack.radius, 0xffff0000);
		GIZMO_MGR->WireSphere(m_spone.worldCenter, m_spone.radius, 0xffffff00);

		GIZMO_MGR->Sector(pTransform->GetWorldPosition(), pTransform->GetForward(), 50, 18 * ONE_RAD);

		for (int i = 0; i < COLLCIRCLE; i++)
		{
			GIZMO_MGR->Quad(m_quad[i]);
			GIZMO_MGR->WireSphere(m_circle[i].worldCenter, m_circle[i].radius, 0xffff0000);

		}
	}

	// ��ų ����Ʈ �κ�
	for (int i = 0; i < COLLCIRCLE; i++)
	{
		m_Skill_Meteo[i]->BaseObjectRender();
		m_Skill_Meteo[i]->Effect_Render();
		m_Skill_Thunder[i]->BaseObjectRender();
		m_Skill_Thunder[i]->Effect_Render();
	}
	// ��ƼŬ �κ�
	m_pBreathParticle->Render();

}

void cDragon::TrailSetting()
{
	pSkinned->AddBoneTransform("BN_Eye_L", &m_LEyeTrans);
	pSkinned->AddBoneTransform("BN_Eye_R", &m_REyeTrans);

	m_pTrailLEye = new cTrailRender();
	m_pTrailLEye->Init(
		1.0f,					//���� ���̺� Ÿ�� ( �̰� ũ�� ȯ��ť ����� Ŀ���� ������ �������� �����ִ� )
		0.1f,					//��
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/TrailTest.png"),	//���� Texture
		D3DXCOLOR(0.5, 1, 0, 1),												//���� Texture �� �׸��� �÷�
		NULL
		);

	m_pTrailREye = new cTrailRender();
	m_pTrailREye->Init(
		1.0f,
		0.1f,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/TrailTest.png"),
		D3DXCOLOR(0.5, 1, 0, 1),
		NULL
		);

	m_pTrailLEye->Transform.AttachTo(&m_LEyeTrans);
	m_pTrailREye->Transform.AttachTo(&m_REyeTrans);

	m_LEyeTrans.SetLocalPosition(-10, 0, 0);
	m_REyeTrans.SetLocalPosition(10, 0, 0);
}

void cDragon::collPosUpdate()
{
	//��ǥ ����.
	//0���� ���� �ٿ�� �ڽ� ����
	BoundBox.GetWorldBox(m_pBoneTrans[BODY], m_collPos);
	//m_bound[BODY].GetWorldBox(m_pBoneTrans[BODY], m_collPos);
	m_pCollTrans[1]->SetWorldPosition(m_collPos[0]);
	m_pCollTrans[2]->SetWorldPosition(m_collPos[3]);
	m_pCollTrans[3]->SetWorldPosition(m_collPos[4]);
	m_pCollTrans[4]->SetWorldPosition(m_collPos[7]);
	//��Ÿ�� ���� ��ǥ ����
	m_basicAttack.worldCenter = pTransform->GetWorldPosition();
}

bool cDragon::battleRange()
{
	D3DXVECTOR3 Length = m_spone.worldCenter - m_pPlayer->pTransform->GetWorldPosition();
	float dist = D3DXVec3Length(&Length);

	if (dist < m_spone.radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool cDragon::basicRange()
{
	D3DXVECTOR3 Length = m_basicAttack.worldCenter - m_pPlayer->pTransform->GetWorldPosition();
	float dist = D3DXVec3Length(&Length);

	if (dist < m_basicAttack.radius + 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void cDragon::MoveToSpone(D3DXVECTOR3 target)
{
	//���� �� ��� �ൿ�� �ϰ� �ִٸ� ���� �Ѵ�. 
	if (isBasicAttack == true)return;
	//���� ����

	D3DXVECTOR3 currentPos = pTransform->GetWorldPosition();
	Ray ray;
	ray.direction = D3DXVECTOR3(0, -1, 0);
	ray.origin = currentPos;
	ray.origin.y += 3;


	//if (PHYSICS_MGR->IsOverlap(m_pPlayer->pTransform, &m_pPlayer->BoundBox, pTransform, &m_Bound[0]))
	//{
	//	return;
	//}
	if (PHYSICS_MGR->IsPointSphere(pTransform, 1.f, target))
	{
		isMove = false;
		isBattle = false;
		stateInit();

		if (strcmp(m_nowAni.c_str(), "Spawn") != 0)
		{
			this->pSkinned->Play("Spawn", 0.3f);
			this->pSkinned->Stop();
		}
		return;

	}

	//�Ÿ��� ���Ѵ�. / �󿡼�-----> Ÿ�� 
	D3DXVECTOR3 dirToTarget = target - pTransform->GetWorldPosition();
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
	ray.origin = VecLerp(currentPos, target, t);
	ray.origin.y += 3;	//�Ӹ� ���� ���δ�.


	D3DXVECTOR3 pos;
	//���̶� �ͷ��� üũ����
	if (pTerrain->IsIntersectRay(&pos, &ray))
	{
		pTransform->SetWorldPosition(pos);
		currentPos = pos;
		//���°�
		isMove = true;
	}

	// ���̶� �ɸ��� �Ÿ��� �־����� ���̰� ���̻� �Ѿ�� ���ϰ� �����.
	float rayCheckDis = D3DXVec3Length(&(ray.origin - currentPos));
	if (rayCheckDis > t + 0.01f) // ��� ���� �ӷ� ���� ���� ���� ��.
	{
		ray.origin = currentPos;
		ray.origin.y += 3;
	}
}

void cDragon::MoveToPlayer()
{
	//���� �� ��� �ൿ�� �ϰ� �ִٸ� ���� �Ѵ�. 
	if (isBasicAttack == true)return;
	//���� ����

	D3DXVECTOR3 currentPos = pTransform->GetWorldPosition();
	Ray ray;
	ray.direction = D3DXVECTOR3(0, -1, 0);
	ray.origin = currentPos;
	ray.origin.y += 3;


	//if (PHYSICS_MGR->IsOverlap(m_pPlayer->pTransform, &m_pPlayer->BoundBox, pTransform, &m_Bound[0]))
	//{
	//	return;
	//}
	if (PHYSICS_MGR->IsPointSphere(pTransform, m_basicAttack.radius, m_pPlayer->pTransform->GetWorldPosition()))
	{
		isMove = false;
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
		//���°�
		isMove = true;
	}

	// ���̶� �ɸ��� �Ÿ��� �־����� ���̰� ���̻� �Ѿ�� ���ϰ� �����.
	float rayCheckDis = D3DXVec3Length(&(ray.origin - currentPos));
	if (rayCheckDis > t + 0.01f) // ��� ���� �ӷ� ���� ���� ���� ��.
	{
		ray.origin = currentPos;
		ray.origin.y += 3;
	}
}
void cDragon::LookPos(D3DXVECTOR3 target)
{

	//�Ÿ��� ���Ѵ�. / �󿡼�-----> Ÿ�� 
	D3DXVECTOR3 dirToTarget = target - pTransform->GetWorldPosition();
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
}
void cDragon::basicAttackUpdate()
{
	if (isNoneBasicAttack == true)return;
	if (strcmp(m_nowAni.c_str(), "ATK_02") == 0)
	{

		float aniTime = pSkinned->GetTime();

		if (aniTime > 0.9f)
		{
			if (m_tick[BasicAtt]->tickStart())
			{
				m_pPlayer->Damage(10.f);
				// �÷��̾� ������ �ִ� �κ�,
				LOG_MGR->AddLog(": Damage.2f", aniTime);

			}
		}

		if (aniTime > 0.99f)
		{
			//LOG_MGR->AddLog(": %.2f", aniTime);
			stateInit();

		}
	}
}

void cDragon::aniManager()
{
	// �����̴� �ִϸ��̼�


	if (isMove == true && isBasicAttack == false
		&& isNoneBasicAttack == false)
	{
		if (strcmp(m_nowAni.c_str(), "Run_F") == 0)return;
		this->pSkinned->Play("Run_F", 0.3);
	}// �⺻ ����
	else if (isBasicAttack == true
		&& isNoneBasicAttack == false)
	{
		if (strcmp(m_nowAni.c_str(), "ATK_02") == 0)return;
		this->pSkinned->Play("ATK_02", 0.3);
	}// �극��
	else if (isBreath == true && isNoneBasicAttack == true)
	{
		if (strcmp(m_nowAni.c_str(), "SK_Firing_02") == 0)return;
		this->pSkinned->Play("SK_Firing_02", 0.3);
	}// ����
	else if (isEarthquake == true && isNoneBasicAttack == true)
	{
		if (strcmp(m_nowAni.c_str(), "ATK_01") == 0)return;
		this->pSkinned->Play("ATK_01", 0.3);
	}// �Ӹ� ġ�� 
	else if (isHeadAtt == true && isNoneBasicAttack == true)
	{
		if (strcmp(m_nowAni.c_str(), "SK_Firing_01") == 0)return;
		this->pSkinned->Play("SK_Firing_01", 0.3);
	}


}

void cDragon::spawn()
{

	if (isBattle == false)
	{
		if (strcmp(m_nowAni.c_str(), "Spawn") == 0)
		{
			float aniTime = pSkinned->GetTime();

			if (aniTime > 0.99f)
			{
				isBattle = true;
			}
		}
		if (pSkinned->GetIsPlay() == false)
		{
			this->pSkinned->Play("Spawn", 0.3f);
			if (SOUND_MGR->isPlaySound("dra_Spawn") == false)
			{
				SOUND_MGR->play("dra_Spawn", 0.8f);
			}
		}
		if (strcmp(m_nowAni.c_str(), "Spawn") == 0)return;
		this->pSkinned->Play("Spawn", 0.3f);

	}
}


void cDragon::breathUpdate()
{
	if (strcmp(m_nowAni.c_str(), "SK_Firing_02") == 0)
	{
		float aniTime = pSkinned->GetTime();

		if (0.58f < aniTime&&aniTime <= 0.59f)
		{
			m_pBreathParticle->StartEmission();
			m_pBreathParticle->pTransform->SetWorldPosition(m_pBoneTrans[HEAD]->GetWorldPosition());
			m_pBreathParticle->pTransform->SetRotateWorld(pTransform->GetWorldRotateMatrix());
			LOG_MGR->AddLog("�극�� ����: %.2f", aniTime);

		}

		if (aniTime > 0.59f)
		{
			if (m_tick[Breath]->tickStart())
			{
				if (PHYSICS_MGR->intersectSector(pTransform, m_pPlayer->pTransform, 50, 18 * ONE_RAD))
				{
					m_pPlayer->Damage(10.f);

					m_pBreathParticle->pTransform->SetWorldPosition(m_pBoneTrans[HEAD]->GetWorldPosition());
					m_pBreathParticle->pTransform->SetRotateWorld(pTransform->GetWorldRotateMatrix());

					LOG_MGR->AddLog("�극�� ����: %.2f", aniTime);

				}

			}
			//m_pPlayer->Damage();

			// �÷��̾� ������ �ִ� �κ�,
		}
		if (aniTime > 0.99f)
		{
			//LOG_MGR->AddLog(": %.2f", aniTime);
			stateInit();
			m_pBreathParticle->StopEmission();
		}
	}
}
void cDragon::earthUpate()
{
	if (strcmp(m_nowAni.c_str(), "ATK_01") == 0)
	{
		float aniTime = pSkinned->GetTime();


		if (aniTime > 0.2f)
		{

			m_pBreathParticle->pTransform->SetWorldPosition(m_pBoneTrans[HEAD]->GetWorldPosition());
			m_pBreathParticle->pTransform->SetRotateWorld(pTransform->GetWorldRotateMatrix());


			if (m_tick[Earthquake]->tickStart())
			{
				for (int i = 0; i < COLLCIRCLE; i++)
				{
					if (PHYSICS_MGR->IsPointSphere(&m_circle[i].worldCenter, m_circle[i].radius
						, &m_pPlayer->pTransform->GetWorldPosition()))
					{
						m_pPlayer->Damage(10.f);
						LOG_MGR->AddLog("�����Ǹ���");

					}
					if (PHYSICS_MGR->IsPointQuad(m_quad[i], &m_pPlayer->getMoveClass()->getRay()))
					{
						m_pPlayer->Damage(10.f);
						LOG_MGR->AddLog("�׸����Ǹ���");
					}
				}

			}
			//m_pPlayer->Damage();

			// �÷��̾� ������ �ִ� �κ�,
		}
		if (aniTime > 0.99f)
		{
			//LOG_MGR->AddLog(": %.2f", aniTime);
			stateInit();

		}
	}
}
void cDragon::HeadAttUpate()
{
	if (strcmp(m_nowAni.c_str(), "SK_Firing_01") == 0)
	{
		float aniTime = pSkinned->GetTime();

		if (m_tick[HeadAtt]->tickStart())
		{
			if (PHYSICS_MGR->IsOverlap(m_pPlayer->pTransform, &m_pPlayer->BoundBox,
				m_pBoneTrans[HEAD], &m_bound[HEAD]))
			{
				m_pPlayer->Damage(10.f);
				LOG_MGR->AddLog("�Ӹ��� ����");

			}

		}


		if (aniTime > 0.99f)
		{

			stateInit();

		}
	}
}

void cDragon::dieUpdate(float timeDelta)
{
	if (isDie == true)return; // �׾����� ���� .
	if (dieAniTime > 8.f)return;
	if (dieAniTime == 0)
	{
		LOG_MGR->AddLog("Ÿ��: %f", dieAniTime);
		if (SOUND_MGR->isPlaySound("dra_Die") == false)
		{
			SOUND_MGR->play("dra_Die", 0.8f);
		}
		this->pSkinned->Play("Spawn", 0.3);
	}

	if (dieAniTime > 7.f)
	{

		pSkinned->Stop();
		stateInit();
		isDie = true;
		m_state == DIE;
		SetActive(false);
	}


	dieAniTime += timeDelta;

}
void cDragon::stateInit()
{
	skillChance = 0;
	isMove = false;           // �����̴���?
	isBasicAttack = false;    // �⺻ ������?
	isBreath = false;         // �극����?
	isEarthquake = false;     // ������?
	isHeadAtt = false;         // �Ӹ� ġ��
	isNoneBasicAttack = false;// �극�� , ���� ,�Ӹ� ġ�� �� �̴�?
}

D3DXVECTOR3 cDragon::makeRndVec(D3DXVECTOR3* pos, float fRadius)
{
	float tX = pos->x;
	float tZ = pos->z;

	float x, z;
	x = RandomFloatRange(tX - fRadius, tX + fRadius);
	z = RandomFloatRange(tZ - fRadius, tZ + fRadius);

	D3DXVECTOR3 finalPos(x, pTerrain->GetHeight(x, z), z);
	return finalPos;
}

void cDragon::makeCircleQuad()
{
	// ��Ŭ ��ǥ ����
	for (int i = 0; i < COLLCIRCLE; i++)
	{
		m_circle[i].worldCenter = makeRndVec(&pTransform->GetWorldPosition(), m_spone.radius / 2);
	}
	// ���� ��ǥ ����. 
	for (int i = 0; i < COLLCIRCLE; i++)
	{
		m_quadPos[i] = makeRndVec(&pTransform->GetWorldPosition(), m_spone.radius / 2);
		MyUtil::createQuad(m_quad[i], 8, 8, pTransform,
			&m_quadPos[i]);
	}
}

void cDragon::initParticle()
{
	m_pBreathParticle = new cPartcleEmitter();
	m_pBreathParticle->SetActive(true);

	//
	// ȭ�� ����
	//

	VEC_COLOR colors;
	colors.push_back(D3DXCOLOR(0.3f, 0.5f, 0.5f, 0.0f));
	colors.push_back(D3DXCOLOR(0.3f, 0.5f, 8.0f, 0.2f));
	colors.push_back(D3DXCOLOR(0.3f, 0.5f, 8.0f, 0.2f));
	colors.push_back(D3DXCOLOR(0.3f, 0.8f, 8.0f, 0.2f));
	colors.push_back(D3DXCOLOR(0.3f, 0.8f, 8.0f, 0.2f));
	colors.push_back(D3DXCOLOR(0.3f, 0.8f, 8.0f, 0.2f));
	colors.push_back(D3DXCOLOR(0.3f, 0.8f, 8.0f, 0.2f));


	VEC_SCALE scales;
	scales.push_back(1.3f);
	scales.push_back(2.4f);
	scales.push_back(4.5f);
	scales.push_back(5.6f);
	scales.push_back(7.7f);
	scales.push_back(8.8f);

	LPDIRECT3DTEXTURE9 pTex = RESOURCE_TEXTURE->GetResource(
		"../Resources/Textures/FireExplosionBlurred.png");

	//��ƼŬ ������ ����
	m_pBreathParticle->Init(
		500,
		80.0f,
		0.3f,
		1.1f,
		D3DXVECTOR3(0, 0, 30),
		D3DXVECTOR3(0, 0, 40),
		D3DXVECTOR3(0, 0.2f, -0.5f),
		D3DXVECTOR3(0, 0.4f, -1.0f),
		colors,
		scales,
		2.3f,
		3.0f,
		pTex
		);


}