#include "stdafx.h"
#include "cMonsterManager.h"


cMonsterManager::cMonsterManager()
{
}


cMonsterManager::~cMonsterManager()
{
}

HRESULT cMonsterManager::Init()
{
	//
	//몬스터 리소스 파일 로딩
	//
	//캐릭터 보정 행렬 세팅
	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.05f, 0.05f, 0.05f);
	D3DXMATRIXA16 matRotate;
	D3DXMatrixRotationY(&matRotate, -90.0f * ONE_RAD);
	D3DXMATRIXA16 matCorrection = matScale * matRotate;

	RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Monster/Bashil/MOB_Bashil.X", &matCorrection);
	RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Monster/Griff/MOB_HipGriff.X", &matCorrection);
	RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Monster/Minho/MOB_Minho.X", &matCorrection);
	RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Monster/SpiderQueen/MOB_Spider.X", &matCorrection);
	RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Monster/SpiderQueen/MOB_SpiderQueen.X", &matCorrection);
	RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Monster/Surcubus/surcubus.X", &matCorrection);
	RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Boss/SkulDragon/skulDragon_1.X", &matCorrection);


	//파일로부터 몬스터 정보를 로드해온다.
	LoadMonsters();

	return S_OK;
}

void cMonsterManager::Release()
{
	for (m_viMonster = m_vMonster.begin(); m_viMonster != m_vMonster.end(); ++m_viMonster)
	{
		SAFE_DELETE(*m_viMonster);
	}
	m_vMonster.clear();
}

void cMonsterManager::Update(float timeDelta)
{
	int size = m_vMonster.size();
	for (int i = 0; i < size; ++i)
	{
		m_vMonster[i]->Update(timeDelta);
	}
}

void cMonsterManager::Render()
{
	int size = m_vMonster.size();
	for (int i = 0; i < size; ++i)
	{
		m_vMonster[i]->Render();
	}
}

void cMonsterManager::LoadMonsters()
{
	//파일로부터 읽어들인 몬스터 정보로 몬스터를 세팅한다.
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


		//푸쉬 
		//CreateMonster(type, pos);
	}

	//임시로 몬스터를 세팅하려면 CreateMonster()에 추가하고,
	//다음과 같이 코드를 작성한다. type, pos
	CreateMonster(DRAGON, D3DXVECTOR3(0, m_pTerrain->GetHeight(0, 0), 0));
	//CreateMonster(MINO, D3DXVECTOR3(20, m_pTerrain->GetHeight(20, 20), 20));
}

void cMonsterManager::CreateMonster(MONSTER_TYPE type, D3DXVECTOR3 pos)
{
	cMonster* monster;

	switch (type)
	{
	case BASILISK:
		monster = new cBasilisk;
		monster->SetTerrain(m_pTerrain);
		monster->SetPlayer(m_pPlayer);
		monster->SetMesh(RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Monster/Bashil/MOB_Bashil.X"));
		monster->pTransform->SetWorldPosition(pos);
		monster->SetActive(true);
		break;
	case GRIFF:
		monster = new cGriff;
		monster->SetTerrain(m_pTerrain);
		monster->SetPlayer(m_pPlayer);
		monster->SetMesh(RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Monster/Griff/MOB_HipGriff.X"));
		monster->pTransform->SetWorldPosition(pos);
		monster->SetActive(true);
		break;
	case MINO:
		monster = new cMinotauros;
		monster->SetTerrain(m_pTerrain);
		monster->SetPlayer(m_pPlayer);
		monster->SetMesh(RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Monster/Minho/MOB_Minho.X"));
		monster->pTransform->SetWorldPosition(pos);
		monster->SetActive(true);
		break;
	case SPIDER:
		monster = new cSpider;
		monster->SetTerrain(m_pTerrain);
		monster->SetPlayer(m_pPlayer);
		monster->SetMesh(RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Monster/SpiderQueen/MOB_Spider.X"));
		monster->pTransform->SetWorldPosition(pos);
		monster->SetActive(true);
		break;
	case SPIDER_QUEEN:
		monster = new cSpiderQueen;
		monster->SetTerrain(m_pTerrain);
		monster->SetPlayer(m_pPlayer);
		monster->SetMesh(RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Monster/SpiderQueen/MOB_SpiderQueen.X"));
		monster->pTransform->SetWorldPosition(pos);
		monster->SetActive(true);
		break;
	case SUCCUBUS:
		monster = new cSuccubus;
		monster->SetTerrain(m_pTerrain);
		monster->SetPlayer(m_pPlayer);
		monster->SetMesh(RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Monster/Surcubus/surcubus.X"));
		monster->pTransform->SetWorldPosition(pos);
		monster->SetActive(true);
		break;
	case DRAGON:
		monster = new cDragon;
		monster->SetTerrain(m_pTerrain);
		monster->SetPlayer(m_pPlayer);
		monster->SetMesh(RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Boss/SkulDragon/skulDragon_1.X"));
		monster->pTransform->SetWorldPosition(pos);
		monster->monType = DRAGON;
		monster->SetActive(true);
		break;
	default:
		break;
	}

	m_vMonster.push_back(monster);
}
