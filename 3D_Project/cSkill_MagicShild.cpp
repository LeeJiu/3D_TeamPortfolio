#include "stdafx.h"
#include "cSkill_MagicShild.h"


cSkill_MagicShild::cSkill_MagicShild()
{
}


cSkill_MagicShild::~cSkill_MagicShild()
{
	

}


void cSkill_MagicShild::Effect_Init()
{
	SOUND_MGR->addSound("mage_magicShild", "../Resources/Sound/메이지_버프_음성.ogg", false, false);
	SOUND_MGR->addSound("mage_magicShild_se", "../Resources/Sound/메이지_버프.ogg", false, false);

	m_magicShild = new cQuadParticleEmitter();
	m_magicShild->SetActive(true);

	VEC_COLOR colors;
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales;
	scales.push_back(4.0f);  //초반 크기
	scales.push_back(4.0f);

	m_magicShild->Init(
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
		2.0f/2, 2.0f/2,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/magicShild.tga"),
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
		D3DXVECTOR3(0, 5, 0),
		D3DXVECTOR3(0, 0.5, 0),     //한쪽으로 발사하는 양 시작
		D3DXVECTOR3(0, 0.8, 0),     //한쪽으로 발사하는 양 끝
		D3DXVECTOR3(-90 * ONE_RAD, 0, 0),	//초기시작시 회전 min
		D3DXVECTOR3(-90 * ONE_RAD, 0, 720 * ONE_RAD),     //초기시작시 회전Max
		D3DXVECTOR3(0, 0, 0),				//초당 회전할 회전 량 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		D3DXVECTOR3(0, 0, 0),				//초당 회전 가속 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		colors2, scales2,
		2.0f/2, 2.0f/2,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/magicAura.tga"),
		true);

	m_magicShild->StartEmission();
	m_snowStrom_under->StartEmission();
}

void cSkill_MagicShild::Effect_Update(float timeDelta)
{
	if (m_BuffCount == 1)
	{
		SOUND_MGR->play("mage_magicShild", 0.8f);
		SOUND_MGR->play("mage_magicShild_se", 0.8f);
	}



	if (m_IsInBuff)
	{
		m_magicShild->Update(timeDelta);
		m_magicShild->pTransform->SetWorldPosition(pTransform->GetWorldPosition());
		m_magicShild->pTransform->SetWorldPosition(pTransform->GetWorldPosition().x, pTransform->GetWorldPosition().y + 1, pTransform->GetWorldPosition().z);
		m_snowStrom_under->Update(timeDelta);
		m_snowStrom_under->pTransform->SetWorldPosition(pTransform->GetWorldPosition());
		m_snowStrom_under->pTransform->SetWorldPosition(pTransform->GetWorldPosition().x, pTransform->GetWorldPosition().y, pTransform->GetWorldPosition().z);
		m_snowStrom_under->pTransform->RotateSelf(D3DXVECTOR3(0, 5.0f, 0));
	}



}

void cSkill_MagicShild::Effect_Render()
{

	if (m_IsInBuff)
	{
		m_magicShild->Render();
		m_snowStrom_under->Render();
	}
}