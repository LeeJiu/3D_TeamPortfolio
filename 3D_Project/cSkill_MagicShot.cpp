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
		50.0f,     //이펙트 몇장
		1.0f,       //라이브타임 (발생 횟수에 대한 시간(적을수록 겹겹이)
		1.0f,
		D3DXVECTOR3(0, 0, 0),     //시작위치에서 끝점까지의 거리
		D3DXVECTOR3(0, 1, -1),
		D3DXVECTOR3(0, 1, -1),     //회전량
		D3DXVECTOR3(1, 1, 1),     //축회전 없이 태풍같은 이펙트는 고정
		D3DXVECTOR3(90 * ONE_RAD, 90 * ONE_RAD, 0),	//초기시작시 회전 min
		D3DXVECTOR3(180 * ONE_RAD, 180 * ONE_RAD, 0),     //초기시작시 회전Max
		D3DXVECTOR3(0, 0, 0),				//초당 회전할 회전 량 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		D3DXVECTOR3(0, 0, 0),				//초당 회전 가속 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		colors, scales,
		1.0f /2, 2.5f /2,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/magicalATK.tga"),
		true);

	m_magicATK->StartEmission();
}

void cSkill_MagicShot::Effect_Update(float timeDelta)
{
	if (m_IsAttacking || m_IsShot)
	{
		m_magicATK->Update(timeDelta);
		m_magicATK->pTransform->SetWorldPosition(pTransform->GetWorldPosition());

	}



}

void cSkill_MagicShot::Effect_Render()
{
	if (m_IsAttacking || m_IsShot)
	{
		m_magicATK->Render();

		if (m_AttackingCount == m_AttackingTime / 1.5f)
		{
			m_magicATK->StopEmission();
		}
	}



}