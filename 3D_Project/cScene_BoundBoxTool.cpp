#include "stdafx.h"
#include "cScene_BoundBoxTool.h"
#include "cSetBoundObject.h"
#include "cTerrain.h"
#include "cMonster.h"
#include "cLight_Direction.h"
#include "cLight_Point.h"
#include "cCamera.h"


cScene_BoundBoxTool::cScene_BoundBoxTool()
{
	m_pSelectBound = NULL;
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
	D3DXMatrixScaling(&matScale, 0.02f, 0.02f, 0.02f);
	D3DXMATRIXA16 matRotate;
	D3DXMatrixRotationY(&matRotate, -90.0f * ONE_RAD);
	D3DXMATRIXA16 matCorrection = matScale * matRotate;

	m_pSelectObject = new cBaseObject;
	m_pSelectObject->SetActive(true);
	m_pSelectObject->SetMesh(RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Migdal/migdal_Wall.X", &matCorrection));
	m_pSelectObject->objType = MIGDAL_WALL;

	RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Migdal_House/house_nobel.X", &matCorrection);
	RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Tree/tree_01.X", &matCorrection);
	RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Tree/tree_02.X", &matCorrection);
	RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Tree/tree_03.X", &matCorrection);
	RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Tree/tree_04.X", &matCorrection);
	RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Tree/tree_05.X", &matCorrection);
	RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Tree/tree_desert_01.X", &matCorrection);
	RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Tree/tree_desert_02.X", &matCorrection);
	RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Tree/tree_desert_03.X", &matCorrection);
	RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Tree/tree_desert_04.X", &matCorrection);
	RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Tree/tree_desert_05.X", &matCorrection);


	//
	//몬스터 세팅
	//
	//캐릭터 보정 행렬 세팅
	D3DXMatrixScaling(&matScale, 0.05f, 0.05f, 0.05f);
	matCorrection = matScale * matRotate;

	m_pSelectMonster = new cBaseObject;
	m_pSelectMonster->SetActive(true);
	m_pSelectMonster->SetMesh(RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Monster/Bashil/MOB_Bashil.X", &matCorrection));
	m_pSelectMonster->monType = BASILISK;	

	RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Monster/Griff/MOB_HipGriff.X", &matCorrection);
	RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Monster/Minho/MOB_Minho.X", &matCorrection);
	RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Monster/SpiderQueen/MOB_Spider.X", &matCorrection);
	RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Monster/SpiderQueen/MOB_SpiderQueen.X", &matCorrection);
	RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Monster/Surcubus/surcubus.X", &matCorrection);
	RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Boss/SkulDragon/skulDragon_1.X", &matCorrection);



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


	m_bSelectObj = false;
	m_bSwapSelection = false;	//오브젝트로 선택
	m_bSetBoundBox = false;		//바운드 박스 설치하려면 true로

	return S_OK;
}

void cScene_BoundBoxTool::Scene_Release()
{
	m_pTerrain->Release();
	SAFE_DELETE(m_pTerrain);
	SAFE_DELETE(m_pSelectObject);


	for (m_viObjects = m_vObjects.begin(); m_viObjects != m_vObjects.end();)
	{
		SAFE_DELETE(*m_viObjects);
		m_viObjects = m_vObjects.erase(m_viObjects);
	}
	m_vObjects.clear();

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
	//다이렉션 라이트 조종
	//lights[0]->pTransform->DefaultControl2(timeDelta);

	//카메라 조종
	pMainCamera->DefaultControl(timeDelta);
	
	//바운드박스 설치 / 오브젝트|몬스터 설치
	if (KEY_MGR->IsOnceDown('B'))
	{
		m_bSetBoundBox = !m_bSetBoundBox;
		if (m_bSetBoundBox)
		{
			LOG_MGR->AddLog("[바운드박스]");
		}
		else
		{
			LOG_MGR->AddLog("[오브젝트|몬스터]");
		}
	}

	//세이브 & 로드
	if (KEY_MGR->IsStayDown(VK_LCONTROL) && KEY_MGR->IsOnceDown('S'))
	{
		SaveObjects();
		SaveMonsters();
		SaveBoundBox();
	}

	if (KEY_MGR->IsStayDown(VK_LCONTROL) && KEY_MGR->IsOnceDown('L'))
	{
		LoadObjects();
		LoadMonsters();
		LoadBoundBox();
	}


	if (m_bSetBoundBox == false)
	{
		KeyControl(timeDelta);
	}
	else
	{
		KeyControl2(timeDelta);
	}
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

	int size = m_vObjects.size();
	for (int i = 0; i < size; ++i)
	{
		m_vObjects[i]->Render();
	}

	size = m_vMonsters.size();
	for (int i = 0; i < size; ++i)
	{
		m_vMonsters[i]->Render();
	}

	//바운드를 그린다.
	size = m_vBoundBoxes.size();
	for (int i = 0; i < size; i++)
	{
		this->m_vBoundBoxes[i]->Render();
	}

	if (this->m_pSelectBound != NULL)
	{
		this->m_pSelectBound->pTransform->RenderGimozo();
	}
}

void cScene_BoundBoxTool::KeyControl(float timeDelta)
{
	//오브젝트 / 몬스터 전환
	if (KEY_MGR->IsOnceDown(VK_SPACE))
	{
		m_bSwapSelection = !m_bSwapSelection;
		if (m_bSwapSelection)
		{
			LOG_MGR->AddLog("[몬스터]");
			m_pMesh = m_pSelectMonster->pMesh;
		}
		else
		{
			LOG_MGR->AddLog("[오브젝트]");
			m_pMesh = m_pSelectObject->pMesh;
		}
	}

	//몬스터 설치할 때
	if (m_bSwapSelection)
	{
		ControlMonsters(timeDelta);
	}
	//오브젝트 설치할 때
	else
	{
		ControlObjects(timeDelta);
	}	
}

void cScene_BoundBoxTool::KeyControl2(float timeDelta)
{
	//바운드 박스 추가
	if (KEY_MGR->IsOnceDown(VK_ADD))
	{
		//현재 마우스 위치에 바운드 박스를 생성
		Ray ray;
		POINT ptMouse = GetMousePos();
		D3DXVECTOR2 screenPos(ptMouse.x, ptMouse.y);
		this->pMainCamera->ComputeRay(&ray, &screenPos);

		//레이의 터레인 히트 포인트를 얻는다.
		D3DXVECTOR3 pos;
		m_pTerrain->IsIntersectRay(&pos, &ray);

		cSetBoundObject* pNewBound = new cSetBoundObject();
		pNewBound->pTransform->SetWorldPosition(pos);
		pNewBound->SetActive(true);
		this->m_vBoundBoxes.push_back(pNewBound);

		this->m_pSelectBound = pNewBound;
	}

	ControlBoxes(timeDelta);
}

void cScene_BoundBoxTool::ControlObjects(float timeDelta)
{
	//설치할 오브젝트를 변경한다.
	if (KEY_MGR->IsOnceDown('1'))
	{
		m_pSelectObject->objType = MIGDAL_WALL;
		SelectObjMesh(m_pSelectObject->objType);
		m_pSelectObject->SetMesh(m_pMesh);
	}
	if (KEY_MGR->IsOnceDown('2'))
	{
		m_pSelectObject->objType = MIGDAL_HOUSE;
		SelectObjMesh(m_pSelectObject->objType);
		m_pSelectObject->SetMesh(m_pMesh);
	}
	if (KEY_MGR->IsOnceDown('3'))
	{
		int typeNum = (int)(m_pSelectObject->objType);
		if (typeNum < TREE01)
		{
			m_pSelectObject->objType = TREE01;
			SelectObjMesh(m_pSelectObject->objType);
		}
		else
		{
			typeNum++;
			if (typeNum > TREE05_D)
			{
				m_pSelectObject->objType = TREE01;
			}
			else
			{
				m_pSelectObject->objType = (OBJECT_TYPE)typeNum;
			}
			SelectObjMesh(m_pSelectObject->objType);
		}
		m_pSelectObject->SetMesh(m_pMesh);
	}

	//오브젝트 선택 / 세팅 전환
	if (KEY_MGR->IsOnceDown(VK_RETURN))
	{
		m_bSelectObj = !m_bSelectObj;
		if (m_bSelectObj)
			LOG_MGR->AddLog("오브젝트 선택");
		else
			LOG_MGR->AddLog("오브젝트 세팅");
	}


	if (m_bSelectObj == true)
	{
		//오브젝트 선택
		if (KEY_MGR->IsStayDown(VK_LCONTROL) == true && KEY_MGR->IsOnceDown(VK_LBUTTON))
			SelectObject();

		//선택된 오브젝트 드래그
		if (KEY_MGR->IsStayDown(VK_LCONTROL) == false && KEY_MGR->IsStayDown(VK_LBUTTON))
		{
			Ray ray;
			POINT ptMouse = GetMousePos();
			D3DXVECTOR2 screenPos(ptMouse.x, ptMouse.y);
			this->pMainCamera->ComputeRay(&ray, &screenPos);

			//레이의 터레인 히트 포인트를 얻는다.
			D3DXVECTOR3 pos;
			m_pTerrain->IsIntersectRay(&pos, &ray);

			m_pSelectObject->pTransform->SetWorldPosition(pos);
		}

		//선택된 오브젝트 삭제
		if (KEY_MGR->IsOnceDown(VK_DELETE))
		{
			DeleteObject();
		}
	}
	else
	{
		//오브젝트 세팅
		if (KEY_MGR->IsOnceDown(VK_LBUTTON))
		{
			SetObjects();
		}
	}

	if (m_vObjects.empty())
	{
		m_pSelectObject = new cBaseObject;
		m_pSelectObject->SetActive(true);
		m_pSelectObject->SetMesh(RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Migdal/migdal_Wall.X"));
		m_pSelectObject->objType = MIGDAL_WALL;
	}
	else
	{
		//선택한 오브젝트 크기 및 이동 설정
		m_pSelectObject->pTransform->DefaultControl4(timeDelta);
	}
}

void cScene_BoundBoxTool::ControlMonsters(float timeDelta)
{
	//위치할 몬스터를 변경한다.
	if (KEY_MGR->IsOnceDown('1'))
	{
		int typeNum = (int)(m_pSelectMonster->monType);
		typeNum--;
		if (typeNum < BASILISK)
		{
			m_pSelectMonster->monType = BASILISK;
		}
		else
		{
			m_pSelectMonster->monType = (MONSTER_TYPE)typeNum;
		}
		SelectMonMesh(m_pSelectMonster->monType);
		m_pSelectMonster->SetMesh(m_pMesh);
	}
	else if (KEY_MGR->IsOnceDown('2'))
	{
		int typeNum = (int)(m_pSelectMonster->monType);
		typeNum++;
		if (typeNum > DRAGON)
		{
			m_pSelectMonster->monType = DRAGON;
		}
		else
		{
			m_pSelectMonster->monType = (MONSTER_TYPE)typeNum;
		}
		SelectMonMesh(m_pSelectMonster->monType);
		m_pSelectMonster->SetMesh(m_pMesh);
	}

	//몬스터 선택 / 세팅 전환
	if (KEY_MGR->IsOnceDown(VK_RETURN))
	{
		m_bSelectObj = !m_bSelectObj;
		if (m_bSelectObj)
			LOG_MGR->AddLog("몬스터 선택");
		else
			LOG_MGR->AddLog("몬스터 세팅");
	}


	if (m_bSelectObj == true)
	{
		//몬스터 선택
		if (KEY_MGR->IsStayDown(VK_LCONTROL) == true && KEY_MGR->IsOnceDown(VK_LBUTTON))
			SelectMonster();

		//선택된 몬스터 드래그
		if (KEY_MGR->IsStayDown(VK_LCONTROL) == false && KEY_MGR->IsStayDown(VK_LBUTTON))
		{
			Ray ray;
			POINT ptMouse = GetMousePos();
			D3DXVECTOR2 screenPos(ptMouse.x, ptMouse.y);
			this->pMainCamera->ComputeRay(&ray, &screenPos);

			//레이의 터레인 히트 포인트를 얻는다.
			D3DXVECTOR3 pos;
			m_pTerrain->IsIntersectRay(&pos, &ray);

			m_pSelectMonster->pTransform->SetWorldPosition(pos);
		}

		//선택된 몬스터 삭제
		if (KEY_MGR->IsOnceDown(VK_DELETE))
		{
			DeleteMonster();
		}
	}
	else
	{
		//몬스터 세팅
		if (KEY_MGR->IsOnceDown(VK_LBUTTON))
		{
			SetMonsters();
		}
	}

	if (m_vMonsters.empty())
	{
		m_pSelectMonster = new cBaseObject;
		m_pSelectMonster->SetActive(true);
		m_pSelectMonster->SetMesh(RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Monster/Bashil/MOB_Bashil.X"));
		m_pSelectMonster->monType = BASILISK;
	}
}

void cScene_BoundBoxTool::ControlBoxes(float timeDelta)
{
	//바운드박스 선택
	if (KEY_MGR->IsStayDown(VK_LCONTROL) == true && KEY_MGR->IsOnceDown(VK_LBUTTON))
		SelectBoundBox();

	//선택된 바운드박스 드래그
	if (KEY_MGR->IsStayDown(VK_LCONTROL) == false && KEY_MGR->IsStayDown(VK_LBUTTON))
	{
		if (m_pSelectBound == NULL) return;

		Ray ray;
		POINT ptMouse = GetMousePos();
		D3DXVECTOR2 screenPos(ptMouse.x, ptMouse.y);
		this->pMainCamera->ComputeRay(&ray, &screenPos);

		//레이의 터레인 히트 포인트를 얻는다.
		D3DXVECTOR3 pos;
		m_pTerrain->IsIntersectRay(&pos, &ray);

		m_pSelectBound->pTransform->SetWorldPosition(pos);
	}

	//선택된 바운드박스 삭제
	if (KEY_MGR->IsOnceDown(VK_DELETE))
	{
		DeleteBoundBox();
	}

	if (m_pSelectBound != NULL)
	{
		m_pSelectBound->Update(timeDelta);
	}
}

void cScene_BoundBoxTool::SetObjects()
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
	obj->SetMesh(m_pSelectObject->pMesh);
	obj->objType = m_pSelectObject->objType;
	obj->pTransform->SetWorldPosition(pos);
	obj->SetActive(true);
	m_vObjects.push_back(obj);

	//마지막에 넣은 오브젝트를 선택된 오브젝트로
	m_pSelectObject = m_vObjects.back();
}

void cScene_BoundBoxTool::SelectObject()
{
	Ray ray;
	POINT ptMouse = GetMousePos();
	D3DXVECTOR2 screenPos(ptMouse.x, ptMouse.y);
	this->pMainCamera->ComputeRay(&ray, &screenPos);

	vector<cBaseObject*> hitObjects;
	vector<float>	hitDistances;

	//현재 있는 놈들 레이체크
	int size = m_vObjects.size();
	for (int i = 0; i < size; ++i)
	{
		D3DXVECTOR3 hitPos;
		if (PHYSICS_MGR->IsRayHitBound(
			&ray,
			&this->m_vObjects[i]->BoundBox,
			this->m_vObjects[i]->pTransform,
			&hitPos,
			NULL))
		{
			//충돌된 놈이라면...
			hitObjects.push_back(this->m_vObjects[i]);

			//카메라로부터의 거리 제곱도 푸쉬
			hitDistances.push_back(D3DXVec3LengthSq(
				&(hitPos - this->pMainCamera->GetWorldPosition())));
		}
	}


	//히트 된 놈이 있다면...
	if (hitObjects.size() > 0)
	{
		//일단 첫번째 
		cBaseObject* pTarget = hitObjects[0];
		float nearest = hitDistances[0];

		for (int i = 1; i < hitObjects.size(); i++)
		{
			//갱신
			if (nearest > hitDistances[i])
			{
				nearest = hitDistances[i];
				pTarget = hitObjects[i];
			}
		}

		//선택된 오브젝트
		m_pSelectObject = pTarget;
	}
}

void cScene_BoundBoxTool::DeleteObject()
{
	if (m_pSelectObject != NULL)
	{
		//벡터에서 날리고
		for (m_viObjects = m_vObjects.begin(); m_viObjects != m_vObjects.end(); ++m_viObjects)
		{
			if (*m_viObjects == m_pSelectObject)
			{
				m_vObjects.erase(m_viObjects);
				if (m_vObjects.empty())
				{
					SAFE_DELETE(m_pSelectObject);
				}
				else
				{
					m_pSelectObject = m_vObjects.back();	//가장 마지막에 들어간 오브젝트를 선택
				}
				break;
			}
		}
	}
}

void cScene_BoundBoxTool::SetMonsters()
{
	Ray ray;
	POINT ptMouse = GetMousePos();
	D3DXVECTOR2 screenPos(ptMouse.x, ptMouse.y);
	this->pMainCamera->ComputeRay(&ray, &screenPos);

	//레이의 터레인 히트 포인트를 얻는다.
	D3DXVECTOR3 pos;
	m_pTerrain->IsIntersectRay(&pos, &ray);

	//몬스터를 벡터에 추가한다.
	cBaseObject* mon = new cBaseObject;
	mon->SetMesh(m_pSelectMonster->pMesh);
	mon->monType = m_pSelectMonster->monType;
	mon->pTransform->SetWorldPosition(pos);
	mon->SetActive(true);
	m_vMonsters.push_back(mon);

	//마지막에 넣은 몬스터를 선택된 몬스터로
	m_pSelectMonster = m_vMonsters.back();
}

void cScene_BoundBoxTool::SelectMonster()
{
	Ray ray;
	POINT ptMouse = GetMousePos();
	D3DXVECTOR2 screenPos(ptMouse.x, ptMouse.y);
	this->pMainCamera->ComputeRay(&ray, &screenPos);

	vector<cBaseObject*> hitMonsters;
	vector<float>	hitDistances;

	//현재 있는 놈들 레이체크
	int size = m_vMonsters.size();
	for (int i = 0; i < size; ++i)
	{
		D3DXVECTOR3 hitPos;
		if (PHYSICS_MGR->IsRayHitBound(
			&ray,
			&this->m_vMonsters[i]->BoundBox,
			this->m_vMonsters[i]->pTransform,
			&hitPos,
			NULL))
		{
			//충돌된 놈이라면...
			hitMonsters.push_back(this->m_vMonsters[i]);

			//카메라로부터의 거리 제곱도 푸쉬
			hitDistances.push_back(D3DXVec3LengthSq(
				&(hitPos - this->pMainCamera->GetWorldPosition())));
		}
	}


	//히트 된 놈이 있다면...
	if (hitMonsters.size() > 0)
	{
		//일단 첫번째 
		cBaseObject* pTarget = hitMonsters[0];
		float nearest = hitDistances[0];

		for (int i = 1; i < hitMonsters.size(); i++)
		{
			//갱신
			if (nearest > hitDistances[i])
			{
				nearest = hitDistances[i];
				pTarget = hitMonsters[i];
			}
		}

		//선택된 오브젝트
		m_pSelectMonster = pTarget;
	}
}

void cScene_BoundBoxTool::DeleteMonster()
{
	if (m_pSelectMonster != NULL)
	{
		//벡터에서 날리고
		for (m_viMonsters = m_vMonsters.begin(); m_viMonsters != m_vMonsters.end(); ++m_viMonsters)
		{
			if (*m_viMonsters == m_pSelectMonster)
			{
				m_vMonsters.erase(m_viMonsters);
				if (m_vMonsters.empty())
				{
					SAFE_DELETE(m_pSelectMonster);
				}
				else
				{
					m_pSelectMonster = m_vMonsters.back();	//가장 마지막에 들어간 몬스터를 선택
				}
				break;
			}
		}
	}
}

void cScene_BoundBoxTool::SelectBoundBox()
{
	Ray ray;
	POINT ptMouse = GetMousePos();
	D3DXVECTOR2 screenPos(ptMouse.x, ptMouse.y);
	this->pMainCamera->ComputeRay(&ray, &screenPos);

	vector<cSetBoundObject*> hitObjects;
	vector<float>	hitDistances;

	//현재 있는 놈들 레이체크
	int size = m_vBoundBoxes.size();
	for (int i = 0; i < size; ++i)
	{
		D3DXVECTOR3 hitPos;
		if (PHYSICS_MGR->IsRayHitBound(
			&ray,
			&this->m_vBoundBoxes[i]->BoundBox,
			this->m_vBoundBoxes[i]->pTransform,
			&hitPos,
			NULL))
		{
			//충돌된 놈이라면...
			hitObjects.push_back(this->m_vBoundBoxes[i]);

			//카메라로부터의 거리 제곱도 푸쉬
			hitDistances.push_back(D3DXVec3LengthSq(
				&(hitPos - this->pMainCamera->GetWorldPosition())));
		}
	}


	//히트 된 놈이 있다면...
	if (hitObjects.size() > 0)
	{
		//일단 첫번째 
		cSetBoundObject* pTarget = hitObjects[0];
		float nearest = hitDistances[0];

		for (int i = 1; i < hitObjects.size(); i++)
		{
			//갱신
			if (nearest > hitDistances[i])
			{
				nearest = hitDistances[i];
				pTarget = hitObjects[i];
			}
		}

		//선택된 오브젝트
		m_pSelectBound = pTarget;
	}
}

void cScene_BoundBoxTool::DeleteBoundBox()
{
	if (m_pSelectBound != NULL)
	{
		//벡터에서 날리고
		for (m_viBoundBoxes= m_vBoundBoxes.begin(); m_viBoundBoxes != m_vBoundBoxes.end(); ++m_viBoundBoxes)
		{
			if (*m_viBoundBoxes == m_pSelectBound)
			{
				m_vBoundBoxes.erase(m_viBoundBoxes);
				if (m_vObjects.empty())
				{
					SAFE_DELETE(m_pSelectBound);
				}
				else
				{
					m_pSelectBound = m_vBoundBoxes.back();	//가장 마지막에 들어간 오브젝트를 선택
				}
				break;
			}
		}
	}
}

void cScene_BoundBoxTool::SelectObjMesh(OBJECT_TYPE type)
{
	switch (type)
	{
	case MIGDAL_WALL:
		m_pMesh = RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Migdal/migdal_Wall.X");
		break;
	case MIGDAL_HOUSE:
		m_pMesh = RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Migdal_House/house_nobel.X");
		break;
	case TREE01:
		m_pMesh = RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Tree/tree_01.X");
		break;
	case TREE02:
		m_pMesh = RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Tree/tree_02.X");
		break;
	case TREE03:
		m_pMesh = RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Tree/tree_03.X");
		break;
	case TREE04:
		m_pMesh = RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Tree/tree_04.X");
		break;
	case TREE05:
		m_pMesh = RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Tree/tree_05.X");
		break;
	case TREE01_D:
		m_pMesh = RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Tree/tree_desert_01.X");
		break;
	case TREE02_D:
		m_pMesh = RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Tree/tree_desert_02.X");
		break;
	case TREE03_D:
		m_pMesh = RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Tree/tree_desert_03.X");
		break;
	case TREE04_D:
		m_pMesh = RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Tree/tree_desert_04.X");
		break;
	case TREE05_D:
		m_pMesh = RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Tree/tree_desert_05.X");
		break;
	default:
		break;
	}
}

void cScene_BoundBoxTool::SelectMonMesh(MONSTER_TYPE type)
{
	switch (type)
	{
	case BASILISK:
		m_pMesh = RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Monster/Bashil/MOB_Bashil.X");
		break;
	case GRIFF:
		m_pMesh = RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Monster/Griff/MOB_HipGriff.X");
		break;
	case MINO:
		m_pMesh = RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Monster/Minho/MOB_Minho.X");
		break;
	case SPIDER:
		m_pMesh = RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Monster/SpiderQueen/MOB_Spider.X");
		break;
	case SPIDER_QUEEN:
		m_pMesh = RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Monster/SpiderQueen/MOB_SpiderQueen.X");
		break;
	case SUCCUBUS:
		m_pMesh = RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Monster/Surcubus/surcubus.X");
		break;
	case DRAGON:
		m_pMesh = RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Boss/SkulDragon/skulDragon_1.X");
		break;
	default:
		break;
	}
}

void cScene_BoundBoxTool::SaveObjects()
{
	fstream file;
	file.open("ObjectData.txt", fstream::out); //fstream::out 파일 쓰기 모드

	int size = m_vObjects.size();
	for (int i = 0; i < m_vObjects.size(); i++)
	{
		cBaseObject* pObj = m_vObjects[i];

		//오브젝트 타입 값 얻는다.
		OBJECT_TYPE type = pObj->objType;

		//위치 값 얻는다.
		D3DXVECTOR3 pos = pObj->pTransform->GetWorldPosition();

		//사원수 얻는다.
		D3DXQUATERNION quat = pObj->pTransform->GetWorldRotateQuaternion();

		//스케일 얻는다.
		D3DXVECTOR3 scale = pObj->pTransform->GetScale();

		file <<
			"[" << type << "]" <<  //Type 쓴다.
			"[" << pos.x << "," << pos.y << "," << pos.z << "]" <<  //Pos 쓴다.
			"[" << quat.x << "," << quat.y << "," << quat.z << "," << quat.w << "]" <<		//사원수 쓴다
			"[" << scale.x << "," << scale.y << "," << scale.z << "]" <<	//스케일쓴다.
			endl;
	}
	file.close(); //다쓴파일 스트림을 클로즈


	LOG_MGR->AddLog("Saved Objects !!!");
}

void cScene_BoundBoxTool::LoadObjects()
{
	fstream file;
	file.open("ObjectData.txt", fstream::in);  //fstream::in 읽기모드

	std::vector<std::string> strLine;		//string 을 저장하는 벡터

	//파일끝까지 읽는다.
	while (file.eof() == false)  // file.eof() 파일을 읽어재끼다 끝을만나면 true
	{
		std::string line;
		file >> line;			//file 한줄 문자열을 읽어 line 에 대입
		strLine.push_back(line);
	}
	file.close();		//다쓴 파일스트림은 닫는다.

	//읽어온 파일 대로 셋팅
	for (int i = 0; i < strLine.size(); i++)
	{
		if (strLine[i].size() == 0)
			continue;

		//한줄라인이 여기에 대입된다.
		char cStr[2048];
		strcpy(cStr, strLine[i].c_str());

		char* pc;

		//오브젝트 타입
		OBJECT_TYPE type;
		pc = strtok(cStr, "][,");
		type = (OBJECT_TYPE)atoi(pc);

		//위치
		D3DXVECTOR3 pos;
		pc = strtok(NULL, "][,");

		pos.x = atof(pc);
		pc = strtok(NULL, "][,");

		pos.y = atof(pc);
		pc = strtok(NULL, "][,");

		pos.z = atof(pc);

		//사원수
		D3DXQUATERNION quat;
		pc = strtok(NULL, "][,");
		quat.x = atof(pc);
		pc = strtok(NULL, "][,");
		quat.y = atof(pc);
		pc = strtok(NULL, "][,");
		quat.z = atof(pc);
		pc = strtok(NULL, "][,");
		quat.w = atof(pc);

		//스케일
		D3DXVECTOR3 scale;
		pc = strtok(NULL, "][,");
		scale.x = atof(pc);
		pc = strtok(NULL, "][,");
		scale.y = atof(pc);
		pc = strtok(NULL, "][,");
		scale.z = atof(pc);

		//위의 정보로 오브젝트 생성
		cBaseObject* pObject = new cBaseObject();
		pObject->objType = type;
		SelectObjMesh(pObject->objType);
		pObject->SetMesh(m_pMesh);
		pObject->SetActive(true);
		pObject->pTransform->SetWorldPosition(pos);
		pObject->pTransform->SetRotateWorld(quat);
		pObject->pTransform->SetScale(scale);

		//푸쉬 
		m_vObjects.push_back(pObject);

	}
}

void cScene_BoundBoxTool::SaveMonsters()
{
	fstream file;
	file.open("MonsterData.txt", fstream::out); //fstream::out 파일 쓰기 모드

	int size = m_vMonsters.size();
	for (int i = 0; i < m_vMonsters.size(); i++)
	{
		cBaseObject* pMon = m_vMonsters[i];

		//몬스터 타입 값 얻는다.
		MONSTER_TYPE type = pMon->monType;

		//위치 값 얻는다.
		D3DXVECTOR3 pos = pMon->pTransform->GetWorldPosition();

		file <<
			"[" << type << "]" <<  //Type 쓴다.
			"[" << pos.x << "," << pos.y << "," << pos.z << "]" <<  //Pos 쓴다.
			endl;
	}
	file.close(); //다쓴파일 스트림을 클로즈


	LOG_MGR->AddLog("Saved Monsters !!!");
}

void cScene_BoundBoxTool::LoadMonsters()
{
	fstream file;
	file.open("MonsterData.txt", fstream::in);  //fstream::in 읽기모드

	std::vector<std::string> strLine;		//string 을 저장하는 벡터

											//파일끝까지 읽는다.
	while (file.eof() == false)  // file.eof() 파일을 읽어재끼다 끝을만나면 true
	{
		std::string line;
		file >> line;			//file 한줄 문자열을 읽어 line 에 대입
		strLine.push_back(line);
	}
	file.close();		//다쓴 파일스트림은 닫는다.

						//읽어온 파일 대로 셋팅
	for (int i = 0; i < strLine.size(); i++)
	{
		if (strLine[i].size() == 0)
			continue;

		//한줄라인이 여기에 대입된다.
		char cStr[2048];
		strcpy(cStr, strLine[i].c_str());

		char* pc;

		//몬스터 타입
		MONSTER_TYPE type;
		pc = strtok(cStr, "][,");
		type = (MONSTER_TYPE)atoi(pc);

		//위치
		D3DXVECTOR3 pos;
		pc = strtok(NULL, "][,");

		pos.x = atof(pc);
		pc = strtok(NULL, "][,");

		pos.y = atof(pc);
		pc = strtok(NULL, "][,");

		pos.z = atof(pc);


		//위의 정보로 오브젝트 생성
		cBaseObject* pMonster = new cBaseObject();
		pMonster->monType = type;
		SelectMonMesh(pMonster->monType);
		pMonster->SetMesh(m_pMesh);
		pMonster->SetActive(true);
		pMonster->pTransform->SetWorldPosition(pos);

		//푸쉬 
		m_vMonsters.push_back(pMonster);
	}
}

void cScene_BoundBoxTool::SaveBoundBox()
{
	fstream file;
	file.open("BoundData.txt", fstream::out); //fstream::out 파일 쓰기 모드

	int size = m_vBoundBoxes.size();
	for (int i = 0; i < size; i++)
	{
		cSetBoundObject* pBounds = this->m_vBoundBoxes[i];

		//위치 값 얻는다.
		D3DXVECTOR3 pos = pBounds->pTransform->GetWorldPosition();

		//사원수 얻는다.
		D3DXQUATERNION quat = pBounds->pTransform->GetWorldRotateQuaternion();

		//스케일 얻는다.
		D3DXVECTOR3 scale = pBounds->pTransform->GetScale();

		//바운드 정보
		D3DXVECTOR3 boundCenter = pBounds->center;
		D3DXVECTOR3 boundHalf = pBounds->halfSize;


		file <<
			"[" << pos.x << "," << pos.y << "," << pos.z << "]" <<  //Pos 쓴다.
			"[" << quat.x << "," << quat.y << "," << quat.z << "," << quat.w << "]" <<		//사원수 쓴다
			"[" << scale.x << "," << scale.y << "," << scale.z << "]" <<	//스케일쓴다.
			"[" << boundCenter.x << "," << boundCenter.y << "," << boundCenter.z << "]" <<	//바운드 센터 쓴다.
			"[" << boundHalf.x << "," << boundHalf.y << "," << boundHalf.z << "]" <<
			endl;
	}
	file.close(); //다쓴파일 스트림을 클로즈


	LOG_MGR->AddLog("Save BoundBoxes !!!");
}

void cScene_BoundBoxTool::LoadBoundBox()
{
	fstream file;
	file.open("BoundData.txt", fstream::in);  //fstream::in 읽기모드

	std::vector<std::string> strLine;		//string 을 저장하는 벡터

	//파일끝까지 읽는다.
	while (file.eof() == false)  // file.eof() 파일을 읽어재끼다 끝을만나면 true
	{
		std::string line;
		file >> line;			//file 한줄 문자열을 읽어 line 에 대입
		strLine.push_back(line);
	}
	file.close();		//다쓴 파일스트림은 닫는다.

	//읽어온 파일 대로 셋팅
	for (int i = 0; i < strLine.size(); i++)
	{
		if (strLine[i].size() == 0)
			continue;


		//한줄라인이 여기에 대입된다.
		char cStr[2048];
		strcpy(cStr, strLine[i].c_str());

		char* pc;

		//위치
		D3DXVECTOR3 pos;
		pc = strtok(cStr, "][,");		
		pos.x = atof(pc);
		pc = strtok(NULL, "][,");
		pos.y = atof(pc);
		pc = strtok(NULL, "][,");	
		pos.z = atof(pc);

		//사원수
		D3DXQUATERNION quat;
		pc = strtok(NULL, "][,");
		quat.x = atof(pc);
		pc = strtok(NULL, "][,");
		quat.y = atof(pc);
		pc = strtok(NULL, "][,");
		quat.z = atof(pc);
		pc = strtok(NULL, "][,");
		quat.w = atof(pc);

		//스케일
		D3DXVECTOR3 scale;
		pc = strtok(NULL, "][,");
		scale.x = atof(pc);
		pc = strtok(NULL, "][,");
		scale.y = atof(pc);
		pc = strtok(NULL, "][,");
		scale.z = atof(pc);


		//바운드 로컬센터
		D3DXVECTOR3 localCenter;
		pc = strtok(NULL, "][,");
		localCenter.x = atof(pc);
		pc = strtok(NULL, "][,");
		localCenter.y = atof(pc);
		pc = strtok(NULL, "][,");
		localCenter.z = atof(pc);

		//바운드 로컬하프
		D3DXVECTOR3 localHalf;
		pc = strtok(NULL, "][,");
		localHalf.x = atof(pc);
		pc = strtok(NULL, "][,");
		localHalf.y = atof(pc);
		pc = strtok(NULL, "][,");
		localHalf.z = atof(pc);


		//위의 정보로 오브젝트 생성
		cSetBoundObject* pNewBound = new cSetBoundObject();
		pNewBound->SetActive(true);
		pNewBound->pTransform->SetWorldPosition(pos);
		pNewBound->pTransform->SetRotateWorld(quat);
		pNewBound->pTransform->SetScale(scale);
		pNewBound->BoundBox.SetBound(&localCenter, &localHalf);

		//푸쉬 
		this->m_vBoundBoxes.push_back(pNewBound);


	}
}
