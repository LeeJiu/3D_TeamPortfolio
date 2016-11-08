#include "stdafx.h"
#include "cScene_testPlayer.h"
#include "cLight_Direction.h"
#include "cTransform.h"


cScene_testPlayer::cScene_testPlayer()
{
}


cScene_testPlayer::~cScene_testPlayer()
{
}

HRESULT cScene_testPlayer::Scene_Init()
{
	//
	//터레인 세팅
	//
	m_pTerrain = new cTerrain;
	m_pTerrain->Init(
		"../Resources/Textures/MyHeight512.bmp",
		"../Resources/Textures/terrain1.jpg",
		"../Resources/Textures/terrain2.png",
		"../Resources/Textures/terrain3.png",
		"../Resources/Textures/terrain4.png",
		"../Resources/Textures/Splat.png",
		1.0f,
		100.0f,
		3,
		100);


	//
	//캐릭터 세팅
	//
	m_pPlayer = new cPlayer;

	//캐릭터 보정 행렬 세팅
	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.1f);
	D3DXMATRIXA16 matRotate;
	D3DXMatrixRotationY(&matRotate, -90.0f * ONE_RAD);
	D3DXMATRIXA16 matCorrection = matScale * matRotate;

	//캐릭터에게 지형 전달
	m_pPlayer->SetTerrain(m_pTerrain);
	
	m_pPlayer->SetMesh(RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Queen/Queen.X", &matCorrection));
	m_pPlayer->SetActive(true);
	

	return S_OK;
}

void cScene_testPlayer::Scene_Release()
{
	m_pTerrain->Release();
	SAFE_DELETE(m_pTerrain);

	SAFE_DELETE(m_pPlayer);
}

void cScene_testPlayer::Scene_Update(float timeDelta)
{
	m_pPlayer->Update(timeDelta);
}

void cScene_testPlayer::Scene_Render1()
{
	m_pTerrain->Render(this->pMainCamera, pSceneBaseDirectionLight);

	cXMesh_Skinned::SetCamera(this->pMainCamera);
	cXMesh_Skinned::SetBaseLight(pSceneBaseDirectionLight);


	m_pPlayer->Render();

	//셰이더에 라이팅 셋팅
	cXMesh_Static::SetCamera(this->pMainCamera);
	cXMesh_Static::SetTechniqueName("Base");		//쉐도우랑 같이 그릴려면 ReciveShadow 로 Technique 셋팅
	cXMesh_Static::SetBaseLight(this->pSceneBaseDirectionLight);
}
