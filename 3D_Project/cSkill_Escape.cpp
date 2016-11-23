#include "stdafx.h"
#include "cSkill_Escape.h"


cSkill_Escape::cSkill_Escape()
{
}


cSkill_Escape::~cSkill_Escape()
{
}

void cSkill_Escape::BaseObjectEnable(D3DXVECTOR3  casterWorldPos, float moveLength, int castTime, int buffCount, int coolTime)
{
	m_IsSelect = false;
	m_IsCasting = false;
	m_IsInBuff = false;
	m_IsCoolTime = false;

	m_MoveLength = moveLength;
	m_CasterWorldPos = casterWorldPos;

	//pTransform->LookDirection(D3DXVECTOR3(0, 0, 1), D3DXVECTOR3(0, 1, 0));
	pTransform->SetWorldPosition(m_CasterWorldPos);  // 트렌스폼 좌표 
	//pTransform->LookDirection(D3DXVECTOR3(0, 0, -1), 90 * ONE_RAD);

	m_CastTimeCount = 0;
	m_CastTime = castTime;

	m_CoolTimeCount = 0;
	m_CoolTime = coolTime;

	m_BuffCount = 0;
	m_BuffTime = buffCount;


	// 범위 이펙트 
	m_CircleEfc = new cQuadParticleEmitter();
	m_CircleEfc->SetActive(true);

	VEC_COLOR colors2;
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales2;
	scales2.push_back(1.0f);  //초반 크기
	scales2.push_back(1.0f);

	m_CircleEfc->Init(
		30,
		2.0f,     //이펙트 몇장
		1.0f,       //라이브타임 (발생 횟수에 대한 시간(적을수록 겹겹이)
		1.0f,
		D3DXVECTOR3(0, 1, 0),     //시작위치에서 끝점까지의 거리
		D3DXVECTOR3(0, 1, 0),
		D3DXVECTOR3(0, 0, 0),     //한쪽으로 발사하는 양 시작
		D3DXVECTOR3(0, 0, 0),     //한쪽으로 발사하는 양 끝
		D3DXVECTOR3(-90 * ONE_RAD, 0, 0),	//초기시작시 회전 min
		D3DXVECTOR3(-90 * ONE_RAD, 0, 0),     //초기시작시 회전Max
		D3DXVECTOR3(0, 0, 0),				//초당 회전할 회전 량 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		D3DXVECTOR3(0, 0, 0),				//초당 회전 가속 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		colors2, scales2,
		3.0f, 3.0f,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/surround_effect.tga"),
		true);

	m_CircleEfc->StartEmission();
}


void cSkill_Escape::BaseObjectUpdate(float timeDelta, D3DXVECTOR3 CasterWorldPos, D3DXVECTOR3 lookDir)
{
	m_CasterWorldPos = CasterWorldPos;
	m_LookDir = lookDir;

	if (m_IsCoolTime) //쿨타임 중이면 
	{
		LOG_MGR->AddLog("쿨타임 중입니다");

		m_CoolTimeCount++; //쿨타임을 계산해주자

		if (m_CoolTimeCount == m_CoolTime)
		{
			m_IsCoolTime = false;
		}

	}
	else //쿨타임 중이 아니면
	{
		if (m_IsSelect)
		{


		}
	}




	if (m_IsCasting)
	{
		m_IsSelect = false;
		m_CastTimeCount++;

		if (m_CastTimeCount == m_CastTime)
		{
			pTransform->SetWorldPosition(CasterWorldPos);
			pTransform->MovePositionSelf(D3DXVECTOR3(0, 0, m_MoveLength));
		}

		

		if (m_CastTimeCount == m_CastTime) //캐스팅이 끝나면 
		{
			m_IsCasting = false;
			m_IsInBuff = true;
			m_IsCoolTime = true; //쿨타임돌기를 시작합시다

		}

	}

	if (m_IsInBuff)
	{
		m_IsCasting = false;
		m_BuffCount++;
		pTransform->LookDirection(m_LookDir, D3DXVECTOR3(0,1,0));
		pTransform->SetWorldPosition(pTransform->GetWorldPosition());
		m_CircleEfc->Update(timeDelta);
		m_CircleEfc->pTransform->SetWorldPosition(pTransform->GetWorldPosition());

		if (m_BuffCount == m_BuffTime) //시전시간이 끝나면
		{

			m_IsInBuff = false;
			LOG_MGR->AddLog("버프 끝");
		}

	}

}


void cSkill_Escape::BaseObjectRender()
{
	if (m_IsCasting || m_IsInBuff)
	{
		m_CircleEfc->Render();
	}
}

void cSkill_Escape::SelectSkill()
{
	m_IsSelect = true;
	m_CastTimeCount = 0;
	m_CoolTimeCount = 0;
	m_BuffCount = 0;

}//UI에 스킬을 마우스 오버 했을때 불러주자

void cSkill_Escape::StartCasting()
{
	m_IsCasting = true;
	m_CastTimeCount = 0;
	m_CoolTimeCount = 0;
	m_BuffCount = 0;
}//스킬을 사용한다 즉시시전 스킬도 이 함수를 불러주자

