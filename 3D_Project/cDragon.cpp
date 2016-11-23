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
	m_pBoneTrans[0] = pTransform;     // pTrans 값을 0 번에 입력
	m_pCollTrans[0] = pTransform;

	// 뼈에 붙일 트렌스 초기화
	for (int i = 1; i < COLLISION; i++)
	{
		m_pBoneTrans[i] = new cTransform; //동적 할당 되있는거. 
	}

	for (int i = 1; i < 5; i++)
	{
		m_pCollTrans[i] = new cTransform; //동적 할당 되있는거. 
	}
	//=================== 초기화 ================
	//pTransform , 몬스터 움직일때 쓰는 trans 

	pSkinned->AddBoneTransform("Bip01-HeadNub", m_pBoneTrans[1]);
	pSkinned->AddBoneTransform("Bip01-L-Hand_Bone", m_pBoneTrans[2]);
	pSkinned->AddBoneTransform("Bip01-R-Hand_Bone", m_pBoneTrans[3]);

	//0몸통
	m_bound[0].Init(D3DXVECTOR3(-4, 0, -4), D3DXVECTOR3(4, 8, 4.5));
	//머리
	m_bound[1].Init(D3DXVECTOR3(-2, -1, -2), D3DXVECTOR3(0, 1, 0.5));
	//왼팔
	m_bound[2].Init(D3DXVECTOR3(0, -1, -1), D3DXVECTOR3(2, 1, 1));
	//오른팔
	m_bound[3].Init(D3DXVECTOR3(0, -1, -1), D3DXVECTOR3(2, 1, 1));

	//처음 시작시 플레이 애니메이션
	this->pSkinned->Play("Spawn", 0.3f);
	this->pSkinned->Stop();
	collPosUpdate();
	// 스폰 지역 월드 센터 값 
	m_spone.worldCenter = pTransform->GetWorldPosition();
	m_spone.radius = 30.f;
	// 평타 사정거리
	m_basicAttack.radius = m_bound[0].radius;

	//애니메이션 상태값
	isBattle = false;         //전투중?
	isMove = false;           // 움직이는중?
	isBasicAttack = false;    // 기본 공격중?
	isBreath = false;         // 브레스중?
	isEarthquake = false;     // 장판중?
	isHeadAtt = false;         // 머리 치기
	isNoneBasicAttack = false;// 브레스 , 장판 ,머리 치기 중 이니?
	//스킬 사용할 숫자. 
	skillChance = 0;          // max 3 개 1,2,3 사용
}

void cDragon::BaseObjectUpdate(float timeDelta)
{
	m_nowAni = pSkinned->GetNowPlayingAni();

	// 전투 범위에 들어오면 
	if (battleRange() == true && isBattle == true)
	{
		//처음 생겨났을때 애니메이션 돌린당~
		//플레이어 방향으로 따라옴
		if (isBasicAttack == false && isNoneBasicAttack == false)
		{
			MoveToPlayer();
		}
		// 충돌 체크에 필요한 Trans값들을 갱신 해줌. 
		collPosUpdate();

		// 평타 범위 안에 들어오면 평타 공격을 한다. 
		if (basicRange() == true)
		{
			//기본 공격을 하기 위해서는 멈춰야 한다. 
			isMove = false;
			isBasicAttack = true;     // 기본 공격 

			//평타 중에 다른 스키 쓸 수 있음.
			//if (KEY_MGR->IsOnceDown('L'))
			//{
			//	stateInit();
			//
			//	isHeadAtt = true;
			//	isNoneBasicAttack = true;
			//}

		}
		else // 기본 공격 범위 벗어 났을때. 
		{
			//스킬 쓰고나서 초기 해야 할 값
			//skillChance =0, isNoneBasicAttack = false, 스킬에 사용한 값
			if (skillChance == 0)
			{
				skillChance = MyUtil::RandomIntRange(1, 4);
				isMove = false;
				isBasicAttack = false;
				LOG_MGR->AddLog("랜덤: %d", skillChance);
				LookPos(m_pPlayer->pTransform->GetWorldPosition());
			}
			switch (skillChance)
			{
			case 1:
				isBreath = true;         // 브레스중?
				isNoneBasicAttack = true;// 브레스 , 장판 ,머리 치기 중 이니?

				break;
			case 2:
				isEarthquake = true;     // 장판중?
				isNoneBasicAttack = true;// 브레스 , 장판 ,머리 치기 중 이니?

				break;
			case 3:
				isHeadAtt = true;         // 머리 치기
				isNoneBasicAttack = true;// 브레스 , 장판 ,머리 치기 중 이니?
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
	// 플레이어가 도망칠때 용이 움직일 코드
	else
	{

	}

	basicAttackUpdate();

	breathUpdate();
	earthUpate();
	HeadAttUpate();

	aniManager();

	//=================== 업데이트 ==============
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
	//=================== 바운드 박스 추가 ======
}

void cDragon::Damage(float fDamage)
{
	//=================== 데미지 받을 함수 ======
}
void cDragon::BaseObjectRender()
{
	//=================== 렌더 함수 =============
	//본 이름 
	// 머리 Bip01-HeadNub
	// 왼팔 Bip01-L-Hand_Bone
	// 오팔 Bip01-R-Hand_Bone
	// 오발 Bip01-R-Foot_Bone
	// 왼발 Bip01-L-Foot_Bone
	// 오날개 BN_Wing_R003,007
	// 왼날개 BN_Wing_L003,007
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
	//좌표 갱신.
	//0번은 몸통 바운드 박스 기준
	m_bound[0].GetWorldBox(m_pBoneTrans[0], m_collPos);
	m_pCollTrans[1]->SetWorldPosition(m_collPos[0]);
	m_pCollTrans[2]->SetWorldPosition(m_collPos[3]);
	m_pCollTrans[3]->SetWorldPosition(m_collPos[4]);
	m_pCollTrans[4]->SetWorldPosition(m_collPos[7]);
	//평타에 쓰일 좌표 갱신
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
	//상태 값 어떠한 행동을 하고 있다면 리턴 한다. 
	if (isBasicAttack == true)return;
	//레이 세팅

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

	//거리를 구한다. / 플레이어와 몬스터의 거리
	D3DXVECTOR3 dirToTarget = m_pPlayer->pTransform->GetWorldPosition() - currentPos;
	float dist = D3DXVec3Length(&dirToTarget);
	dirToTarget.y = 0;


	//방향을 구한다.
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


	//이동량
	float deltaMove = 5.0f * TIME_MGR->GetFrameDeltaSec();
	float t = Clamp01(deltaMove / dist);

	//현재 위치에서 웨이 포인트로 보간된 위치값을 레이에 넣는다.
	ray.origin = VecLerp(currentPos, m_pPlayer->pTransform->GetWorldPosition(), t);
	ray.origin.y += 3;	//머리 위에 붙인다.


	D3DXVECTOR3 pos;
	//레이랑 터레인 체크하자
	if (pTerrain->IsIntersectRay(&pos, &ray))
	{
		pTransform->SetWorldPosition(pos);
		currentPos = pos;
		//상태값
		isMove = true;
	}

	// 레이랑 케릭터 거리가 멀어지면 레이가 더이상 넘어가지 못하게 만든다.
	float rayCheckDis = D3DXVec3Length(&(ray.origin - currentPos));
	if (rayCheckDis > t + 0.01f) // 상수 값은 속력 보다 조금 높은 값.
	{
		ray.origin = currentPos;
		ray.origin.y += 3;
	}
}
void cDragon::LookPos(D3DXVECTOR3 target)
{

	//거리를 구한다. / 몬에서-----> 타겟 
	D3DXVECTOR3 dirToTarget = target - pTransform->GetWorldPosition();
	float dist = D3DXVec3Length(&dirToTarget);
	dirToTarget.y = 0;

	//방향을 구한다.
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

			// 플레이어 데미지 주는 부분,
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
	// 움직이는 애니메이션
	if (isMove == true && isBasicAttack == false
		&& isNoneBasicAttack == false)
	{
		if (strcmp(m_nowAni.c_str(), "Walk_F") == 0)return;
		this->pSkinned->Play("Walk_F", 0.3);
	}// 기본 공격
	else if (isBasicAttack == true
		&& isNoneBasicAttack == false)
	{
		if (strcmp(m_nowAni.c_str(), "ATK_02") == 0)return;
		this->pSkinned->Play("ATK_02", 0.3);
	}// 브레스
	else if (isBreath == true && isNoneBasicAttack == true)
	{
		if (strcmp(m_nowAni.c_str(), "SK_Firing_02") == 0)return;
		this->pSkinned->Play("SK_Firing_02", 0.3);
	}// 장판
	else if (isEarthquake == true && isNoneBasicAttack == true)
	{
		if (strcmp(m_nowAni.c_str(), "ATK_01") == 0)return;
		this->pSkinned->Play("ATK_01", 0.3);
	}// 머리 치기 
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

			// 플레이어 데미지 주는 부분,
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

			// 플레이어 데미지 주는 부분,
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

			// 플레이어 데미지 주는 부분,
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
	isMove = false;           // 움직이는중?
	isBasicAttack = false;    // 기본 공격중?
	isBreath = false;         // 브레스중?
	isEarthquake = false;     // 장판중?
	isHeadAtt = false;         // 머리 치기
	isNoneBasicAttack = false;// 브레스 , 장판 ,머리 치기 중 이니?
}