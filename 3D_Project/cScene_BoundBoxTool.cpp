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
	//������Ʈ ����
	//

	//�ǹ� ���� ��� ����
	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.01f, 0.01f, 0.01f);
	D3DXMATRIXA16 matRotate;
	D3DXMatrixRotationY(&matRotate, -90.0f * ONE_RAD);
	D3DXMATRIXA16 matCorrection = matScale * matRotate;

	selectObject = new cBaseObject;
	selectObject->SetActive(true);
	selectObject->SetMesh(RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Migdal/migdal_Wall.X", &matCorrection));
	
	RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Migdal_House/house_nobel.X", &matCorrection);



	//
	//���� ����
	//
	m_pMonster = new cMonster;

	//ĳ���� ���� ��� ����
	D3DXMATRIXA16 matScale2;
	D3DXMatrixScaling(&matScale2, 0.1f, 0.1f, 0.1f);
	matCorrection = matScale2 * matRotate;

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
	SAFE_DELETE(selectObject);


	vector<cBaseObject*>::iterator obj_iter;
	for (obj_iter = objects.begin(); obj_iter != objects.end();)
	{
		SAFE_DELETE(*obj_iter);
		obj_iter = objects.erase(obj_iter);
	}
	objects.clear();

	vector<cLight*>::iterator light_iter;
	for (light_iter = lights.begin(); light_iter != lights.end();)
	{
		SAFE_DELETE(*light_iter);
		light_iter = lights.erase(light_iter);
	}
	lights.clear();
}

void cScene_BoundBoxTool::Scene_Update(float timeDelta)
{
	m_pMonster->Update(timeDelta);

	KeyControl(timeDelta);	
}

void cScene_BoundBoxTool::Scene_Render1()
{
	m_pTerrain->Render(this->pMainCamera, dynamic_cast<cLight_Direction*>(lights[0]));

	//����Ǵ� LightMatrix
	D3DXMATRIXA16 matLights[10];
	for (int i = 0; i < this->lights.size(); i++)
		matLights[i] = this->lights[i]->GetLightMatrix();

	//���̴��� ������ ����
	cXMesh_Static::SetCamera(this->pMainCamera);
	cXMesh_Static::SetTechniqueName("Base");		//������� ���� �׸����� ReciveShadow �� Technique ����
	cXMesh_Static::SetBaseLight(dynamic_cast<cLight_Direction*>(lights[0]));

	int size = objects.size();
	for (int i = 0; i < size; ++i)
	{
		objects[i]->Render();
	}


	//���̴��� ������ ����
	cXMesh_Skinned::sSkinnedMeshEffect->SetMatrixArray("matLights", matLights, 10);
	cXMesh_Skinned::sSkinnedMeshEffect->SetInt("LightNum", this->lights.size());

	cXMesh_Skinned::SetCamera(this->pMainCamera);

	m_pMonster->Render();



	//�ٿ�带 �׸���.
	/*for (int i = 0; i < this->boundObjects.size(); i++)
		this->boundObjects[i]->Render();

	if (this->selectBound != NULL)
	{
		this->selectBound->pTransform->RenderGimozo();
	}*/
}

void cScene_BoundBoxTool::KeyControl(float timeDelta)
{
	//���̷��� ����Ʈ ����
	//lights[0]->pTransform->DefaultControl2(timeDelta);

	//��ġ�� ������Ʈ�� �����Ѵ�.
	if (KEY_MGR->IsOnceDown('1'))
	{
		selectObject->SetMesh(RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Migdal/migdal_Wall.X"));
	}
	if (KEY_MGR->IsOnceDown('2'))
	{
		selectObject->SetMesh(RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Migdal_House/house_nobel.X"));
	}


	//������ ������Ʈ ũ�� �� �̵� ����
	selectObject->pTransform->DefaultControl4(timeDelta);


	//��ŷ�ؼ� �� ��ġ�� ������Ʈ�� ����,
	//��ġ ��Ų ������Ʈ�� ���Ϳ� �߰��Ѵ�.
	if (KEY_MGR->IsOnceDown(VK_LBUTTON))
	{
		Ray ray;
		POINT ptMouse = GetMousePos();
		D3DXVECTOR2 screenPos(ptMouse.x, ptMouse.y);
		this->pMainCamera->ComputeRay(&ray, &screenPos);

		//������ �ͷ��� ��Ʈ ����Ʈ�� ��´�.
		D3DXVECTOR3 pos;
		m_pTerrain->IsIntersectRay(&pos, &ray);

		//������Ʈ�� ���Ϳ� �߰��Ѵ�.
		cBaseObject* obj = new cBaseObject;
		obj->SetMesh(selectObject->pMesh);
		obj->pTransform->SetWorldPosition(pos);
		obj->SetActive(true);
		objects.push_back(obj);

		selectObject = objects.back();

		//vector<cSetBoundObject*> hitBounds;
		//vector<float>	hitdistances;

		////���� �ִ� ��� ����üũ
		//for (int i = 0; i < this->boundObjects.size(); i++)
		//{
		//	D3DXVECTOR3 hitPos;
		//	if (PHYSICS_MGR->IsRayHitBound(
		//		&ray,
		//		&this->boundObjects[i]->BoundBox,
		//		this->boundObjects[i]->pTransform,
		//		&hitPos,
		//		NULL)) {

		//		//�浹�� ���̶��...
		//		hitBounds.push_back(this->boundObjects[i]);

		//		//ī�޶�κ����� �Ÿ� ������ Ǫ��
		//		hitdistances.push_back(D3DXVec3LengthSq(
		//			&(hitPos - this->pMainCamera->GetWorldPosition())));

		//	}
		//}


		////��Ʈ �� ���� �ִٸ�...
		//if (hitBounds.size() > 0)
		//{
		//	//�ϴ� ù��° 
		//	cSetBoundObject* pTarget = hitBounds[0];
		//	float nearest = hitdistances[0];

		//	for (int i = 1; i < hitBounds.size(); i++)
		//	{
		//		//����
		//		if (nearest > hitdistances[i])
		//		{
		//			nearest = hitdistances[i];
		//			pTarget = hitBounds[i];
		//		}

		//	}

		//	this->selectBound = pTarget;
		//}
	}
}
