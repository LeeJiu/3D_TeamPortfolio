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
	//���� ����
	//
	//ĳ���� ���� ��� ����
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
	m_bSwapSelection = false;	//������Ʈ�� ����
	m_bSetBoundBox = false;		//�ٿ�� �ڽ� ��ġ�Ϸ��� true��

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
	//���̷��� ����Ʈ ����
	//lights[0]->pTransform->DefaultControl2(timeDelta);

	//ī�޶� ����
	pMainCamera->DefaultControl(timeDelta);
	
	//�ٿ��ڽ� ��ġ / ������Ʈ|���� ��ġ
	if (KEY_MGR->IsOnceDown('B'))
	{
		m_bSetBoundBox = !m_bSetBoundBox;
		if (m_bSetBoundBox)
		{
			LOG_MGR->AddLog("[�ٿ��ڽ�]");
		}
		else
		{
			LOG_MGR->AddLog("[������Ʈ|����]");
		}
	}

	//���̺� & �ε�
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

	//����Ǵ� LightMatrix
	D3DXMATRIXA16 matLights[10];
	for (int i = 0; i < this->lights.size(); i++)
		matLights[i] = this->lights[i]->GetLightMatrix();

	//���̴��� ������ ����
	cXMesh_Static::SetCamera(this->pMainCamera);
	cXMesh_Static::SetTechniqueName("Base");		//������� ���� �׸����� ReciveShadow �� Technique ����
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

	//�ٿ�带 �׸���.
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
	//������Ʈ / ���� ��ȯ
	if (KEY_MGR->IsOnceDown(VK_SPACE))
	{
		m_bSwapSelection = !m_bSwapSelection;
		if (m_bSwapSelection)
		{
			LOG_MGR->AddLog("[����]");
			m_pMesh = m_pSelectMonster->pMesh;
		}
		else
		{
			LOG_MGR->AddLog("[������Ʈ]");
			m_pMesh = m_pSelectObject->pMesh;
		}
	}

	//���� ��ġ�� ��
	if (m_bSwapSelection)
	{
		ControlMonsters(timeDelta);
	}
	//������Ʈ ��ġ�� ��
	else
	{
		ControlObjects(timeDelta);
	}	
}

void cScene_BoundBoxTool::KeyControl2(float timeDelta)
{
	//�ٿ�� �ڽ� �߰�
	if (KEY_MGR->IsOnceDown(VK_ADD))
	{
		//���� ���콺 ��ġ�� �ٿ�� �ڽ��� ����
		Ray ray;
		POINT ptMouse = GetMousePos();
		D3DXVECTOR2 screenPos(ptMouse.x, ptMouse.y);
		this->pMainCamera->ComputeRay(&ray, &screenPos);

		//������ �ͷ��� ��Ʈ ����Ʈ�� ��´�.
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
	//��ġ�� ������Ʈ�� �����Ѵ�.
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

	//������Ʈ ���� / ���� ��ȯ
	if (KEY_MGR->IsOnceDown(VK_RETURN))
	{
		m_bSelectObj = !m_bSelectObj;
		if (m_bSelectObj)
			LOG_MGR->AddLog("������Ʈ ����");
		else
			LOG_MGR->AddLog("������Ʈ ����");
	}


	if (m_bSelectObj == true)
	{
		//������Ʈ ����
		if (KEY_MGR->IsStayDown(VK_LCONTROL) == true && KEY_MGR->IsOnceDown(VK_LBUTTON))
			SelectObject();

		//���õ� ������Ʈ �巡��
		if (KEY_MGR->IsStayDown(VK_LCONTROL) == false && KEY_MGR->IsStayDown(VK_LBUTTON))
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

		//���õ� ������Ʈ ����
		if (KEY_MGR->IsOnceDown(VK_DELETE))
		{
			DeleteObject();
		}
	}
	else
	{
		//������Ʈ ����
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
		//������ ������Ʈ ũ�� �� �̵� ����
		m_pSelectObject->pTransform->DefaultControl4(timeDelta);
	}
}

void cScene_BoundBoxTool::ControlMonsters(float timeDelta)
{
	//��ġ�� ���͸� �����Ѵ�.
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

	//���� ���� / ���� ��ȯ
	if (KEY_MGR->IsOnceDown(VK_RETURN))
	{
		m_bSelectObj = !m_bSelectObj;
		if (m_bSelectObj)
			LOG_MGR->AddLog("���� ����");
		else
			LOG_MGR->AddLog("���� ����");
	}


	if (m_bSelectObj == true)
	{
		//���� ����
		if (KEY_MGR->IsStayDown(VK_LCONTROL) == true && KEY_MGR->IsOnceDown(VK_LBUTTON))
			SelectMonster();

		//���õ� ���� �巡��
		if (KEY_MGR->IsStayDown(VK_LCONTROL) == false && KEY_MGR->IsStayDown(VK_LBUTTON))
		{
			Ray ray;
			POINT ptMouse = GetMousePos();
			D3DXVECTOR2 screenPos(ptMouse.x, ptMouse.y);
			this->pMainCamera->ComputeRay(&ray, &screenPos);

			//������ �ͷ��� ��Ʈ ����Ʈ�� ��´�.
			D3DXVECTOR3 pos;
			m_pTerrain->IsIntersectRay(&pos, &ray);

			m_pSelectMonster->pTransform->SetWorldPosition(pos);
		}

		//���õ� ���� ����
		if (KEY_MGR->IsOnceDown(VK_DELETE))
		{
			DeleteMonster();
		}
	}
	else
	{
		//���� ����
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
	//�ٿ��ڽ� ����
	if (KEY_MGR->IsStayDown(VK_LCONTROL) == true && KEY_MGR->IsOnceDown(VK_LBUTTON))
		SelectBoundBox();

	//���õ� �ٿ��ڽ� �巡��
	if (KEY_MGR->IsStayDown(VK_LCONTROL) == false && KEY_MGR->IsStayDown(VK_LBUTTON))
	{
		if (m_pSelectBound == NULL) return;

		Ray ray;
		POINT ptMouse = GetMousePos();
		D3DXVECTOR2 screenPos(ptMouse.x, ptMouse.y);
		this->pMainCamera->ComputeRay(&ray, &screenPos);

		//������ �ͷ��� ��Ʈ ����Ʈ�� ��´�.
		D3DXVECTOR3 pos;
		m_pTerrain->IsIntersectRay(&pos, &ray);

		m_pSelectBound->pTransform->SetWorldPosition(pos);
	}

	//���õ� �ٿ��ڽ� ����
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

	//������ �ͷ��� ��Ʈ ����Ʈ�� ��´�.
	D3DXVECTOR3 pos;
	m_pTerrain->IsIntersectRay(&pos, &ray);

	//������Ʈ�� ���Ϳ� �߰��Ѵ�.
	cBaseObject* obj = new cBaseObject;
	obj->SetMesh(m_pSelectObject->pMesh);
	obj->objType = m_pSelectObject->objType;
	obj->pTransform->SetWorldPosition(pos);
	obj->SetActive(true);
	m_vObjects.push_back(obj);

	//�������� ���� ������Ʈ�� ���õ� ������Ʈ��
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

	//���� �ִ� ��� ����üũ
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
			//�浹�� ���̶��...
			hitObjects.push_back(this->m_vObjects[i]);

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

void cScene_BoundBoxTool::DeleteObject()
{
	if (m_pSelectObject != NULL)
	{
		//���Ϳ��� ������
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
					m_pSelectObject = m_vObjects.back();	//���� �������� �� ������Ʈ�� ����
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

	//������ �ͷ��� ��Ʈ ����Ʈ�� ��´�.
	D3DXVECTOR3 pos;
	m_pTerrain->IsIntersectRay(&pos, &ray);

	//���͸� ���Ϳ� �߰��Ѵ�.
	cBaseObject* mon = new cBaseObject;
	mon->SetMesh(m_pSelectMonster->pMesh);
	mon->monType = m_pSelectMonster->monType;
	mon->pTransform->SetWorldPosition(pos);
	mon->SetActive(true);
	m_vMonsters.push_back(mon);

	//�������� ���� ���͸� ���õ� ���ͷ�
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

	//���� �ִ� ��� ����üũ
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
			//�浹�� ���̶��...
			hitMonsters.push_back(this->m_vMonsters[i]);

			//ī�޶�κ����� �Ÿ� ������ Ǫ��
			hitDistances.push_back(D3DXVec3LengthSq(
				&(hitPos - this->pMainCamera->GetWorldPosition())));
		}
	}


	//��Ʈ �� ���� �ִٸ�...
	if (hitMonsters.size() > 0)
	{
		//�ϴ� ù��° 
		cBaseObject* pTarget = hitMonsters[0];
		float nearest = hitDistances[0];

		for (int i = 1; i < hitMonsters.size(); i++)
		{
			//����
			if (nearest > hitDistances[i])
			{
				nearest = hitDistances[i];
				pTarget = hitMonsters[i];
			}
		}

		//���õ� ������Ʈ
		m_pSelectMonster = pTarget;
	}
}

void cScene_BoundBoxTool::DeleteMonster()
{
	if (m_pSelectMonster != NULL)
	{
		//���Ϳ��� ������
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
					m_pSelectMonster = m_vMonsters.back();	//���� �������� �� ���͸� ����
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

	//���� �ִ� ��� ����üũ
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
			//�浹�� ���̶��...
			hitObjects.push_back(this->m_vBoundBoxes[i]);

			//ī�޶�κ����� �Ÿ� ������ Ǫ��
			hitDistances.push_back(D3DXVec3LengthSq(
				&(hitPos - this->pMainCamera->GetWorldPosition())));
		}
	}


	//��Ʈ �� ���� �ִٸ�...
	if (hitObjects.size() > 0)
	{
		//�ϴ� ù��° 
		cSetBoundObject* pTarget = hitObjects[0];
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
		m_pSelectBound = pTarget;
	}
}

void cScene_BoundBoxTool::DeleteBoundBox()
{
	if (m_pSelectBound != NULL)
	{
		//���Ϳ��� ������
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
					m_pSelectBound = m_vBoundBoxes.back();	//���� �������� �� ������Ʈ�� ����
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
	file.open("ObjectData.txt", fstream::out); //fstream::out ���� ���� ���

	int size = m_vObjects.size();
	for (int i = 0; i < m_vObjects.size(); i++)
	{
		cBaseObject* pObj = m_vObjects[i];

		//������Ʈ Ÿ�� �� ��´�.
		OBJECT_TYPE type = pObj->objType;

		//��ġ �� ��´�.
		D3DXVECTOR3 pos = pObj->pTransform->GetWorldPosition();

		//����� ��´�.
		D3DXQUATERNION quat = pObj->pTransform->GetWorldRotateQuaternion();

		//������ ��´�.
		D3DXVECTOR3 scale = pObj->pTransform->GetScale();

		file <<
			"[" << type << "]" <<  //Type ����.
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

		//������Ʈ Ÿ��
		OBJECT_TYPE type;
		pc = strtok(cStr, "][,");
		type = (OBJECT_TYPE)atoi(pc);

		//��ġ
		D3DXVECTOR3 pos;
		pc = strtok(NULL, "][,");

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
		pObject->objType = type;
		SelectObjMesh(pObject->objType);
		pObject->SetMesh(m_pMesh);
		pObject->SetActive(true);
		pObject->pTransform->SetWorldPosition(pos);
		pObject->pTransform->SetRotateWorld(quat);
		pObject->pTransform->SetScale(scale);

		//Ǫ�� 
		m_vObjects.push_back(pObject);

	}
}

void cScene_BoundBoxTool::SaveMonsters()
{
	fstream file;
	file.open("MonsterData.txt", fstream::out); //fstream::out ���� ���� ���

	int size = m_vMonsters.size();
	for (int i = 0; i < m_vMonsters.size(); i++)
	{
		cBaseObject* pMon = m_vMonsters[i];

		//���� Ÿ�� �� ��´�.
		MONSTER_TYPE type = pMon->monType;

		//��ġ �� ��´�.
		D3DXVECTOR3 pos = pMon->pTransform->GetWorldPosition();

		file <<
			"[" << type << "]" <<  //Type ����.
			"[" << pos.x << "," << pos.y << "," << pos.z << "]" <<  //Pos ����.
			endl;
	}
	file.close(); //�پ����� ��Ʈ���� Ŭ����


	LOG_MGR->AddLog("Saved Monsters !!!");
}

void cScene_BoundBoxTool::LoadMonsters()
{
	fstream file;
	file.open("MonsterData.txt", fstream::in);  //fstream::in �б���

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

		//���� Ÿ��
		MONSTER_TYPE type;
		pc = strtok(cStr, "][,");
		type = (MONSTER_TYPE)atoi(pc);

		//��ġ
		D3DXVECTOR3 pos;
		pc = strtok(NULL, "][,");

		pos.x = atof(pc);
		pc = strtok(NULL, "][,");

		pos.y = atof(pc);
		pc = strtok(NULL, "][,");

		pos.z = atof(pc);


		//���� ������ ������Ʈ ����
		cBaseObject* pMonster = new cBaseObject();
		pMonster->monType = type;
		SelectMonMesh(pMonster->monType);
		pMonster->SetMesh(m_pMesh);
		pMonster->SetActive(true);
		pMonster->pTransform->SetWorldPosition(pos);

		//Ǫ�� 
		m_vMonsters.push_back(pMonster);
	}
}

void cScene_BoundBoxTool::SaveBoundBox()
{
	fstream file;
	file.open("BoundData.txt", fstream::out); //fstream::out ���� ���� ���

	int size = m_vBoundBoxes.size();
	for (int i = 0; i < size; i++)
	{
		cSetBoundObject* pBounds = this->m_vBoundBoxes[i];

		//��ġ �� ��´�.
		D3DXVECTOR3 pos = pBounds->pTransform->GetWorldPosition();

		//����� ��´�.
		D3DXQUATERNION quat = pBounds->pTransform->GetWorldRotateQuaternion();

		//������ ��´�.
		D3DXVECTOR3 scale = pBounds->pTransform->GetScale();

		//�ٿ�� ����
		D3DXVECTOR3 boundCenter = pBounds->center;
		D3DXVECTOR3 boundHalf = pBounds->halfSize;


		file <<
			"[" << pos.x << "," << pos.y << "," << pos.z << "]" <<  //Pos ����.
			"[" << quat.x << "," << quat.y << "," << quat.z << "," << quat.w << "]" <<		//����� ����
			"[" << scale.x << "," << scale.y << "," << scale.z << "]" <<	//�����Ͼ���.
			"[" << boundCenter.x << "," << boundCenter.y << "," << boundCenter.z << "]" <<	//�ٿ�� ���� ����.
			"[" << boundHalf.x << "," << boundHalf.y << "," << boundHalf.z << "]" <<
			endl;
	}
	file.close(); //�پ����� ��Ʈ���� Ŭ����


	LOG_MGR->AddLog("Save BoundBoxes !!!");
}

void cScene_BoundBoxTool::LoadBoundBox()
{
	fstream file;
	file.open("BoundData.txt", fstream::in);  //fstream::in �б���

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


		//�ٿ�� ���ü���
		D3DXVECTOR3 localCenter;
		pc = strtok(NULL, "][,");
		localCenter.x = atof(pc);
		pc = strtok(NULL, "][,");
		localCenter.y = atof(pc);
		pc = strtok(NULL, "][,");
		localCenter.z = atof(pc);

		//�ٿ�� ��������
		D3DXVECTOR3 localHalf;
		pc = strtok(NULL, "][,");
		localHalf.x = atof(pc);
		pc = strtok(NULL, "][,");
		localHalf.y = atof(pc);
		pc = strtok(NULL, "][,");
		localHalf.z = atof(pc);


		//���� ������ ������Ʈ ����
		cSetBoundObject* pNewBound = new cSetBoundObject();
		pNewBound->SetActive(true);
		pNewBound->pTransform->SetWorldPosition(pos);
		pNewBound->pTransform->SetRotateWorld(quat);
		pNewBound->pTransform->SetScale(scale);
		pNewBound->BoundBox.SetBound(&localCenter, &localHalf);

		//Ǫ�� 
		this->m_vBoundBoxes.push_back(pNewBound);


	}
}
