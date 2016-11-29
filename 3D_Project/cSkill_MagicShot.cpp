#include "stdafx.h"
#include "cSkill_MagicShot.h"


cSkill_MagicShot::cSkill_MagicShot()
{
}


cSkill_MagicShot::~cSkill_MagicShot()
{
}



void cSkill_MagicShot::Effect_Init()
{
	m_magicATK = new cQuadParticleEmitter;
	m_magicATK->SetActive(true);

	VEC_COLOR colors;
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales;
	scales.push_back(1.5f);  //초반 크기
	scales.push_back(2.5f);

	m_magicATK->Init(
		100,
		10.0f,     //이펙트 몇장
		0.0f,       //라이브타임 (발생 횟수에 대한 시간(적을수록 겹겹이)
		0.5f,
		D3DXVECTOR3(0, 0, 0),     //시작위치에서 끝점까지의 거리
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(0, 0, 0),     //회전량
		D3DXVECTOR3(0, 0, 0),     //축회전 없이 태풍같은 이펙트는 고정
		D3DXVECTOR3(0, 180 * ONE_RAD, 0),	//초기시작시 회전 min
		D3DXVECTOR3(180 * ONE_RAD, 0, 0),     //초기시작시 회전Max
		D3DXVECTOR3(0, 0, 0),				//초당 회전할 회전 량 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		D3DXVECTOR3(0, 0, 0),				//초당 회전 가속 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		colors, scales,
		5.0f /2, 7.5f /2,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/magicalATK2.tga"),
		true);

	m_magicATK->StartEmission();


	//2번 매직박스

	m_magicATK2 = new cQuadParticleEmitter;
	m_magicATK2->SetActive(true);

	VEC_COLOR colors2;
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales2;
	scales2.push_back(1.5f);  //초반 크기
	scales2.push_back(2.5f);

	m_magicATK2->Init(
		100,
		20.0f,     //이펙트 몇장
		0.0f,       //라이브타임 (발생 횟수에 대한 시간(적을수록 겹겹이)
		0.5f,
		D3DXVECTOR3(0, 0, 0),     //시작위치에서 끝점까지의 거리
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(0, 0, 0),     //회전량
		D3DXVECTOR3(0, 0, 0),     //축회전 없이 태풍같은 이펙트는 고정
		D3DXVECTOR3(0, 180 * ONE_RAD, 0),	//초기시작시 회전 min
		D3DXVECTOR3(180 * ONE_RAD, 0, 0),     //초기시작시 회전Max
		D3DXVECTOR3(0, 0, 0),				//초당 회전할 회전 량 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		D3DXVECTOR3(0, 0, 0),				//초당 회전 가속 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		colors2, scales2,
		10.0f / 2, 10.5f / 2,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/magicalATK.tga"),
		true);

	m_magicATK2->StartEmission();

	m_magicATK3 = new cQuadParticleEmitter;
	m_magicATK3->SetActive(true);

	VEC_COLOR colors3;
	colors3.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors3.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors3.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales3;
	scales3.push_back(1.5f);  //초반 크기
	scales3.push_back(2.5f);

	m_magicATK3->Init(
		100,
		10.0f,     //이펙트 몇장
		0.0f,       //라이브타임 (발생 횟수에 대한 시간(적을수록 겹겹이)
		0.5f,
		D3DXVECTOR3(0, 0, 0),     //시작위치에서 끝점까지의 거리
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(0, 0, 0),     //회전량
		D3DXVECTOR3(0, 0, 0),     //축회전 없이 태풍같은 이펙트는 고정
		D3DXVECTOR3(0, 180 * ONE_RAD, 0),	//초기시작시 회전 min
		D3DXVECTOR3(180 * ONE_RAD, 0, 0),     //초기시작시 회전Max
		D3DXVECTOR3(0, 0, 0),				//초당 회전할 회전 량 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		D3DXVECTOR3(0, 0, 0),				//초당 회전 가속 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		colors3, scales3,
		3.5f / 2, 5.5f / 2,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/magicalATK2.tga"),
		true);

	m_magicATK3->StartEmission();



}

void cSkill_MagicShot::Effect_Update(float timeDelta)
{

	if (m_AttackingCount == 1)
	{
		m_magicATK2->pTransform->SetWorldPosition(pTransform->GetWorldPosition());
		m_magicATK3->pTransform->SetWorldPosition(pTransform->GetWorldPosition());
	}

	if (m_IsAttacking || m_IsShot)
	{
		m_magicATK->Update(timeDelta);
		m_magicATK->pTransform->SetWorldPosition(pTransform->GetWorldPosition());

		float followSpeed = 7.0f;
		m_magicATK2->Update(timeDelta);
		m_magicATK2->pTransform->Interpolate(*m_magicATK2->pTransform, *pTransform, followSpeed * timeDelta);

		m_magicATK3->Update(timeDelta);
		m_magicATK3->pTransform->Interpolate(*m_magicATK3->pTransform, *m_magicATK2->pTransform, followSpeed * timeDelta);

		
		//m_magicATK->pTransform->RotateSelf(D3DXVECTOR3(0.5f, 0, 0));


	}



}

void cSkill_MagicShot::Effect_Render()
{
	if (m_IsAttacking || m_IsShot)
	{
		if (m_IsHit)
		{
			m_magicATK2->Render();
		}
		m_magicATK->Render();
		m_magicATK3->Render();

		if (m_AttackingCount == m_AttackingTime / 1.5f)
		{
			//m_magicATK->StopEmission();
		}
	}



}