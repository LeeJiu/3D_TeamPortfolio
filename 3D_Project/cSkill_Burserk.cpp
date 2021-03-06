#include "stdafx.h"
#include "cSkill_Burserk.h"


cSkill_Burserk::cSkill_Burserk()
{
}

cSkill_Burserk::~cSkill_Burserk()
{
}

void cSkill_Burserk::Effect_Init()
{
	m_burserking = new cQuadParticleEmitter();
	m_burserking->SetActive(true);

	VEC_COLOR colors;
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales;
	scales.push_back(4.0f);  //초반 크기
	scales.push_back(4.0f);

	m_burserking->Init(
		10,
		30.0f,     //이펙트 몇장
		1.0f,       //라이브타임 (발생 횟수에 대한 시간(적을수록 겹겹이)
		5.0f,
		D3DXVECTOR3(0, 0, 0),     //시작위치에서 끝점까지의 거리
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(0, 0, 0),     //회전량
		D3DXVECTOR3(0, 0, 0),     //축회전 없이 태풍같은 이펙트는 고정
		D3DXVECTOR3(0, 0, 0),	//초기시작시 회전 min
		D3DXVECTOR3(0, 180 * ONE_RAD, 0),     //초기시작시 회전Max
		D3DXVECTOR3(0, 0, 0),				//초당 회전할 회전 량 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		D3DXVECTOR3(0, 0, 0),				//초당 회전 가속 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		colors, scales,
		1.5f / 2, 1.5f / 2,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/red_Buff.tga"),
		true);

	m_burserking_under = new cQuadParticleEmitter();
	m_burserking_under->SetActive(true);


	VEC_COLOR colors2;
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales2;
	scales2.push_back(1.0f);  //초반 크기
	scales2.push_back(2.0f);

	m_burserking_under->Init(
		100,
		5.0f,     //이펙트 몇장
		1.0f,       //라이브타임 (발생 횟수에 대한 시간(적을수록 겹겹이)
		1.0f,
		D3DXVECTOR3(0, 0, 0),     //시작위치에서 끝점까지의 거리
		D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(0, 0.5, 0),     //한쪽으로 발사하는 양 시작
		D3DXVECTOR3(0, 0.8, 0),     //한쪽으로 발사하는 양 끝
		D3DXVECTOR3(180 * ONE_RAD, 0, 0),	//초기시작시 회전 min
		D3DXVECTOR3(0, 180 * ONE_RAD, 0),     //초기시작시 회전Max
		D3DXVECTOR3(0, 0, 0),				//초당 회전할 회전 량 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		D3DXVECTOR3(0, 0, 0),				//초당 회전 가속 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		colors2, scales2,
		2.0f / 2, 2.0f / 2,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/red_cloud.tga"),
		true);

	m_burserking->StartEmission();
	m_burserking_under->StartEmission();

	m_DarkStorm_under = new cQuadParticleEmitter();
	m_DarkStorm_under->SetActive(true);


	VEC_COLOR colors3;
	colors3.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors3.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors3.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales3;
	scales3.push_back(3.0f);  //초반 크기
	scales3.push_back(3.0f);

	m_DarkStorm_under->Init(
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
		colors3, scales3,
		5.0f / 2, 5.0f / 2,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/RedStorm.tga"),
		true);

	m_burserking->StartEmission();
	m_burserking_under->StartEmission();
	m_DarkStorm_under->StartEmission();
}


void cSkill_Burserk::Effect_Update(float timeDelta)
{
	if (m_IsCasting)
	{
		m_DarkStorm_under->Update(timeDelta);
		m_DarkStorm_under->pTransform->SetWorldPosition(pTransform->GetWorldPosition());
		m_DarkStorm_under->pTransform->RotateSelf(D3DXVECTOR3(0, 10.0f, 0));
	}



	if (m_IsInBuff)
	{
		m_burserking->Update(timeDelta);
		m_burserking->pTransform->SetWorldPosition(pTransform->GetWorldPosition());
		m_burserking->pTransform->SetWorldPosition(pTransform->GetWorldPosition().x, pTransform->GetWorldPosition().y + 1.5f, pTransform->GetWorldPosition().z);
		m_burserking->pTransform->RotateSelf(D3DXVECTOR3(0.3f, 0, 0));
		m_burserking_under->Update(timeDelta);
		m_burserking_under->pTransform->SetWorldPosition(pTransform->GetWorldPosition());
		m_burserking_under->pTransform->SetWorldPosition(pTransform->GetWorldPosition().x, pTransform->GetWorldPosition().y + 1.5f, pTransform->GetWorldPosition().z);
		//m_burserking_under->pTransform->RotateSelf(D3DXVECTOR3(0, 5.0f, 0));
	}

}

void cSkill_Burserk::Effect_Render()
{

	if (m_IsCasting)
	{
		m_DarkStorm_under->Render();
	}

	if (m_IsInBuff)
	{
		m_burserking->Render();
		m_burserking_under->Render();
	}
}


