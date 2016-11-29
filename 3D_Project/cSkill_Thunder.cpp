#include "stdafx.h"
#include "cSkill_Thunder.h"


cSkill_Thunder::cSkill_Thunder()
{
}


cSkill_Thunder::~cSkill_Thunder()
{
}


void cSkill_Thunder::Effect_Init()
{
	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.05f, 0.05f, 0.05f);
	D3DXMATRIXA16 matCorrection = matScale;


	m_snowStrom = new cQuadParticleEmitter();
	m_snowStrom->SetActive(true);

	VEC_COLOR colors;
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales;
	scales.push_back(5.0f);  //초반 크기
	scales.push_back(5.0f);

	m_snowStrom->Init(
		100,
		5.0f,     //이펙트 몇장
		1.0f,       //라이브타임 (발생 횟수에 대한 시간(적을수록 겹겹이)
		1.0f,
		D3DXVECTOR3(0, 0, 0),     //시작위치에서 끝점까지의 거리
		D3DXVECTOR3(2, 0, 1),
		D3DXVECTOR3(0, 0, 0),     //회전량
		D3DXVECTOR3(0, 0, 0),     //축회전 없이 태풍같은 이펙트는 고정
		D3DXVECTOR3(180 * ONE_RAD, 0, 0),	//초기시작시 회전 min
		D3DXVECTOR3(180 * ONE_RAD, 90 * ONE_RAD, 0),     //초기시작시 회전Max
		D3DXVECTOR3(0, 0, 0),				//초당 회전할 회전 량 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		D3DXVECTOR3(0, 0, 0),				//초당 회전 가속 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		colors, scales,
		30.0f, 30.0f,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/thunder_1.tga"),
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
		5.0f,     //이펙트 몇장
		1.0f,       //라이브타임 (발생 횟수에 대한 시간(적을수록 겹겹이)
		1.0f,
		D3DXVECTOR3(0, 1, 0),     //시작위치에서 끝점까지의 거리
		D3DXVECTOR3(0, 2, 0),
		D3DXVECTOR3(0, 0.5, 0),     //한쪽으로 발사하는 양 시작
		D3DXVECTOR3(0, 0.8, 0),     //한쪽으로 발사하는 양 끝
		D3DXVECTOR3(-90 * ONE_RAD, 0, 0),	//초기시작시 회전 min
		D3DXVECTOR3(-90 * ONE_RAD, 0, 720 * ONE_RAD),     //초기시작시 회전Max
		D3DXVECTOR3(0, 0, 0),				//초당 회전할 회전 량 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		D3DXVECTOR3(0, 0, 0),				//초당 회전 가속 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		colors2, scales2,
		50.0f, 50.0f,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/darkCloud.tga"),
		true);

	m_snowStrom->StartEmission();
	m_snowStrom_under->StartEmission();


	//m_isSnowStorm = true;

}


void cSkill_Thunder::Effect_Update(float timeDelta)
{
	if (m_CastTime / 1.2 == m_CastTimeCount)
	{
		m_snowStrom_under->StopEmission();
	}

	if (m_AttackingTime - 50 == m_AttackingCount)
	{
		m_snowStrom->StopEmission();

	}


	if (m_IsCasting || m_IsAttacking)
	{
		if(m_CastTimeCount == 1)
		{
			m_snowStrom_under->pTransform->SetWorldPosition(D3DXVECTOR3(m_AttackPos.z, m_AttackPos.y + 50, m_AttackPos.z));
		}

		m_snowStrom_under->pTransform->RotateSelf(D3DXVECTOR3(0, -0.5*timeDelta, 0));
		m_snowStrom_under->Update(timeDelta);



	}


	if (m_IsAttacking)
	{

		m_snowStrom->pTransform->SetWorldPosition(m_AttackPos);
		//m_snowStrom->pTransform->RotateSelf(D3DXVECTOR3(0, -10.0*timeDelta, 0));
		m_snowStrom->Update(timeDelta);

	}

}

void cSkill_Thunder::Effect_Render()
{

	if (m_IsCasting || m_IsAttacking)
	{
		m_snowStrom_under->Render();
	}

	if (m_IsAttacking)
	{
		m_snowStrom->Render();

	}

}