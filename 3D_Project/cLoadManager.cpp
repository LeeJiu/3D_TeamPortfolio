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
	//건물 보정 행렬 세팅
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
		vObjects.push_back(pObject);
	}
}

void cLoadManager::LoadBoundBox(vector<cBaseObject*>& vObjects)
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
		cBaseObject* pNewBound = new cBaseObject();
		pNewBound->SetActive(true);
		pNewBound->pTransform->SetWorldPosition(pos);
		pNewBound->pTransform->SetRotateWorld(quat);
		pNewBound->pTransform->SetScale(scale);
		pNewBound->BoundBox.SetBound(&localCenter, &localHalf);

		//푸쉬 
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