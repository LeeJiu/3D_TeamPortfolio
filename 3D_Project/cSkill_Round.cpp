#include "stdafx.h"
#include "cSkill_Round.h"
#include "cQuadParticleEmitter.h"

cSkill_Round::cSkill_Round()
{
}


cSkill_Round::~cSkill_Round()
{
}


void cSkill_Round::BaseObjectEnable(float surroundLength, int castTime, int maxDistance)
{
	m_IsSelect = false;   //범위 선택하는중
	m_IsCasting = false;  //캐스팅 시작하는 중
	m_IsAttacking = false;  //공격 시작하는 중
	m_IsCoolTime = false;   // 쿨타임이 도는 중 - 이떄 모든것을 false로 바꿔주자

	m_MaxDistance = maxDistance;  //최대 사거리 대입



	// 범위 이펙트 
	m_CircleEfc = new cQuadParticleEmitter();  
	m_CircleEfc->SetActive(true);

	pTransform->SetWorldPosition(D3DXVECTOR3(0,0,0));  // 트렌스폼 좌표 

	m_SurroundLength = surroundLength;

	m_BoundSphere.SetBound(&pTransform->GetWorldPosition(), &D3DXVECTOR3(m_SurroundLength, 0, m_SurroundLength));

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


	// 범위 이펙트  - 빨간색
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
		m_SurroundLength, m_SurroundLength,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/surround_cast_effect.tga"),
		true);

	m_CastEfc->StartEmission();

	VEC_COLOR colors4;
	colors4.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors4.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors4.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales4;
	scales4.push_back(3.0f);  //초반 크기
	scales4.push_back(3.0f);


	//사거리 표시 범위

	m_SurroundEfc = new cQuadParticleEmitter();
	m_SurroundEfc->SetActive(true);


	m_SurroundEfc->Init(
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
		colors4, scales4,
		maxDistance / 2 , maxDistance / 2,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/surround_shot_effect.tga"),
		true);

	m_SurroundEfc->StartEmission();


}

void cSkill_Round::BaseObjectUpdate(D3DXVECTOR3 CasterWorldPos, float timeDelta, D3DXVECTOR3 mousePos)
{


	m_CasterWorldPos = CasterWorldPos;

	m_MousePos = mousePos;

	pTransform->SetWorldPosition(m_MousePos);

	D3DXVECTOR3 selectMax = pTransform->GetWorldPosition() - m_CasterWorldPos;

	if (m_IsSelect)
	{

		m_SurroundEfc->Update(timeDelta);
		m_SurroundEfc->pTransform->SetWorldPosition(m_CasterWorldPos);

		if (D3DXVec3Length(&selectMax) < m_MaxDistance)
		{
			m_CircleEfc->Update(timeDelta);
			m_CircleEfc->pTransform->SetWorldPosition(m_MousePos);

			//클릭할 시 캐스팅이 시작되도록

			if (KEY_MGR->IsOnceDown(VK_LBUTTON))
			{
				m_IsCasting = true;

			}
		}
		else
		{
			m_CastEfc->Update(timeDelta);
			m_CastEfc->pTransform->SetWorldPosition(m_MousePos);
		}
	}

		


	if (m_IsCasting)  //캐스팅이 시작되면
	{

	}




}

void cSkill_Round::BaseObjectRender()
{

	D3DXVECTOR3 selectMax = pTransform->GetWorldPosition() - m_CasterWorldPos;


	if (m_IsSelect)
	{
		m_SurroundEfc->Render();

		if (D3DXVec3Length(&selectMax) < m_MaxDistance)
		{
			m_CircleEfc->Render();
			m_BoundSphere.RenderGizmo(pTransform);
		}
		else
		{
			m_CastEfc->Render();
			m_BoundSphere.RenderGizmo(pTransform);
		}

	
	}


	if (m_IsCasting)
	{

	}

}


void cSkill_Round::SelectSkill()
{
	m_IsSelect = true;

}

void cSkill_Round::StartCasting()
{

	m_IsCasting = true;
}

void cSkill_Round::UseSkill()
{


}