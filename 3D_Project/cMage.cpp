#include "stdafx.h"
#include "cMage.h"
#include "cTerrain.h"
#include "cCamera.h"
#include "cItem.h"
//파티클
#include "cPartcleEmitter.h"
#include "cParticleQuad.h""
#include "cParticle.h"
#include "cQuadParticleEmitter.h"

//스킬

cMage::cMage()
{

}


cMage::~cMage()
{
	SAFE_DELETE(m_pMove);
	SAFE_DELETE(m_ATKBox);

	SAFE_DELETE(pWeapon);
	
}



void cMage::BaseObjectEnable()
{

	//몬스터 관련
	MonsterInit();

	

	//무기 관련

	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.1f);
	D3DXMATRIXA16 matRotate;
	D3DXMatrixRotationY(&matRotate, -90.0f * ONE_RAD);
	D3DXMATRIXA16 matCorrection = matScale * matRotate;

	cXMesh_Static* pSTF_Basic = RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Weapon/STF_Master.X", &matCorrection);


	pWeapon = new cItem;
	pWeapon->SetMesh(pSTF_Basic);
	pWeapon->SetActive(true);

	pSkinned->AddBoneTransform("Bip01-R-Hand", pWeapon->pTransform);

	m_isPetOn = false;

	//스킬 관련
	SkillInit();



	//평타 박스
	m_ATKBox = new cBaseObject;
	m_ATKBox->BoundBox.Init(D3DXVECTOR3(-0.3f, -0.3f, -0.3f), D3DXVECTOR3(0.3f, 0.3f, 0.3f));

	
	m_ATKBox->BoundBox.SetBound(&m_ATKBox->pTransform->GetWorldPosition(), &D3DXVECTOR3(-0.3f, -0.3f, -0.3f));
	pSkinned->AddBoneTransform("Bip01-L-Hand", m_ATKBox->pTransform);



	//캐릭터의 그려진 위치를 세팅
	pTransform->SetWorldPosition(0, pTerrain->GetHeight(0, 0), 0);
	D3DXVECTOR3	minPos(-1, 0, -1);
	D3DXVECTOR3	maxPos(1, 3, 1);
	BoundBox.Init(minPos, maxPos);

	m_state = IDLE;
	m_Aniname = SetAnimation(m_state);

	m_pMove = new moveClass;
	m_isMove = false;



	//무빙용으로 사용할 키값 세팅
	std::pair<int, bool> key_W('W', false);
	std::pair<int, bool> key_S('S', false);
	std::pair<int, bool> key_A('A', false);
	std::pair<int, bool> key_D('D', false);
	m_InputKeys.insert(key_W);
	m_InputKeys.insert(key_S);
	m_InputKeys.insert(key_A);
	m_InputKeys.insert(key_D);
	
	m_pMove->init(pTransform, pTerrain, m_camera, NULL);
}

void cMage::BaseObjectUpdate(float timeDelta)
{
	//펫에 타고 있냐
	if (KEY_MGR->IsOnceDown('9'))
	{
		if (m_isPetOn) m_isPetOn = false;
		else
		{
			m_state = PET_RUN;
			m_Aniname = SetAnimation(m_state);
			this->pSkinned->Play(m_Aniname, 0.3);
			m_isPetOn = true;
		}
	}


	if (m_isPetOn)
	{
		
	}
	else
	{


		//애니메이션셋
		if ((KEY_MGR->IsOnceDown('W') || KEY_MGR->IsOnceDown('D')
			|| KEY_MGR->IsOnceDown('A')))
		{
			m_state = RUN;
			m_Aniname = SetAnimation(m_state);
			this->pSkinned->Play(m_Aniname, 0.3);
		}


		if (m_isMove && KEY_MGR->IsOnceDown('S'))
		{
			m_state = WALK_BACK;
			m_Aniname = SetAnimation(m_state);
			this->pSkinned->Play(m_Aniname, 0.3);
		}

		if (!m_isMove && (KEY_MGR->IsOnceUp('W') || KEY_MGR->IsOnceUp('S')
			|| KEY_MGR->IsOnceUp('Q') || KEY_MGR->IsOnceUp('E')
			|| KEY_MGR->IsOnceUp('A') || KEY_MGR->IsOnceUp('D')))
		{
			m_state = WAIT;
			m_Aniname = SetAnimation(m_state);
			this->pSkinned->Play(m_Aniname, 0.3);
		}


		if (KEY_MGR->IsOnceDown('4'))
		{
			m_state = ATK_01;
			m_Aniname = SetAnimation(m_state);
			this->pSkinned->PlayOneShot(m_Aniname, 0.3);
			MagicATKInit();
			m_magicATK->StartEmission();
			m_isMagicATK = true;
			m_aniCount = 0;
			
		}

		if (KEY_MGR->IsOnceDown('5'))
		{
			m_state = STF_BUFF;
			m_Aniname = SetAnimation(m_state);
			this->pSkinned->PlayOneShot(m_Aniname, 0.3);
			m_magicShild->StartEmission();
			m_isMagicShild = true;
			m_aniCount = 0;
		}

		if (KEY_MGR->IsOnceDown('6'))
		{
			m_state = STF_FROZEN;
			m_Aniname = SetAnimation(m_state);
			this->pSkinned->PlayOneShot(m_Aniname, 0.3);
			FlameRoadInit();
			m_flameRoad_cast = true;
			m_flameRoad_cast_count = 0;
			m_aniCount = 0;
		}

		if (KEY_MGR->IsOnceDown('7'))
		{
			m_state = STF_STORM;
			m_Aniname = SetAnimation(m_state);
			this->pSkinned->PlayOneShot(m_Aniname, 0.3);
		}

		if (KEY_MGR->IsOnceDown('8'))
		{
			m_state = STF_TYFUNG;
			m_Aniname = SetAnimation(m_state);
			this->pSkinned->PlayOneShot(m_Aniname, 0.3);
			m_snowStrom->StartEmission();
			m_snowStrom_under->StartEmission();
			m_snow->StartEmission();
			m_isSnowStorm = true;
			m_aniCount = 0;
		}


		//===============무브==============================

		if (KEY_MGR->IsStayDown('W'))
		{
			m_InputKeys.find('W')->second = true;
		}
		else m_InputKeys.find('W')->second = false;


		if (KEY_MGR->IsStayDown('S'))
		{
			m_InputKeys.find('S')->second = true;
		}
		else m_InputKeys.find('S')->second = false;

		if (KEY_MGR->IsStayDown('A'))
		{
			m_InputKeys.find('A')->second = true;
		}
		else m_InputKeys.find('A')->second = false;

		if (KEY_MGR->IsStayDown('D'))
		{
			m_InputKeys.find('D')->second = true;

		}
		else m_InputKeys.find('D')->second = false;

		m_pMove->update(timeDelta, NULL, NULL, NULL, m_InputKeys);

		m_isMove = m_pMove->GetIsMove();

		LOG_MGR->AddLog("%s", m_Aniname.c_str());

	}

	this->pWeapon->Update(timeDelta);


	//스킬 사용 관련
	


	if (m_aniCount == 480)
	{
		m_snowStrom->StopEmission();
		m_snowStrom_under->StopEmission();
		m_snow->StopEmission();
		//m_isSnowStorm = false;
	}

	if (m_aniCount == 120)
	{
		m_magicATK->StopEmission();
		m_isMagicATK = false;
	}

	if (m_aniCount == 600)
	{
		m_magicShild->StopEmission();
		
	}


	if (m_flameRoad_cast)
	{
		m_flameRoad_cast_count++;
	}

	if (m_flameRoad_cast_count == 120)
	{
		m_flameRoad->StartEmission();
		m_flameRoad2->StartEmission();
		m_flameRoad3->StartEmission();
		m_isFlameRoad = true;
		m_aniCount = 0;
	}

	if (m_aniCount == 200)
	{
		m_flameRoad->StopEmission();
		m_flameRoad2->StopEmission();
		m_flameRoad3->StopEmission();
		m_flameRoad_cast_count = 0;
		m_isFlameRoad = false;
		m_flameRoad_cast = false;
	}



	if (m_isMagicATK)
	{
		m_aniCount++;
		m_magicATK->Update(timeDelta);
		m_magicATK->pTransform->SetWorldPosition(this->m_ATKBox->pTransform->GetWorldPosition());
	}



	if (m_isFlameRoad)
	{
		m_aniCount++;
		m_flameRoad->Update(timeDelta);
		m_flameRoad2->Update(timeDelta);
		m_flameRoad3->Update(timeDelta);
		m_flameRoad->pTransform->SetWorldPosition(pTransform->GetWorldPosition());
		m_flameRoad->pTransform->LookDirection(pTransform->GetForward(), 90.0f * ONE_RAD);
		m_flameRoad2->pTransform->SetWorldPosition(pTransform->GetWorldPosition());
		m_flameRoad2->pTransform->LookDirection(pTransform->GetForward(), 90.0f * ONE_RAD);
		m_flameRoad3->pTransform->SetWorldPosition(pTransform->GetWorldPosition());
		m_flameRoad3->pTransform->LookDirection(pTransform->GetForward(), 90.0f * ONE_RAD);
	}



	if (m_isSnowStorm)
	{
		m_aniCount++;
		m_snowStrom->pTransform->SetWorldPosition(pTransform->GetWorldPosition());
		m_snowStrom->Update(timeDelta);
		m_snowStrom_under->pTransform->SetWorldPosition(pTransform->GetWorldPosition());
		m_snowStrom_under->Update(timeDelta);
		m_snow->pTransform->SetWorldPosition(pTransform->GetWorldPosition() + D3DXVECTOR3(0,7,0));
		m_snow->Update(timeDelta);
	}


	if (m_isMagicShild)
	{
		m_aniCount++;
		m_magicShild->Update(timeDelta);
		m_magicShild->pTransform->SetWorldPosition(this->pTransform->GetWorldPosition());

	}
	


	MonsterUpdate(timeDelta);

}


void cMage::ATKBoxRender()
{



	//m_ATKBox->BoundBox.RenderGizmo(m_ATKBox->pTransform);


}

void cMage::WeaponRender()
{

	this->pWeapon->Render();
	
	MonsterRender();

	SkillRender();



}

void  cMage::SkillInit()
{
	m_aniCount = 0;
	SnowStormInit();
	MagicShildInit();
	
	m_isSnowStorm = false;
	m_isMagicATK = false;
	m_isMagicShild = false;
	m_isFlameRoad = false;
	m_flameRoad_cast = false;
}


void  cMage::SkillRender()
{
	if (m_isSnowStorm)
	{
		m_snowStrom_under->Render();
		m_snowStrom->Render();
		m_snow->Render();
		
	}

	if (m_isMagicATK)
	{
		m_magicATK->Render();
	}

	if (m_isMagicShild)
	{
		m_magicShild->Render();
	}

	if (m_isFlameRoad)
	{
		m_flameRoad->Render();
		m_flameRoad2->Render();
		m_flameRoad3->Render();
	}
	
}


//평타
void cMage::MagicATKInit()
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
		1.0f, 2.5f,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/magicalATK.tga"),
		true);

	m_magicATK->StartEmission();




}


void cMage::FlameRoadInit()
{
	m_flameRoad = new cQuadParticleEmitter();
	m_flameRoad->SetActive(true);


	VEC_COLOR colors;
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales;
	scales.push_back(1.0f);  //초반 크기
	scales.push_back(6.0f);

	m_flameRoad->Init(
		101,
		50.0f,     //이펙트 몇장
		1.0f,       //라이브타임 (발생 횟수에 대한 시간(적을수록 겹겹이)
		3.0f,
		D3DXVECTOR3(0, 1, 10),     //시작위치에서 끝점까지의 거리
		D3DXVECTOR3(0, 1, 20),
		D3DXVECTOR3(0, 0, 0),     //회전량
		D3DXVECTOR3(0, 0, 0),     //축회전 없이 태풍같은 이펙트는 고정
		D3DXVECTOR3(150 * ONE_RAD, 0, 0),	//초기시작시 회전 min
		D3DXVECTOR3(150 * ONE_RAD, 90 * ONE_RAD, 0),     //초기시작시 회전Max
		D3DXVECTOR3(0, 0, 0),				//초당 회전할 회전 량 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		D3DXVECTOR3(0, 0, 0),				//초당 회전 가속 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		colors, scales,
		1.0f, 3.0f,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/flame.tga"),
		true);


	m_flameRoad2 = new cQuadParticleEmitter();
	m_flameRoad2->SetActive(true);


	VEC_COLOR colors2;
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales2;
	scales2.push_back(1.0f);  //초반 크기
	scales2.push_back(4.0f);

	m_flameRoad2->Init(
		102,
		50.0f,     //이펙트 몇장
		1.0f,       //라이브타임 (발생 횟수에 대한 시간(적을수록 겹겹이)
		3.0f,
		D3DXVECTOR3(0, 1, 10),     //시작위치에서 끝점까지의 거리
		D3DXVECTOR3(0, 1, 20),
		D3DXVECTOR3(0, 0, 0),     //회전량
		D3DXVECTOR3(0, 0, 0),     //축회전 없이 태풍같은 이펙트는 고정
		D3DXVECTOR3(150 * ONE_RAD, 0, 0),	//초기시작시 회전 min
		D3DXVECTOR3(150 * ONE_RAD, 90 * ONE_RAD, 0),     //초기시작시 회전Max
		D3DXVECTOR3(0, 0, 0),				//초당 회전할 회전 량 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		D3DXVECTOR3(0, 0, 0),				//초당 회전 가속 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		colors2, scales2,
		1.0f, 3.0f,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/flame2.tga"),
		true);

	m_flameRoad3 = new cPartcleEmitter();
	m_flameRoad3->SetActive(true);

	//배열을 2 개이상 
	VEC_COLOR colors3;
	colors3.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors3.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	VEC_SCALE scales3;
	scales3.push_back(0.1f);
	scales3.push_back(0.1f);

	LPDIRECT3DTEXTURE9 pTex = RESOURCE_TEXTURE->GetResource(
		"../Resources/Textures/Effects/flame3.tga");

	//파티클 랜더러 셋팅
	m_flameRoad3->Init(
		50,				//최대 파티클 수
		5.0f,				//초당 파티클 발생 량
		7,					//하나의 파티클 입자 라이프 최소값
		10,					//하나의 파티클 입자 라이프 최대값
		D3DXVECTOR3(0, 5, 10),	//파티클 입자 속도 최소값 ( 로컬기준 )
		D3DXVECTOR3(0, 10, 20),	//파티클 입자 속도 최대값 ( 로컬기준 )
		D3DXVECTOR3(0, 0, 0),	//파티클 입자 가속 최소값 ( 로컬기준 )
		D3DXVECTOR3(0, 0, 0), //파티클 입자 가속 최대값 ( 로컬기준 )
		colors3,				//컬러 배열
		scales3,				//스케일 배열
		1.1f,				//입자크기 최소값
		5.2f,				//최대값
		pTex,				//텍스쳐
		false);


	m_flameRoad3->EmissionType = PATICLE_EMISSION_TYPE::SPHERE_OUTLINE;
	m_flameRoad3->SphereEmissionRange = 3.0f;

}





//매직 실드

void cMage::MagicShildInit()
{
	m_magicShild = new cQuadParticleEmitter();
	m_magicShild->SetActive(true);

	VEC_COLOR colors;
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales;
	scales.push_back(5.0f);  //초반 크기
	scales.push_back(5.0f);

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
		2.0f, 2.0f,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/magicShild.tga"),
		true);

}


//스노우 스톰 

void cMage::SnowStormInit()
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
		1.0f,       //라이브타임 (발생 횟수에 대한 시간(적을수록 겹겹이)
		5.0f,
		D3DXVECTOR3(0, 2, 0),     //시작위치에서 끝점까지의 거리
		D3DXVECTOR3(0, 10, 0),
		D3DXVECTOR3(0, 0, 0),     //회전량
		D3DXVECTOR3(0, 0, 0),     //축회전 없이 태풍같은 이펙트는 고정
		D3DXVECTOR3(90 * ONE_RAD, 0, 0),	//초기시작시 회전 min
		D3DXVECTOR3(90 * ONE_RAD, 0, 0),     //초기시작시 회전Max
		D3DXVECTOR3(0, 0, 0),				//초당 회전할 회전 량 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		D3DXVECTOR3(0, 0, 0),				//초당 회전 가속 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		colors, scales,
		3.0f, 3.0f,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/snowStrom.tga"),
		true);


	m_snowStrom_under = new cQuadParticleEmitter();
	m_snowStrom_under->SetActive(true);


	VEC_COLOR colors2;
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	VEC_SCALE scales2;
	scales2.push_back(2.0f);  //초반 크기
	scales2.push_back(2.0f);

	m_snowStrom_under->Init(
		100,
		40.0f,     //이펙트 몇장
		1.0f,       //라이브타임 (발생 횟수에 대한 시간(적을수록 겹겹이)
		1.0f,
		D3DXVECTOR3(0, 1, 0),     //시작위치에서 끝점까지의 거리
		D3DXVECTOR3(0, 7, 0),
		D3DXVECTOR3(0, 0.5, 0),     //한쪽으로 발사하는 양 시작
		D3DXVECTOR3(0, 0.8, 0),     //한쪽으로 발사하는 양 끝
		D3DXVECTOR3(-90 * ONE_RAD, 0, 0),	//초기시작시 회전 min
		D3DXVECTOR3 (- 90 * ONE_RAD, 0, 720 * ONE_RAD),     //초기시작시 회전Max
		D3DXVECTOR3(0, 0, 0),				//초당 회전할 회전 량 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		D3DXVECTOR3(0, 0, 0),				//초당 회전 가속 Min
		D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
		colors2, scales2,
		3.0f, 9.0f,
		RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/snowStorm2.tga"),
		true);

	m_snow = new cPartcleEmitter();
	m_snow->SetActive(true);

	//배열을 2 개이상 
	VEC_COLOR colors_snow;
	colors_snow.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	colors_snow.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	VEC_SCALE scales_snow;
	scales_snow.push_back(0.1f);
	scales_snow.push_back(0.1f);

	LPDIRECT3DTEXTURE9 pTex = RESOURCE_TEXTURE->GetResource(
		"../Resources/Textures/Effects/snow.tga");

	//파티클 랜더러 셋팅
	m_snow->Init(
		50,				//최대 파티클 수
		30.0f,				//초당 파티클 발생 량
		7,					//하나의 파티클 입자 라이프 최소값
		10,					//하나의 파티클 입자 라이프 최대값
		D3DXVECTOR3(0, 0, 0),	//파티클 입자 속도 최소값 ( 로컬기준 )
		D3DXVECTOR3(-10, 10, -10),	//파티클 입자 속도 최대값 ( 로컬기준 )
		D3DXVECTOR3(0, 0, 0),	//파티클 입자 가속 최소값 ( 로컬기준 )
		D3DXVECTOR3(0, 0, 0), //파티클 입자 가속 최대값 ( 로컬기준 )
		colors_snow,				//컬러 배열
		scales_snow,				//스케일 배열
		1.1f,				//입자크기 최소값
		50.2f,				//최대값
		pTex,				//텍스쳐
		false);


	m_snow->EmissionType = PATICLE_EMISSION_TYPE::SPHERE_OUTLINE;
	m_snow->SphereEmissionRange = 3.0f;
	m_snow->StartEmission();

	m_snowStrom->StartEmission();
	m_snowStrom_under->StartEmission();




}


void cMage::MonsterInit()
{
	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.1f);
	D3DXMATRIXA16 matRotate;
	D3DXMatrixRotationY(&matRotate, -90.0f * ONE_RAD);
	D3DXMATRIXA16 matCorrection = matScale * matRotate;

	cXMesh_Skinned* pMonster = RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Monster/Minho/MOB_Minho.X", &matCorrection);

	//무기 관련
	m_pMonster = new cBaseObject;
	m_pMonster->SetMesh(pMonster);
	m_pMonster->SetActive(true);

	m_pMonster->BoundBox.Init(D3DXVECTOR3(-0.5, -0.5, -0.5), D3DXVECTOR3(0.5, 5.5, 0.5));
	m_pMonster->pTransform->SetWorldPosition(D3DXVECTOR3(0, 8, 0));


	m_isTarget = false;
	m_MobCollision = false;




}


void cMage::MonsterUpdate(float timeDelta)
{
	
	m_pMonster->pSkinned->Update(timeDelta);



	MonsterCollision(timeDelta);
	
	

}


void cMage::MonsterCollision(float timeDelta)
{

	D3DXVECTOR3 magicATKLegth = pTransform->GetWorldPosition() - m_pMonster->pTransform->GetWorldPosition();

	if (KEY_MGR->IsOnceDown(VK_LBUTTON))
	{
		Ray ray;
		POINT ptMousePos = GetMousePos();
		D3DXVECTOR2 screenPos(ptMousePos.x, ptMousePos.y);
		this->m_camera->ComputeRay(&ray, &screenPos);

		if (PHYSICS_MGR->IsRayHitBound(&ray, &m_pMonster->BoundBox, m_pMonster->pTransform, NULL, NULL))
		{
			m_isTarget = true;
			m_pMonster->pSkinned->PlayOneShot("WAIT", 0.3f);

		}
		else
		{
			m_isTarget = false;
			m_pMonster->pSkinned->Play("IDLE", 0.3f);
		}


		if (m_isTarget &&D3DXVec3Length(&magicATKLegth) > 20)
		{
			m_state = RUN;
			m_Aniname = SetAnimation(m_state);
			this->pSkinned->Play(m_Aniname, 0.3);
		}

	
	}



	if (m_isTarget && D3DXVec3Length(&magicATKLegth) > 20)
	{
		pTransform->LookPosition(m_pMonster->pTransform->GetWorldPosition(), 90.0f * ONE_RAD);
		pTransform->MovePositionSelf(D3DXVECTOR3(0, 0, 10.0f * timeDelta));
		m_StateCount = 0;
		//사거리 밖이면 이동해라
	}
	else
	{

		m_StateCount++;
		if (m_StateCount == 1)
		{
			m_state = WAIT;
			m_Aniname = SetAnimation(m_state);
			this->pSkinned->Play(m_Aniname, 0.3);
		}
	
	}




	if (m_isTarget && D3DXVec3Length(&magicATKLegth) < 20);
	{
	

		if (m_isMagicATK)
		{
			pSkinned->RemoveBoneTransform("Bip01-L-Hand");
			m_ATKBox->pTransform->LookPosition(m_pMonster->pTransform->GetWorldPosition() + D3DXVECTOR3(0, 2, 0));
			m_ATKBox->pTransform->MovePositionSelf(0, 0, 30.0f * timeDelta);
		}
		else
		{
			pSkinned->AddBoneTransform("Bip01-L-Hand", m_ATKBox->pTransform);
		}
	
	}
	
	if (PHYSICS_MGR->IsOverlap(m_ATKBox, m_pMonster))
	{
		
	}





}


void cMage::MonsterRender()
{

	m_pMonster->Render();
	m_pMonster->BoundBox.RenderGizmo(m_pMonster->pTransform);

}