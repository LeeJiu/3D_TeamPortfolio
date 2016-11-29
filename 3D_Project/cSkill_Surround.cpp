#include "stdafx.h"
#include "cSkill_Surround.h"




cSkill_Surround::cSkill_Surround()
{
}


cSkill_Surround::~cSkill_Surround()
{

}

void cSkill_Surround::BaseObjectEnable(D3DXVECTOR3 casterWorldPos, float surroundLength, int castTime, int attackingTime, int coolTime)
{

	m_IsSelect = false;
	m_IsCasting = false;
	m_IsAttacking = false;
	m_IsCoolTime = false;


		m_CasterWorldPos = casterWorldPos;

		pTransform->SetWorldPosition(m_CasterWorldPos);  // 트렌스폼 좌표 

		m_SurroundLength = surroundLength;


		m_CastTimeCount = 0;
		m_CastTime = castTime;

		m_CoolTimeCount = 0;
		m_CoolTime = coolTime;

		m_AttackingCount = 0;
		m_AttackingTime = attackingTime;

		m_CircleEfc = new cQuadParticleEmitter();
		m_CircleEfc->SetActive(true);

		m_BoundSphere.SetBound(&D3DXVECTOR3(m_CasterWorldPos.x, 0, m_CasterWorldPos.z), &D3DXVECTOR3(m_SurroundLength, 0, m_SurroundLength));


		VEC_COLOR colors2;
		colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

		VEC_SCALE scales2;
		scales2.push_back(3.0f);  //초반 크기
		scales2.push_back(3.0f);

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
			m_SurroundLength, m_SurroundLength,
			RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/surround_effect.tga"),
			true);

		m_CircleEfc->StartEmission();



		m_CastEfc = new cQuadParticleEmitter();
		m_CastEfc->SetActive(true);

		VEC_COLOR colors3;
		colors3.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		colors3.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		colors3.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

		VEC_SCALE scales3;
		scales3.push_back(3.0f);  //초반 크기
		scales3.push_back(3.0f);


		m_CastEfc->Init(
			30,
			10.0f,     //이펙트 몇장
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
			colors3, scales3,
			m_SurroundLength / 10, m_SurroundLength,
			RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/surround_cast_effect.tga"),
			true);

		m_CastEfc->StartEmission();

	

	
}

void cSkill_Surround::BaseObjectUpdate(float timeDelta, D3DXVECTOR3 CasterWorldPos)
{

	m_CasterWorldPos = CasterWorldPos;
	pTransform->SetWorldPosition(m_CasterWorldPos);

	if (m_IsCoolTime) //쿨타임 중이면 
	{
		//LOG_MGR->AddLog("쿨타임 중입니다");

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
			m_CircleEfc->Update(timeDelta);
			m_CircleEfc->pTransform->SetWorldPosition(m_CasterWorldPos);
			m_CircleEfc->pTransform->RotateSelf(D3DXVECTOR3(0, 0.3f * timeDelta, 0));

		}
	}




	if (m_IsCasting)
	{
		m_IsSelect = false;
		m_CastEfc->Update(timeDelta);
		m_CastEfc->pTransform->SetWorldPosition(m_CasterWorldPos);
		m_CastTimeCount++;
		
		if (m_CastTimeCount == m_CastTime) //캐스팅이 끝나면 
		{
			m_IsCasting = false;
			m_IsAttacking = true;
			m_IsCoolTime = true; //쿨타임돌기를 시작합시다

		}

	}

	if (m_IsAttacking)
	{
		m_IsCasting = false;
		m_AttackingCount++;

		if (m_AttackingCount == m_AttackingTime) //시전시간이 끝나면
		{
		
			m_IsAttacking = false;
			LOG_MGR->AddLog("스킬끝");
		}

	}


	

}

void cSkill_Surround::BaseObjectRender()
{

	if (m_IsSelect)
	{
		m_CircleEfc->Render();
		m_BoundSphere.RenderGizmo(pTransform);

	}


	if (m_IsCasting)
	{
		m_CastEfc->Render();
	}


	


	


}


void cSkill_Surround::SelectSkill()
{
	
		m_IsSelect = true;
		m_CastTimeCount = 0;
		m_CoolTimeCount = 0;
		m_AttackingCount = 0;



}

void cSkill_Surround::StartCasting()
{
	
		m_IsCasting = true;
		m_CastTimeCount = 0;
		m_CoolTimeCount = 0;
		m_AttackingCount = 0;

}
