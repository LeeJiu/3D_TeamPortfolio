#include "stdafx.h"
#include "cScene_BoundBoxTool.h"
#include "cTerrain.h"
#include "cMonster.h"
#include "cLight_Direction.h"
#include "cLight_Point.h"
#include "cCamera.h"


cScene_BoundBoxTool::cScene_BoundBoxTool()
{
}


cScene_BoundBoxTool::~cScene_BoundBoxTool()
{
}

HRESULT cScene_BoundBoxTool::Scene_Init()
{
	//
	//�ͷ��� ����
	//
	m_pTerrain = new cTerrain;
	m_pTerrain->Init(
		"../Resources/Textures/MyHeight256.bmp",
		"../Resources/Textures/terrain1.png",
		"../Resources/Textures/terrain2.png",
		"../Resources/Textures/terrain3.png",
		"../Resources/Textures/terrain4.png",
		"../Resources/Textures/Splat2.png",
		1.0f,
		100.0f,
		3,
		100);


	//
	//���� ����
	//
	m_pMonster = new cMonster;

	//ĳ���� ���� ��� ����
	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.1f);
	D3DXMATRIXA16 matRotate;
	D3DXMatrixRotationY(&matRotate, -90.0f * ONE_RAD);
	D3DXMATRIXA16 matCorrection = matScale * matRotate;

	//ĳ���Ϳ��� ���� ����
	m_pMonster->SetTerrain(m_pTerrain);

	m_pMonster->SetMesh(RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Monster/Surcubus/surcubus.X", &matCorrection));
	m_pMonster->SetActive(true);


	//
	//����Ʈ ����
	//

	//����Ʈ Ǫ��
	cLight_Direction* pLight1 = new cLight_Direction();
	pLight1->Color = D3DXCOLOR(1, 1, 1, 1);
	pLight1->Intensity = 1.0f;
	pLight1->pTransform->SetRotateWorld(90 * ONE_RAD, 0, 0);

	/*testLight = new cLight_Direction();
	testLight->Color = D3DXCOLOR(1, 1, 1, 1);
	testLight->Intensity = 1.0f;
	testLight->pTransform->SetRotateWorld(90 * ONE_RAD, 0, 0);*/

	/*cLight_Point* pLight2 = new cLight_Point();
	pLight2->Color = D3DXCOLOR(1, 1, 1, 0);
	pLight2->minRange = 5.0f;
	pLight2->maxRange = 10.0f;
	pLight2->distancePow = 10.0f;

	cLight_Point* pLight3 = new cLight_Point();
	pLight3->Color = D3DXCOLOR(1, 1, 1, 0);
	pLight3->minRange = 5.0f;
	pLight3->maxRange = 10.0f;
	pLight3->distancePow = 10.0f;
	pLight3->pTransform->SetWorldPosition(3, 3, 0);
	pLight3->Intensity = 0.5f;*/

	this->lights.push_back(pLight1);
	/*this->lights.push_back(pLight2);
	this->lights.push_back(pLight3);*/


	return S_OK;
}

void cScene_BoundBoxTool::Scene_Release()
{
	m_pTerrain->Release();
	SAFE_DELETE(m_pTerrain);

	SAFE_DELETE(m_pMonster);
}

void cScene_BoundBoxTool::Scene_Update(float timeDelta)
{
	m_pMonster->Update(timeDelta);
}

void cScene_BoundBoxTool::Scene_Render1()
{
	m_pTerrain->Render(this->pMainCamera, dynamic_cast<cLight_Direction*>(lights[0]));

	//����Ǵ� LightMatrix
	D3DXMATRIXA16 matLights[10];
	for (int i = 0; i < this->lights.size(); i++)
		matLights[i] = this->lights[i]->GetLightMatrix();

	//���̴��� ������ ����
	cXMesh_Skinned::sSkinnedMeshEffect->SetMatrixArray("matLights", matLights, 10);
	cXMesh_Skinned::sSkinnedMeshEffect->SetInt("LightNum", this->lights.size());

	cXMesh_Skinned::SetCamera(this->pMainCamera);

	m_pMonster->Render();

	//���̴��� ������ ����
	cXMesh_Static::SetCamera(this->pMainCamera);
	cXMesh_Static::SetTechniqueName("Base");		//������� ���� �׸����� ReciveShadow �� Technique ����
	cXMesh_Static::SetBaseLight(this->pSceneBaseDirectionLight);




	//�ٿ�带 �׸���.
	/*for (int i = 0; i < this->boundObjects.size(); i++)
		this->boundObjects[i]->Render();

	if (this->selectBound != NULL)
	{
		this->selectBound->pTransform->RenderGimozo();
	}*/
}
