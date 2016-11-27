#include "stdafx.h"
#include "cLoadManager.h"


cLoadManager::cLoadManager()
{
	m_pMesh = NULL;
}


cLoadManager::~cLoadManager()
{
}

HRESULT cLoadManager::Init()
{
	//�ǹ� ���� ��� ����
	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.02f, 0.02f, 0.02f);
	D3DXMATRIXA16 matRotate;
	D3DXMatrixRotationY(&matRotate, -90.0f * ONE_RAD);
	D3DXMATRIXA16 matCorrection = matScale * matRotate;

	RESOURCE_STATICXMESH->GetResource("../Resources/Meshes/Migdal/migdal_Wall.X", &matCorrection);
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

	return S_OK;
}

void cLoadManager::Release()
{
}

void cLoadManager::LoadObjects(vector<cBaseObject*>& vObjects)
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
		vObjects.push_back(pObject);
	}
}

void cLoadManager::LoadBoundBox(vector<cBaseObject*>& vObjects)
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
		cBaseObject* pNewBound = new cBaseObject();
		pNewBound->SetActive(true);
		pNewBound->pTransform->SetWorldPosition(pos);
		pNewBound->pTransform->SetRotateWorld(quat);
		pNewBound->pTransform->SetScale(scale);
		pNewBound->BoundBox.SetBound(&localCenter, &localHalf);

		//Ǫ�� 
		vObjects.push_back(pNewBound);
	}
}

void cLoadManager::SelectObjMesh(OBJECT_TYPE type)
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