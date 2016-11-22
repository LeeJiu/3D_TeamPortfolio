#include "stdafx.h"
#include "cSkill_Front.h"


cSkill_Front::cSkill_Front()
{
}


cSkill_Front::~cSkill_Front()
{
}

void cSkill_Front::BaseObjectEnable(D3DXVECTOR3 casterWorldPos, float maxDistance, float maxWidth, int castTime, int attackingTime, int coolTime)
{
	m_IsSelect = false;   //범위 선택하는중
	m_IsCasting = false;  //캐스팅 시작하는 중
	m_IsAttacking = false;  //공격 시작하는 중
	m_IsCoolTime = false;   // 쿨타임이 도는 중 - 이떄 모든것을 false로 바꿔주자

	m_CasterWorldPos = casterWorldPos;
	m_MaxDistance = maxDistance;  //최대 사거리 대입
	m_MaxWidth = maxWidth;

	m_CastTimeCount = 0;
	m_CastTime = castTime;

	m_CoolTimeCount = 0;
	m_CoolTime = coolTime;

	m_AttackingCount = 0;
	m_AttackingTime = attackingTime;


	pTransform->SetWorldPosition(m_CasterWorldPos);
	m_BoundBox.SetBound(&pTransform->GetWorldPosition(), &D3DXVECTOR3(m_MaxWidth, 10, m_MaxDistance));


	// 범위 이펙트 - 빨간색
	m_CastEfc = new cQuadParticleEmitter();
	m_CastEfc->SetActive(true);

	VEC_COLOR colors3;
	colors3.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors3.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors3.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales3;
	scales3.push_back(1.5f);  //초반 크기
	scales3.push_back(1.5f);


	m_CastEfc->Init(
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
		colors3, scales3,
		1, 1,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/front_effect.tga"),
		true);


	m_CastEfc->pTransform->Scaling(D3DXVECTOR3( m_MaxWidth, 1, m_MaxDistance));

	m_CastEfc->StartEmission();


}


void cSkill_Front::BaseObjectUpdate(float timeDelta, D3DXVECTOR3 casterWorldPos, D3DXVECTOR3 mousePos)
{

	m_CasterWorldPos = casterWorldPos;
	m_LookDir = mousePos;


	if (m_IsCasting)  //캐스팅이 시작되면
	{
		LOG_MGR->AddLog("캐스팅시작");
		m_IsSelect = false;
		m_CastTimeCount++;

		if (m_CastTimeCount == m_CastTime) //캐스팅이 끝나면 
		{
			m_IsCasting = false;
			m_IsAttacking = true;
			m_IsCoolTime = true; //쿨타임돌기를 시작합시다
			m_AttackPos = m_LookDir;

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
			m_CastEfc->Update(timeDelta);
			pTransform->SetWorldPosition(D3DXVECTOR3(0,0,0));
			pTransform->SetWorldPosition(D3DXVECTOR3(m_CasterWorldPos.x, 0, m_CasterWorldPos.z));
			pTransform->LookPosition(D3DXVECTOR3(m_LookDir.x, 0, m_LookDir.z), 90 * ONE_RAD);
			//m_BoundBox.SetBound(&pTransform->GetWorldPosition(), &D3DXVECTOR3(m_MaxWidth, 10, m_MaxDistance));
			m_CastEfc->pTransform->SetWorldPosition(D3DXVECTOR3(m_CasterWorldPos.x, 0, m_CasterWorldPos.z));
			m_CastEfc->pTransform->LookPosition(D3DXVECTOR3(m_LookDir.x, 0, m_LookDir.z), 90 * ONE_RAD);
	
			//m_CastEfc->pTransform->LookPosition(m_LookDir, 180 * ONE_RAD);
			D3DXVECTOR3 selectMax = pTransform->GetWorldPosition() - m_CasterWorldPos;

	
			if (KEY_MGR->IsOnceDown(VK_LBUTTON))
			{
				LOG_MGR->AddLog("시전시작");
				m_IsCasting = true;
				m_IsSelect = false;

			}
		
		}
	}



}

void cSkill_Front::BaseObjectRender()
{
	D3DXVECTOR3 selectMax = pTransform->GetWorldPosition() - m_CasterWorldPos;


	if (m_IsSelect)
	{
		m_CastEfc->Render();
		m_BoundBox.RenderGizmo(pTransform);

	

	}
}

void cSkill_Front::SelectSkill()
{
	m_IsSelect = true;
	m_CastTimeCount = 0;
	m_CoolTimeCount = 0;
	m_AttackingCount = 0;
}//UI에 스킬을 마우스 오버 했을때 불러주자

void cSkill_Front::StartCasting()
{
	m_IsCasting = true;
	m_CastTimeCount = 0;
	m_CoolTimeCount = 0;
	m_AttackingCount = 0;
}//스킬을 사용한다 즉시시전 스킬도 이 함수를 불러주자