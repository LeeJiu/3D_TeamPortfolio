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
	//터레인 세팅
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
	//오브젝트 세팅
	//

	//건물 보정 행렬 세팅
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
	//몬스터 세팅
	//
	m_pMonster = new cMonster;

	//캐릭터 보정 행렬 세팅
	D3DXMATRIXA16 matScale2;
	D3DXMatrixScaling(&matScale2, 0.1f, 0.1f, 0.1f);
	matCorrection = matScale2 * matRotate;

	//캐릭터에게 지형 전달
	m_pMonster->SetTerrain(m_pTerrain);
	m_pMonster->SetMesh(RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Monster/Surcubus/surcubus.X", &matCorrection));
	m_pMonster->SetActive(true);


	//
	//라이트 세팅
	//

	//라이트 푸쉬
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

	//적용되는 LightMatrix
	D3DXMATRIXA16 matLights[10];
	for (int i = 0; i < this->lights.size(); i++)
		matLights[i] = this->lights[i]->GetLightMatrix();

	//셰이더에 라이팅 셋팅
	cXMesh_Static::SetCamera(this->pMainCamera);
	cXMesh_Static::SetTechniqueName("Base");		//쉐도우랑 같이 그릴려면 ReciveShadow 로 Technique 셋팅
	cXMesh_Static::SetBaseLight(dynamic_cast<cLight_Direction*>(lights[0]));

	int size = objects.size();
	for (int i = 0; i < size; ++i)
	{
		objects[i]->Render();
	}


	//셰이더에 라이팅 셋팅
	cXMesh_Skinned::sSkinnedMeshEffect->SetMatrixArray("matLights", matLights, 10);
	cXMesh_Skinned::sSkinnedMeshEffect->SetInt("LightNum", this->lights.size());

	cXMesh_Skinned::SetCamera(this->pMainCamera);

	m_pMonster->Render();



	//바운드를 그린다.
	/*for (int i = 0; i < this->boundObjects.size(); i++)
		this->boundObjects[i]->Render();

	if (this->selectBound != NULL)
	{
		this->selectBound->pTransform->RenderGimozo();
	}*/
}

void cScene_BoundBoxTool::KeyControl(float timeDelta)
{
	//다이렉션 라이트 조종
	//lights[0]->pTransform->DefaultControl2(timeDelta);

	//설치할 오브젝트를 변경한다.
	if (KEY_MGR->IsOnceDown('1'))
	{
		selectObject->SetMesh(RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Migdal/migdal_Wall.X"));
	}
	if (KEY_MGR->IsOnceDown('2'))
	{
		selectObject->SetMesh(RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Migdal_House/house_nobel.X"));
	}


	//선택한 오브젝트 크기 및 이동 설정
	selectObject->pTransform->DefaultControl4(timeDelta);


	//피킹해서 그 위치에 오브젝트를 놓고,
	//위치 시킨 오브젝트를 벡터에 추가한다.
	if (KEY_MGR->IsOnceDown(VK_LBUTTON))
	{
		Ray ray;
		POINT ptMouse = GetMousePos();
		D3DXVECTOR2 screenPos(ptMouse.x, ptMouse.y);
		this->pMainCamera->ComputeRay(&ray, &screenPos);

		//레이의 터레인 히트 포인트를 얻는다.
		D3DXVECTOR3 pos;
		m_pTerrain->IsIntersectRay(&pos, &ray);

		//오브젝트를 벡터에 추가한다.
		cBaseObject* obj = new cBaseObject;
		obj->SetMesh(selectObject->pMesh);
		obj->pTransform->SetWorldPosition(pos);
		obj->SetActive(true);
		objects.push_back(obj);

		selectObject = objects.back();

		//vector<cSetBoundObject*> hitBounds;
		//vector<float>	hitdistances;

		////현제 있는 놈들 레이체크
		//for (int i = 0; i < this->boundObjects.size(); i++)
		//{
		//	D3DXVECTOR3 hitPos;
		//	if (PHYSICS_MGR->IsRayHitBound(
		//		&ray,
		//		&this->boundObjects[i]->BoundBox,
		//		this->boundObjects[i]->pTransform,
		//		&hitPos,
		//		NULL)) {

		//		//충돌된 놈이라면...
		//		hitBounds.push_back(this->boundObjects[i]);

		//		//카메라로부터의 거리 제곱도 푸쉬
		//		hitdistances.push_back(D3DXVec3LengthSq(
		//			&(hitPos - this->pMainCamera->GetWorldPosition())));

		//	}
		//}


		////히트 된 놈이 있다면...
		//if (hitBounds.size() > 0)
		//{
		//	//일단 첫번째 
		//	cSetBoundObject* pTarget = hitBounds[0];
		//	float nearest = hitdistances[0];

		//	for (int i = 1; i < hitBounds.size(); i++)
		//	{
		//		//갱신
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
