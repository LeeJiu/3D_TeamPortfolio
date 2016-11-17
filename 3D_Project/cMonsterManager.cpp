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
	//���� ���ҽ� ���� �ε�
	
	//ĳ���� ���� ��� ����
	D3DXMATRIXA16 matScale;
	D3DXMatrixScaling(&matScale, 0.1f, 0.1f, 0.1f);
	D3DXMATRIXA16 matRotate;
	D3DXMatrixRotationY(&matRotate, -90.0f * ONE_RAD);
	D3DXMATRIXA16 matCorrection = matScale * matRotate;

	RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Monster/SpiderQueen/MOB_Spider.X", &matCorrection);

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




	//������ �ӽ÷� ���͸� �����Ѵ�.
	CreateMonster(SPIDER, D3DXVECTOR3(10, m_pTerrain->GetHeight(10, 5), 5));
	CreateMonster(SPIDER, D3DXVECTOR3(10, m_pTerrain->GetHeight(10, 0), 0));
}

void cMonsterManager::CreateMonster(MONSTER_TYPE type, D3DXVECTOR3 pos)
{
	cMonster* monster;

	switch (type)
	{
	case BASILISK:
		break;
	case GRIFF:
		break;
	case MINO:
		break;
	case SPIDER:
		monster = new cSpider(1000, 10);
		monster->SetTerrain(m_pTerrain);
		monster->SetPlayer(m_pPlayer);
		monster->SetMesh(RESOURCE_SKINNEDXMESH->GetResource("../Resources/Meshes/Monster/SpiderQueen/MOB_Spider.X"));
		monster->pTransform->SetWorldPosition(pos);
		monster->SetActive(true);
		break;
	case SPIDER_QUEEN:
		break;
	case SUCCUBUS:
		break;
	case DRAGON:
		break;
	default:
		break;
	}

	m_vMonster.push_back(monster);
}
