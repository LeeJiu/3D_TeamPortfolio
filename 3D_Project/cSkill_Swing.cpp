#include "stdafx.h"
#include "cSkill_Swing.h"


cSkill_Swing::cSkill_Swing()
{
}


cSkill_Swing::~cSkill_Swing()
{
}


void cSkill_Swing::Effect_Init()
{

	//D3DXMATRIXA16 matScale;
	//D3DXMatrixScaling(&matScale, 0.3f, 0.3f, 0.3f);
	//D3DXMATRIXA16 matCorrection = matScale;
	//
	////m_DarkDorm = new cXMesh_Static;
	////m_DarkDorm->Init("../Resources/Textures/Effects/Dorm_ice.X", &matCorrection);
	//
	//m_snowStrom = new cQuadParticleEmitter();
	//m_snowStrom->SetActive(true);
	//
	//VEC_COLOR colors;
	//colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	//colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//colors.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	//
	//VEC_SCALE scales;
	//scales.push_back(1.0f);  //초반 크기
	//scales.push_back(5.0f);
	//
	//m_snowStrom->Init(
	//	100,
	//	100.0f,     //이펙트 몇장
	//	1.0f,       //라이브타임 (발생 횟수에 대한 시간(적을수록 겹겹이)
	//	5.0f,
	//	D3DXVECTOR3(0, 2, 0),     //시작위치에서 끝점까지의 거리
	//	D3DXVECTOR3(0, 10, 0),
	//	D3DXVECTOR3(0, 0, 0),     //회전량
	//	D3DXVECTOR3(0, 0, 0),     //축회전 없이 태풍같은 이펙트는 고정
	//	D3DXVECTOR3(90 * ONE_RAD, 0, 0),	//초기시작시 회전 min
	//	D3DXVECTOR3(90 * ONE_RAD, 0, 0),     //초기시작시 회전Max
	//	D3DXVECTOR3(0, 0, 0),				//초당 회전할 회전 량 Min
	//	D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
	//	D3DXVECTOR3(0, 0, 0),				//초당 회전 가속 Min
	//	D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
	//	colors, scales,
	//	3.0f, 3.0f,
	//	RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/snowStrom.tga"),
	//	true);
	//
	//
	//m_snowStrom_under = new cQuadParticleEmitter();
	//m_snowStrom_under->SetActive(true);
	//
	//
	//VEC_COLOR colors2;
	//colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	//colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//colors2.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	//
	//VEC_SCALE scales2;
	//scales2.push_back(2.0f);  //초반 크기
	//scales2.push_back(2.0f);
	//
	//m_snowStrom_under->Init(
	//	100,
	//	40.0f,     //이펙트 몇장
	//	1.0f,       //라이브타임 (발생 횟수에 대한 시간(적을수록 겹겹이)
	//	1.0f,
	//	D3DXVECTOR3(0, 1, 0),     //시작위치에서 끝점까지의 거리
	//	D3DXVECTOR3(0, 7, 0),
	//	D3DXVECTOR3(0, 0.5, 0),     //한쪽으로 발사하는 양 시작
	//	D3DXVECTOR3(0, 0.8, 0),     //한쪽으로 발사하는 양 끝
	//	D3DXVECTOR3(-90 * ONE_RAD, 0, 0),	//초기시작시 회전 min
	//	D3DXVECTOR3(-90 * ONE_RAD, 0, 720 * ONE_RAD),     //초기시작시 회전Max
	//	D3DXVECTOR3(0, 0, 0),				//초당 회전할 회전 량 Min
	//	D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
	//	D3DXVECTOR3(0, 0, 0),				//초당 회전 가속 Min
	//	D3DXVECTOR3(0, 0, 0),				//축회전 없이 태풍같은 이펙트는 고정
	//	colors2, scales2,
	//	3.0f, 9.0f,
	//	RESOURCE_TEXTURE->GetResource("../Resources/Textures/Effects/snowStorm2.tga"),
	//	true);
	//
	//m_snow = new cPartcleEmitter();
	//m_snow->SetActive(true);
	//
	////배열을 2 개이상 
	//VEC_COLOR colors_snow;
	//colors_snow.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//colors_snow.push_back(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//
	//VEC_SCALE scales_snow;
	//scales_snow.push_back(0.1f);
	//scales_snow.push_back(0.1f);
	//
	//LPDIRECT3DTEXTURE9 pTex = RESOURCE_TEXTURE->GetResource(
	//	"../Resources/Textures/Effects/snow.tga");
	//
	////파티클 랜더러 셋팅
	//m_snow->Init(
	//	50,				//최대 파티클 수
	//	30.0f,				//초당 파티클 발생 량
	//	7,					//하나의 파티클 입자 라이프 최소값
	//	10,					//하나의 파티클 입자 라이프 최대값
	//	D3DXVECTOR3(0, 0, 0),	//파티클 입자 속도 최소값 ( 로컬기준 )
	//	D3DXVECTOR3(-10, 10, -10),	//파티클 입자 속도 최대값 ( 로컬기준 )
	//	D3DXVECTOR3(0, 0, 0),	//파티클 입자 가속 최소값 ( 로컬기준 )
	//	D3DXVECTOR3(0, 0, 0), //파티클 입자 가속 최대값 ( 로컬기준 )
	//	colors_snow,				//컬러 배열
	//	scales_snow,				//스케일 배열
	//	1.1f,				//입자크기 최소값
	//	50.2f,				//최대값
	//	pTex,				//텍스쳐
	//	false);
	//
	//
	//m_snow->EmissionType = PATICLE_EMISSION_TYPE::SPHERE_OUTLINE;
	//m_snow->SphereEmissionRange = 3.0f;
	//
	//
	//m_snowStrom->StartEmission();
	//m_snowStrom_under->StartEmission();
	//m_snow->StartEmission();
	//
	////m_isSnowStorm = true;
	//m_aniCount = 0;

}


void cSkill_Swing::Effect_Update(float timeDelta)
{

	//if (m_AttackingTime - 100 == m_AttackingCount)
	//{
	//	m_snowStrom->StopEmission();
	//	m_snowStrom_under->StopEmission();
	//	m_snow->StopEmission();
	//}
	//
	//
	//if (m_IsAttacking)
	//{
	//	m_aniCount++;
	//	m_snowStrom->pTransform->SetWorldPosition(pTransform->GetWorldPosition());
	//	m_snowStrom->pTransform->RotateSelf(D3DXVECTOR3(0, -10.0*timeDelta, 0));
	//	m_snowStrom->Update(timeDelta);
	//	m_snowStrom_under->pTransform->SetWorldPosition(pTransform->GetWorldPosition());
	//	m_snowStrom_under->pTransform->RotateSelf(D3DXVECTOR3(0, -5.0*timeDelta, 0));
	//	m_snowStrom_under->Update(timeDelta);
	//	m_snow->pTransform->SetWorldPosition(pTransform->GetWorldPosition() + D3DXVECTOR3(0, 7, 0));
	//	m_snow->Update(timeDelta);
	//}

}
void cSkill_Swing::Effect_Render()
{
	//if (m_IsAttacking)
	//{
	//	//m_DarkDorm->Render(m_snowStrom_under->pTransform);
	//	m_snowStrom_under->Render();
	//	m_snowStrom->Render();
	//	m_snow->Render();
	//
	//}
}