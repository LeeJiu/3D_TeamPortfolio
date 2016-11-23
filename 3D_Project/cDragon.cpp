#include "stdafx.h"
#include "cDragon.h"
#include "cPlayer.h"


cDragon::cDragon()
{
	m_collCount = COLLISION;
	m_fHP = 30000.f;

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
}

void cDragon::BaseObjectEnable()
{
	m_pBoneTrans[0] = pTransform;     // pTrans ���� 0 ���� �Է�
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
	//=================== �ʱ�ȭ ================
	//pTransform , ���� �����϶� ���� trans 

	pSkinned->AddBoneTransform("Bip01-HeadNub", m_pBoneTrans[1]);
	pSkinned->AddBoneTransform("Bip01-L-Hand_Bone", m_pBoneTrans[2]);
	pSkinned->AddBoneTransform("Bip01-R-Hand_Bone", m_pBoneTrans[3]);

	//0����
	m_bound[0].Init(D3DXVECTOR3(-4, 0, -4), D3DXVECTOR3(4, 8, 4.5));
	//�Ӹ�
	m_bound[1].Init(D3DXVECTOR3(-2, -1, -2), D3DXVECTOR3(0, 1, 0.5));
	//����
	m_bound[2].Init(D3DXVECTOR3(0, -1, -1), D3DXVECTOR3(2, 1, 1));
	//������
	m_bound[3].Init(D3DXVECTOR3(0, -1, -1), D3DXVECTOR3(2, 1, 1));

	//ó�� ���۽� �÷��� �ִϸ��̼�
	this->pSkinned->Play("Spawn", 0.3f);
	this->pSkinned->Stop();
	collPosUpdate();
	// ���� ���� ���� ���� �� 
	m_spone.worldCenter = pTransform->GetWorldPosition();
	m_spone.radius = 30.f;
	// ��Ÿ �����Ÿ�
	m_basicAttack.radius = m_bound[0].radius;

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
}

void cDragon::BaseObjectUpdate(float timeDelta)
{
	m_nowAni = pSkinned->GetNowPlayingAni();

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
			//�⺻ ������ �ϱ� ���ؼ��� ����� �Ѵ�. 
			isMove = false;
			isBasicAttack = true;     // �⺻ ���� 

			//��Ÿ �߿� �ٸ� ��Ű �� �� ����.
			//if (KEY_MGR->IsOnceDown('L'))
			//{
			//	stateInit();
			//
			//	isHeadAtt = true;
			//	isNoneBasicAttack = true;
			//}

		}
		else // �⺻ ���� ���� ���� ������. 
		{
			//��ų ������ �ʱ� �ؾ� �� ��
			//skillChance =0, isNoneBasicAttack = false, ��ų�� ����� ��
			if (skillChance == 0)
			{
				skillChance = MyUtil::RandomIntRange(1, 4);
				isMove = false;
				isBasicAttack = false;
				LOG_MGR->AddLog("����: %d", skillChance);
				LookPos(m_pPlayer->pTransform->GetWorldPosition());
			}
			switch (skillChance)
			{
			case 1:
				isBreath = true;         // �극����?
				isNoneBasicAttack = true;// �극�� , ���� ,�Ӹ� ġ�� �� �̴�?

				break;
			case 2:
				isEarthquake = true;     // ������?
				isNoneBasicAttack = true;// �극�� , ���� ,�Ӹ� ġ�� �� �̴�?

				break;
			case 3:
				isHeadAtt = true;         // �Ӹ� ġ��
				isNoneBasicAttack = true;// �극�� , ���� ,�Ӹ� ġ�� �� �̴�?
				break;

			default:
				break;
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

	}

	basicAttackUpdate();

	breathUpdate();
	earthUpate();
	HeadAttUpate();

	aniManager();

	//=================== ������Ʈ ==============
	if (KEY_MGR->IsStayDown(VK_LCONTROL))
	{
		if (KEY_MGR->IsOnceDown('1'))
			this->pSkinned->Play("None_1", 0.3f);

		if (KEY_MGR->IsOnceDown('2'))
			this->pSkinned->Play("SK_Fring_03", 0.3f);

		if (KEY_MGR->IsOnceDown('3'))
			this->pSkinned->Play("Spawn", 0.3f);

		if (KEY_MGR->IsOnceDown(VK_SPACE))
			this->pSkinned->PlayOneShot("Walk_F", 0.3, 0.3);

		if (KEY_MGR->IsOnceDown('4'))
			this->pSkinned->Play("SK_Firing_02", 0.3f);
		if (KEY_MGR->IsOnceDown('5'))
			this->pSkinned->Play("SK_Firing_01", 0.3f);
		if (KEY_MGR->IsOnceDown('6'))
			this->pSkinned->Play("Run_F", 0.3f);
		if (KEY_MGR->IsOnceDown('7'))
			this->pSkinned->Play("Passout", 0.3f);
		if (KEY_MGR->IsOnceDown('8'))
			this->pSkinned->Play("IDLE_P_01", 0.3f);
		if (KEY_MGR->IsOnceDown('9'))
			this->pSkinned->Play("IDLE_C", 0.3f);
		if (KEY_MGR->IsOnceDown('0'))
			this->pSkinned->Play("DMG_F", 0.3f);
		if (KEY_MGR->IsOnceDown('Z'))
			this->pSkinned->Play("DMG_B", 0.3f);
		if (KEY_MGR->IsOnceDown('X'))
			this->pSkinned->Play("ATK_02", 0.3f);
		if (KEY_MGR->IsOnceDown('C'))
			this->pSkinned->Play("ATK_01", 0.3f);

		if (KEY_MGR->IsOnceDown('V'))
			this->pSkinned->Stop();
	}
}

void cDragon::BaseObjectBoundBox()
{
	//=================== �ٿ�� �ڽ� �߰� ======
}

void cDragon::Damage(float fDamage)
{
	//=================== ������ ���� �Լ� ======
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
	pSkinned->Render(m_pBoneTrans[0]);
	for (int i = 0; i < COLLISION; i++)
	{
		//m_pBoneTrans[i]->RenderGimozo(true);

	}
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

}

void cDragon::collPosUpdate()
{
	//��ǥ ����.
	//0���� ���� �ٿ�� �ڽ� ����
	m_bound[0].GetWorldBox(m_pBoneTrans[0], m_collPos);
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
	if (strcmp(m_nowAni.c_str(), "ATK_02") == 0);
	{

		float aniTime = pSkinned->GetTime();

		if (aniTime > 0.8f)
		{
			//m_pPlayer->Damage();

			// �÷��̾� ������ �ִ� �κ�,
		}
		if (aniTime > 0.98f)
		{
			LOG_MGR->AddLog(": %.2f", aniTime);
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
		if (strcmp(m_nowAni.c_str(), "Walk_F") == 0)return;
		this->pSkinned->Play("Walk_F", 0.3);
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
		if (strcmp(m_nowAni.c_str(), "Spawn") == 0);
		{
			float aniTime = pSkinned->GetTime();
			if (aniTime > 0.95f)
			{
				isBattle = true;
			}
		}
		if (pSkinned->GetIsPlay() == false)
		{
			this->pSkinned->Play("Spawn", 0.3f);
		}
		if (strcmp(m_nowAni.c_str(), "Spawn") == 0)return;
		this->pSkinned->Play("Spawn", 0.3f);

	}
}


void cDragon::breathUpdate()
{
	if (strcmp(m_nowAni.c_str(), "SK_Firing_02") == 0);
	{
		float aniTime = pSkinned->GetTime();

		if (aniTime > 0.8f)
		{
			//m_pPlayer->Damage();

			// �÷��̾� ������ �ִ� �κ�,
		}
		if (aniTime > 0.98f)
		{
			//LOG_MGR->AddLog(": %.2f", aniTime);
			stateInit();

		}
	}
}
void cDragon::earthUpate()
{
	if (strcmp(m_nowAni.c_str(), "ATK_01") == 0);
	{
		float aniTime = pSkinned->GetTime();

		if (aniTime > 0.8f)
		{
			//m_pPlayer->Damage();

			// �÷��̾� ������ �ִ� �κ�,
		}
		if (aniTime > 0.98f)
		{
			//LOG_MGR->AddLog(": %.2f", aniTime);
			stateInit();

		}
	}
}
void cDragon::HeadAttUpate()
{
	if (strcmp(m_nowAni.c_str(), "SK_Firing_01") == 0);
	{
		float aniTime = pSkinned->GetTime();

		if (aniTime > 0.8f)
		{
			//m_pPlayer->Damage();

			// �÷��̾� ������ �ִ� �κ�,
		}
		if (aniTime > 0.98f)
		{
			//LOG_MGR->AddLog(": %.2f", aniTime);
			stateInit();

		}
	}
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