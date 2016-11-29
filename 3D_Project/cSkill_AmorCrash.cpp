#include "stdafx.h"
#include "cSkill_AmorCrash.h"


cSkill_AmorCrash::cSkill_AmorCrash()
{
}


cSkill_AmorCrash::~cSkill_AmorCrash()
{
}


void cSkill_AmorCrash::Effect_Init()
{
	m_snowStrom = new cQuadParticleEmitter();
	m_snowStrom->SetActive(true);

	VEC_COLOR colors;
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales;
	scales.push_back(1.0f);  //초반 크기
	scales.push_back(5.0f);

	m_snowStrom->Init(
		100,
		100.0f,     //이펙트 몇장
		5.0f,       //라이브타임 (발생 횟수에 대한 시간(적을수록 겹겹이)
		5.5f,
		D3DXVECTOR3(0, 1, 0),     //시작위치에서 끝점까지의 거리
		D3DXVECTOR3(0, 4, 0),
		D3DXVECTOR3(0, 0, 0),     //회전량
		D3DXVECTOR3(0, 0, 0),     //축회전 없이 태풍같은 이펙트는 고정
		D3DXVECTOR3(0, 90 * ONE_RAD, 0),	//초기시작시 회전 min
		D3DXVECTOR3(90 * ONE_RAD, 0, 0),     //초기시작시 회전Max
		D3DXVECTOR3(0, 0, 0),				//초당 회전할 회전 량 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		D3DXVECTOR3(0, 0, 0),				//초당 회전 가속 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		colors, scales,
		0.0f, 5.0f,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/blood.tga"),
		true);


	m_snowStrom_under = new cQuadParticleEmitter();
	m_snowStrom_under->SetActive(true);


	VEC_COLOR colors2;
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales2;
	scales2.push_back(3.0f);  //초반 크기
	scales2.push_back(3.0f);

	m_snowStrom_under->Init(
		100,
		20.0f,     //이펙트 몇장
		1.0f,       //라이브타임 (발생 횟수에 대한 시간(적을수록 겹겹이)
		1.0f,
		D3DXVECTOR3(0, 0, 0),     //시작위치에서 끝점까지의 거리
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(0, 0.5, 0),     //한쪽으로 발사하는 양 시작
		D3DXVECTOR3(0, 0.8, 0),     //한쪽으로 발사하는 양 끝
		D3DXVECTOR3(-90 * ONE_RAD, 0, 0),	//초기시작시 회전 min
		D3DXVECTOR3(-90 * ONE_RAD, 0, 720 * ONE_RAD),     //초기시작시 회전Max
		D3DXVECTOR3(0, 0, 0),				//초당 회전할 회전 량 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		D3DXVECTOR3(0, 0, 0),				//초당 회전 가속 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		colors2, scales2,
		0.0f, 3.0f,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/blood.tga"),
		true);


	m_chargeEfc = new cQuadParticleEmitter();
	m_chargeEfc->SetActive(true);

	VEC_COLOR colors3;
	colors3.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors3.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors3.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales3;
	scales3.push_back(1.0f);  //초반 크기
	scales3.push_back(5.0f);

	m_chargeEfc->Init(
		10,
		30.0f,     //이펙트 몇장
		1.0f,       //라이브타임 (발생 횟수에 대한 시간(적을수록 겹겹이)
		1.0f,
		D3DXVECTOR3(0, 0, 0),     //시작위치에서 끝점까지의 거리
		D3DXVECTOR3(0, 1, 0),
		D3DXVECTOR3(0, 0, 0),     //회전량
		D3DXVECTOR3(0, 0, 0),     //축회전 없이 태풍같은 이펙트는 고정
		D3DXVECTOR3(0, 0, 0),	//초기시작시 회전 min
		D3DXVECTOR3(0, 180 * ONE_RAD, 0),     //초기시작시 회전Max
		D3DXVECTOR3(0, 0, 0),				//초당 회전할 회전 량 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		D3DXVECTOR3(0, 0, 0),				//초당 회전 가속 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		colors, scales,
		0.0f / 2, 5.0f / 2,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/charge.tga"),
		true);

	m_chargeEfc_under = new cQuadParticleEmitter();
	m_chargeEfc_under->SetActive(true);

	VEC_COLOR colors4;
	colors4.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors4.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors4.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales4;
	scales4.push_back(1.0f);  //초반 크기
	scales4.push_back(5.0f);

	m_chargeEfc_under->Init(
		100,
		5.0f,     //이펙트 몇장
		1.0f,       //라이브타임 (발생 횟수에 대한 시간(적을수록 겹겹이)
		1.0f,
		D3DXVECTOR3(0, 0, 0),     //시작위치에서 끝점까지의 거리
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(0, 0.5, 0),     //한쪽으로 발사하는 양 시작
		D3DXVECTOR3(0, 0.8, 0),     //한쪽으로 발사하는 양 끝
		D3DXVECTOR3(-90 * ONE_RAD, 0, 0),	//초기시작시 회전 min
		D3DXVECTOR3(-90 * ONE_RAD, 0, 720 * ONE_RAD),     //초기시작시 회전Max
		D3DXVECTOR3(0, 0, 0),				//초당 회전할 회전 량 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		D3DXVECTOR3(0, 0, 0),				//초당 회전 가속 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		colors2, scales2,
		0.0f / 2, 5.0f / 2,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/chargeStorm.tga"),
		true);

	m_snowStrom->StartEmission();
	m_snowStrom_under->StartEmission();
	m_chargeEfc->StartEmission();
	m_chargeEfc_under->StartEmission();


}

void cSkill_AmorCrash::Effect_Update(float timeDelta)
{
	if (m_CastTime / 1.2 == m_CastTimeCount)
	{
		//m_snowStrom_under->StopEmission();
		//m_snow->StopEmission();
	}

	if (m_AttackingTime / 0.9 == m_AttackingCount)
	{
		m_snowStrom->StopEmission();

	}


	if (m_IsSelect)
	{
		m_chargeEfc->Update(timeDelta);
		m_chargeEfc_under->Update(timeDelta);
		m_chargeEfc->pTransform->SetWorldPosition(m_CasterWorldPos.x, m_CasterWorldPos.y + 1, m_CasterWorldPos.z);
		m_chargeEfc_under->pTransform->SetWorldPosition(m_CasterWorldPos);
		m_chargeEfc_under->pTransform->RotateSelf(D3DXVECTOR3(0, -5.0f, 0));

	}


	if (m_IsAttacking)
	{
		m_snowStrom_under->pTransform->SetWorldPosition(m_AttackPos);
		m_snowStrom_under->Update(timeDelta);
		m_snowStrom->pTransform->SetWorldPosition(m_AttackPos);
		m_snowStrom->Update(timeDelta);

	}
}


void cSkill_AmorCrash::Effect_Render()
{
	if (m_IsSelect)
	{
		
		m_chargeEfc_under->Render();
		m_chargeEfc->Render();
	}

	if (m_IsAttacking)
	{
		m_snowStrom_under->Render();

		m_snowStrom->Render();


	}

}