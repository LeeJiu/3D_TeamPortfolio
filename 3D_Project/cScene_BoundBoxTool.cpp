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

	m_pSelectObject = new cBaseObject;
	m_pSelectObject->SetActive(true);
	m_pSelectObject->SetMesh(RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Migdal/migdal_Wall.X", &matCorrection));
	
	RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Migdal_House/house_nobel.X", &matCorrection);



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
	//���̷��� ����Ʈ ����
	//lights[0]->pTransform->DefaultControl2(timeDelta);

	//������ ������Ʈ ũ�� �� �̵� ����
	m_pSelectObject->pTransform->DefaultControl4(timeDelta);

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
	/*cXMesh_Skinned::sSkinnedMeshEffect->SetMatrixArray("matLights", matLights, 10);
	cXMesh_Skinned::sSkinnedMeshEffect->SetInt("LightNum", this->lights.size());

	cXMesh_Skinned::SetCamera(this->pMainCamera);*/




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
	//��ġ�� ������Ʈ�� �����Ѵ�.
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
			LOG_MGR->AddLog("������Ʈ ����");
		else
			LOG_MGR->AddLog("������Ʈ ����");
	}

	//��ŷ�ؼ� �� ��ġ�� ������Ʈ�� ����,
	//��ġ ��Ų ������Ʈ�� ���Ϳ� �߰��Ѵ�.
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

		//������ �ͷ��� ��Ʈ ����Ʈ�� ��´�.
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

	//������ �ͷ��� ��Ʈ ����Ʈ�� ��´�.
	D3DXVECTOR3 pos;
	m_pTerrain->IsIntersectRay(&pos, &ray);

	//������Ʈ�� ���Ϳ� �߰��Ѵ�.
	cBaseObject* obj = new cBaseObject;
	obj->SetMesh(m_pSelectObject->pMesh);
	obj->pTransform->SetWorldPosition(pos);
	obj->SetActive(true);
	objects.push_back(obj);

	//�������� ���� ������Ʈ�� ���õ� ������Ʈ��
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

	//���� �ִ� ��� ����üũ
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
			//�浹�� ���̶��...
			hitObjects.push_back(this->objects[i]);

			//ī�޶�κ����� �Ÿ� ������ Ǫ��
			hitDistances.push_back(D3DXVec3LengthSq(
				&(hitPos - this->pMainCamera->GetWorldPosition())));
		}
	}


	//��Ʈ �� ���� �ִٸ�...
	if (hitObjects.size() > 0)
	{
		//�ϴ� ù��° 
		cBaseObject* pTarget = hitObjects[0];
		float nearest = hitDistances[0];

		for (int i = 1; i < hitObjects.size(); i++)
		{
			//����
			if (nearest > hitDistances[i])
			{
				nearest = hitDistances[i];
				pTarget = hitObjects[i];
			}
		}

		//���õ� ������Ʈ
		m_pSelectObject = pTarget;
	}
}

void cScene_BoundBoxTool::SaveObjects()
{
	fstream file;
	file.open("ObjectData.txt", fstream::out); //fstream::out ���� ���� ���

	int size = objects.size();
	for (int i = 0; i < objects.size(); i++)
	{
		cBaseObject* pObj = objects[i];

		//��ġ �� ��´�.
		D3DXVECTOR3 pos = pObj->pTransform->GetWorldPosition();

		//����� ��´�.
		D3DXQUATERNION quat = pObj->pTransform->GetWorldRotateQuaternion();

		//������ ��´�.
		D3DXVECTOR3 scale = pObj->pTransform->GetScale();

		file <<
			"[" << pos.x << "," << pos.y << "," << pos.z << "]" <<  //Pos ����.
			"[" << quat.x << "," << quat.y << "," << quat.z << "," << quat.w << "]" <<		//����� ����
			"[" << scale.x << "," << scale.y << "," << scale.z << "]" <<	//�����Ͼ���.
			endl;
	}
	file.close(); //�پ����� ��Ʈ���� Ŭ����


	LOG_MGR->AddLog("Saved Objects !!!");
}

void cScene_BoundBoxTool::LoadObjects()
{
	fstream file;
	file.open("ObjectData.txt", fstream::in);  //fstream::in �б���

	std::vector<std::string> strLine;		//string �� �����ϴ� ����

	//���ϳ����� �д´�.
	while (file.eof() == false)  // file.eof() ������ �о��糢�� ���������� true
	{
		std::string line;
		file >> line;			//file ���� ���ڿ��� �о� line �� ����
		strLine.push_back(line);
	}
	file.close();		//�پ� ���Ͻ�Ʈ���� �ݴ´�.

	//�о�� ���� ��� ����
	for (int i = 0; i < strLine.size(); i++)
	{
		if (strLine[i].size() == 0)
			continue;

		//���ٶ����� ���⿡ ���Եȴ�.
		char cStr[2048];
		strcpy(cStr, strLine[i].c_str());

		char* pc;

		//��ġ
		D3DXVECTOR3 pos;
		pc = strtok(cStr, "][,");			

		pos.x = atof(pc);
		pc = strtok(NULL, "][,");			
											
		pos.y = atof(pc);
		pc = strtok(NULL, "][,");

		pos.z = atof(pc);

		//�����
		D3DXQUATERNION quat;
		pc = strtok(NULL, "][,");
		quat.x = atof(pc);
		pc = strtok(NULL, "][,");
		quat.y = atof(pc);
		pc = strtok(NULL, "][,");
		quat.z = atof(pc);
		pc = strtok(NULL, "][,");
		quat.w = atof(pc);

		//������
		D3DXVECTOR3 scale;
		pc = strtok(NULL, "][,");
		scale.x = atof(pc);
		pc = strtok(NULL, "][,");
		scale.y = atof(pc);
		pc = strtok(NULL, "][,");
		scale.z = atof(pc);

		//���� ������ ������Ʈ ����
		cBaseObject* pObject = new cBaseObject();
		pObject->SetActive(true);
		pObject->pTransform->SetWorldPosition(pos);
		pObject->pTransform->SetRotateWorld(quat);
		pObject->pTransform->SetScale(scale);

		//Ǫ�� 
		objects.push_back(pObject);

	}
}
