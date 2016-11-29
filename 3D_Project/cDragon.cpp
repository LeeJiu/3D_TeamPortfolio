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
	m_pBoneTrans[BODY] = pTransform;     // pTrans 값을 0 번에 입력
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

	//=================== 초기화 ================
	//pTransform , 몬스터 움직일때 쓰는 trans 


	pSkinned->AddBoneTransform("Bip01-HeadNub", m_pBoneTrans[HEAD]);
	pSkinned->AddBoneTransform("Bip01-L-Hand_Bone", m_pBoneTrans[LHANAD]);
	pSkinned->AddBoneTransform("Bip01-R-Hand_Bone", m_pBoneTrans[RHAND]);

	//0몸통
	BoundBox.Init(D3DXVECTOR3(-4, 0, -4), D3DXVECTOR3(4, 8, 4.5));
	m_bound[BODY].Init(D3DXVECTOR3(-4, 0, -4), D3DXVECTOR3(4, 8, 4.5));
	//머리
	m_bound[HEAD].Init(D3DXVECTOR3(-2, -1, -2), D3DXVECTOR3(0, 1, 0.5));
	//왼팔
	m_bound[LHANAD].Init(D3DXVECTOR3(0, -1, -1), D3DXVECTOR3(2, 1, 1));
	//오른팔
	m_bound[RHAND].Init(D3DXVECTOR3(0, -1, -1), D3DXVECTOR3(2, 1, 1));

	//처음 시작시 플레이 애니메이션
	this->pSkinned->Play("Spawn", 0.3f);
	this->pSkinned->Stop();
	collPosUpdate();
	// 스폰 지역 월드 센터 값 
	m_spone.worldCenter = pTransform->GetWorldPosition();
	m_spone.radius = 100.f;
	// 평타 사정거리
	m_basicAttack.radius = m_bound[BODY].radius;

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
	//죽었니?
	isDie = false;



	// 장판 범위 
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
	//테스트용
	//if (KEY_MGR->IsOnceDown('B'))
	//{
	//	m_fHP = -500.f;
	//	LOG_MGR->AddLog("눌렀씨요: %f", dieAniTime);
	//}

	if (m_fHP < 0.f)
	{
		dieUpdate(timeDelta);
	}
	else if (m_fHP > 0.f)
	{
		m_nowAni = pSkinned->GetNowPlayingAni();
		int chance = MyUtil::RandomIntRange(0, 10);

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
				if (chance == 5 && isBasicAttack != true)  // 1/10 확률로 머리치기 /
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
					isEarthquake = true;     // 장판중?
					isNoneBasicAttack = true;// 브레스 , 장판 ,머리 치기 중 이니?
					LOG_MGR->AddLog("평타중 발동: %d", skillChance);
					makeCircleQuad();
					if (SOUND_MGR->isPlaySound("dra_Meteo") == false)
					{
						SOUND_MGR->play("dra_Meteo", 0.8f);
					}
				}
				else
				{
					//기본 공격을 하기 위해서는 멈춰야 한다. 
					isMove = false;
					isBasicAttack = true;     // 기본 공격 
					if (SOUND_MGR->isPlaySound("dra_BasicATK")==false)
					{
						SOUND_MGR->play("dra_BasicATK", 0.8f);
					}
				}

			}
			else // 기본 공격 범위 벗어 났을때. 
			{
				//스킬 쓰고나서 초기 해야 할 값
				//skillChance =0, isNoneBasicAttack = false, 스킬에 사용한 값
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
							isBreath = true;         // 브레스중?
							isNoneBasicAttack = true;// 브레스 , 장판 ,머리 치기 중 이니?
							if (SOUND_MGR->isPlaySound("dra_Breath") == false)
							{
								SOUND_MGR->play("dra_Breath", 0.8f);
							}
							break;
						case 2:
							if (isEarthquake == true)break;
							isEarthquake = true;     // 장판중?
							isNoneBasicAttack = true;// 브레스 , 장판 ,머리 치기 중 이니?
							LOG_MGR->AddLog("랜덤: %d", skillChance);
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
		// 플레이어가 도망칠때 용이 움직일 코드
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

			// 전투중일때 업데이트 아니면 돌지 않게 한당. 
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

			m_pTrailLEye->Update(timeDelta);					//트레일렌더 업데이트
			m_pTrailREye->Update(timeDelta);					//트레일렌더 업데이트
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


		//=================== 업데이트 ==============
	}




}

void cDragon::BaseObjectBoundBox()
{
	//=================== 바운드 박스 추가 ======
}

void cDragon::Damage(float fDamage)
{
	//=================== 데미지 받을 함수 ======
	m_fHP -= fDamage;
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
	m_pTrailLEye->Render();							//트레일렌더 랜더링
	m_pTrailREye->Render();							//트레일렌더 랜더링

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

	// 스킬 이팩트 부분
	for (int i = 0; i < COLLCIRCLE; i++)
	{
		m_Skill_Meteo[i]->BaseObjectRender();
		m_Skill_Meteo[i]->Effect_Render();
		m_Skill_Thunder[i]->BaseObjectRender();
		m_Skill_Thunder[i]->Effect_Render();
	}
	// 파티클 부분
	m_pBreathParticle->Render();

}

void cDragon::TrailSetting()
{
	pSkinned->AddBoneTransform("BN_Eye_L", &m_LEyeTrans);
	pSkinned->AddBoneTransform("BN_Eye_R", &m_REyeTrans);

	m_pTrailLEye = new cTrailRender();
	m_pTrailLEye->Init(
		1.0f,					//꼬리 라이브 타임 ( 이게 크면 환영큐 사이즈가 커지고 꼬리가 오랬동안 남아있다 )
		0.1f,					//폭
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/TrailTest.png"),	//메인 Texture
		D3DXCOLOR(0.5, 1, 0, 1),												//메인 Texture 로 그릴때 컬러
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
	//좌표 갱신.
	//0번은 몸통 바운드 박스 기준
	BoundBox.GetWorldBox(m_pBoneTrans[BODY], m_collPos);
	//m_bound[BODY].GetWorldBox(m_pBoneTrans[BODY], m_collPos);
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
void cDragon::MoveToSpone(D3DXVECTOR3 target)
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


	//이동량
	float deltaMove = 5.0f * TIME_MGR->GetFrameDeltaSec();
	float t = Clamp01(deltaMove / dist);

	//현재 위치에서 웨이 포인트로 보간된 위치값을 레이에 넣는다.
	ray.origin = VecLerp(currentPos, target, t);
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
	if (isNoneBasicAttack == true)return;
	if (strcmp(m_nowAni.c_str(), "ATK_02") == 0)
	{

		float aniTime = pSkinned->GetTime();

		if (aniTime > 0.9f)
		{
			if (m_tick[BasicAtt]->tickStart())
			{
				m_pPlayer->Damage(10.f);
				// 플레이어 데미지 주는 부분,
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
	// 움직이는 애니메이션


	if (isMove == true && isBasicAttack == false
		&& isNoneBasicAttack == false)
	{
		if (strcmp(m_nowAni.c_str(), "Run_F") == 0)return;
		this->pSkinned->Play("Run_F", 0.3);
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
			LOG_MGR->AddLog("브레스 시작: %.2f", aniTime);

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

					LOG_MGR->AddLog("브레스 맞음: %.2f", aniTime);

				}

			}
			//m_pPlayer->Damage();

			// 플레이어 데미지 주는 부분,
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
						LOG_MGR->AddLog("원장판맞음");

					}
					if (PHYSICS_MGR->IsPointQuad(m_quad[i], &m_pPlayer->getMoveClass()->getRay()))
					{
						m_pPlayer->Damage(10.f);
						LOG_MGR->AddLog("네모장판맞음");
					}
				}

			}
			//m_pPlayer->Damage();

			// 플레이어 데미지 주는 부분,
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
				LOG_MGR->AddLog("머리에 맞음");

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
	if (isDie == true)return; // 죽었으면 리턴 .
	if (dieAniTime > 8.f)return;
	if (dieAniTime == 0)
	{
		LOG_MGR->AddLog("타임: %f", dieAniTime);
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
	isMove = false;           // 움직이는중?
	isBasicAttack = false;    // 기본 공격중?
	isBreath = false;         // 브레스중?
	isEarthquake = false;     // 장판중?
	isHeadAtt = false;         // 머리 치기
	isNoneBasicAttack = false;// 브레스 , 장판 ,머리 치기 중 이니?
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
	// 서클 좌표 생성
	for (int i = 0; i < COLLCIRCLE; i++)
	{
		m_circle[i].worldCenter = makeRndVec(&pTransform->GetWorldPosition(), m_spone.radius / 2);
	}
	// 쿼드 좌표 생성. 
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
	// 화염 방사기
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

	//파티클 랜더러 셋팅
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