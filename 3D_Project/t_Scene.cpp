#include "StdAfx.h"
#include "t_Scene.h"
#include "cLight_Direction.h"
#include "cXMesh_Static.h"
#include "cBaseObject.h"
#include "cTransform.h"
#include "cCamera.h"
#include "cTerrain.h"
#include "cSkinnedAnimation.h"
#include "cLight_Point.h"

t_Scene::t_Scene(void)
{
}

t_Scene::~t_Scene(void)
{
}

HRESULT t_Scene::Scene_Init()
{


	//���� �ִ� �Ž����� ������ ���� ��ķ� �������� 
	//��� ������ Ʋ�������.
	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.007f, 0.007f, 0.007f);
	D3DXMATRIXA16 matCorrection = matScale;

	//���� �޽� �ε�
	cXMesh_Static* mesh =
		RESOURCE_STATICXMESH->GetResource(
		"../Resources/Meshes/Tree/PineTree_01.X", &matCorrection);

	this->object = new cBaseObject();
	this->object->SetActive(true);
	this->object->SetMesh(mesh);

	//�⺻����Ʈ ����
	this->pSceneBaseDirectionLight->pTransform->RotateWorld(
		90.0f * ONE_RAD, 0, 0);


	this->pMainCamera->SetWorldPosition(0, 5, -10);


	return S_OK;
}

void t_Scene::Scene_Release()
{
	//������Ʈ ����
	SAFE_DELETE(this->object);

}

void t_Scene::Scene_Update(float timeDelta)
{
	this->object->pTransform->RotateWorld(0, 90 * ONE_RAD * timeDelta, 0);
	this->object->Update(timeDelta);

}

void t_Scene::Scene_Render1()
{


	cXMesh_Static::SetCamera(this->pMainCamera);
	cXMesh_Static::SetTechniqueName("BaseTree");		//������� ���� �׸����� ReciveShadow �� Technique ����
	cXMesh_Static::SetBaseLight(this->pSceneBaseDirectionLight);;


	cXMesh_Skinned::SetCamera(this->pMainCamera);
	cXMesh_Skinned::SetTechniqueName("ReciveShadow");
	cXMesh_Skinned::sSkinnedMeshEffect->SetTexture("Ramp_Tex", RESOURCE_TEXTURE->GetResource("../Resources/Testures/Ramp_1.png"));
	cXMesh_Skinned::SetBaseLight(this->pSceneBaseDirectionLight);

	this->object->Render();




}


void t_Scene::Scene_RenderSprite()
{

	DXFONT_MGR->PrintText(SCENE_MGR->fString, 100, 100, 0xffffff00);
	char szTemp[128];
	sprintf(szTemp, "%.2f �ۼ�Ʈ �ε���", SCENE_MGR->fProgress);
	DXFONT_MGR->PrintText(szTemp, 100, 130, 0xffffff00);
}

