#include "stdafx.h"
#include "cScene_BoundBoxTool.h"
#include "cTerrain.h"
#include "cMonster.h"
#include "cLight_Direction.h"
#include "cLight_Point.h"
#include "cCamera.h"
#include <fstream>		//FileStream


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

	m_pSelectObject = new cBaseObject;
	m_pSelectObject->SetActive(true);
	m_pSelectObject->SetMesh(RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Migdal/migdal_Wall.X", &matCorrection));
	
	RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Migdal_House/house_nobel.X", &matCorrection);



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


	return S_OK;
}

void cScene_BoundBoxTool::Scene_Release()
{
	m_pTerrain->Release();
	SAFE_DELETE(m_pTerrain);
	SAFE_DELETE(m_pSelectObject);


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
	//다이렉션 라이트 조종
	//lights[0]->pTransform->DefaultControl2(timeDelta);

	//선택한 오브젝트 크기 및 이동 설정
	m_pSelectObject->pTransform->DefaultControl4(timeDelta);

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
	/*cXMesh_Skinned::sSkinnedMeshEffect->SetMatrixArray("matLights", matLights, 10);
	cXMesh_Skinned::sSkinnedMeshEffect->SetInt("LightNum", this->lights.size());

	cXMesh_Skinned::SetCamera(this->pMainCamera);*/




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
	//설치할 오브젝트를 변경한다.
	if (KEY_MGR->IsOnceDown('1'))
	{
		m_pSelectObject->SetMesh(RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Migdal/migdal_Wall.X"));
	}
	if (KEY_MGR->IsOnceDown('2'))
	{
		m_pSelectObject->SetMesh(RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Migdal_House/house_nobel.X"));
	}

	if (KEY_MGR->IsOnceDown(VK_RETURN))
	{
		m_bSelectObj = !m_bSelectObj;
		if(m_bSelectObj)
			LOG_MGR->AddLog("오브젝트 선택");
		else
			LOG_MGR->AddLog("오브젝트 세팅");
	}

	//피킹해서 그 위치에 오브젝트를 놓고,
	//위치 시킨 오브젝트를 벡터에 추가한다.
	if (KEY_MGR->IsOnceDown(VK_LBUTTON))
	{
		if (m_bSelectObj == true)
		{
			SelectObject();
		}
		else
		{
			SetObjects();
		}
	}

	if (m_bSelectObj && KEY_MGR->IsStayDown(VK_LBUTTON))
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

	if (KEY_MGR->IsStayDown(VK_LCONTROL) && KEY_MGR->IsOnceDown('S'))
	{
		SaveObjects();
	}

	if (KEY_MGR->IsStayDown(VK_LCONTROL) && KEY_MGR->IsOnceDown('L'))
	{
		LoadObjects();
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
	obj->pTransform->SetWorldPosition(pos);
	obj->SetActive(true);
	objects.push_back(obj);

	//마지막에 넣은 오브젝트를 선택된 오브젝트로
	m_pSelectObject = objects.back();
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
	int size = objects.size();
	for (int i = 0; i < size; ++i)
	{
		D3DXVECTOR3 hitPos;
		if (PHYSICS_MGR->IsRayHitBound(
			&ray,
			&this->objects[i]->BoundBox,
			this->objects[i]->pTransform,
			&hitPos,
			NULL)) 
		{
			//충돌된 놈이라면...
			hitObjects.push_back(this->objects[i]);

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

void cScene_BoundBoxTool::SaveObjects()
{
	fstream file;
	file.open("ObjectData.txt", fstream::out); //fstream::out 파일 쓰기 모드

	int size = objects.size();
	for (int i = 0; i < objects.size(); i++)
	{
		cBaseObject* pObj = objects[i];

		//위치 값 얻는다.
		D3DXVECTOR3 pos = pObj->pTransform->GetWorldPosition();

		//사원수 얻는다.
		D3DXQUATERNION quat = pObj->pTransform->GetWorldRotateQuaternion();

		//스케일 얻는다.
		D3DXVECTOR3 scale = pObj->pTransform->GetScale();

		file <<
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

		//위의 정보로 오브젝트 생성
		cBaseObject* pObject = new cBaseObject();
		pObject->SetActive(true);
		pObject->pTransform->SetWorldPosition(pos);
		pObject->pTransform->SetRotateWorld(quat);
		pObject->pTransform->SetScale(scale);

		//푸쉬 
		objects.push_back(pObject);

	}
}
