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
	//�ͷ��� ����
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
	//ĳ���� ����
	//
	m_pPlayer = new cPlayer;

	//ĳ���� ���� ��� ����
	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.1f);
	D3DXMATRIXA16 matRotate;
	D3DXMatrixRotationY(&matRotate, -90.0f * ONE_RAD);
	D3DXMATRIXA16 matCorrection = matScale * matRotate;

	//ĳ���Ϳ��� ���� ����
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

	//���̴��� ������ ����
	cXMesh_Static::SetCamera(this->pMainCamera);
	cXMesh_Static::SetTechniqueName("Base");		//������� ���� �׸����� ReciveShadow �� Technique ����
	cXMesh_Static::SetBaseLight(this->pSceneBaseDirectionLight);
}
