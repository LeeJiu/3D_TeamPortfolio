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
	//���� ���ҽ� ���� �ε�
	//
	//ĳ���� ���� ��� ����
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


	//���Ϸκ��� ���� ������ �ε��ؿ´�.
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
	//���Ϸκ��� �о���� ���� ������ ���͸� �����Ѵ�.
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


		//Ǫ�� 
		//CreateMonster(type, pos);
	}

	//�ӽ÷� ���͸� �����Ϸ��� CreateMonster()�� �߰��ϰ�,
	//������ ���� �ڵ带 �ۼ��Ѵ�. type, pos
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
