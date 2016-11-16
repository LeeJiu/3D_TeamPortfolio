#pragma once
#include "cSpider.h"

class cBaseObject;
class cTerrain;

class cMonsterManager
{
private:
	vector<cMonster*>				m_vMonster;
	vector<cMonster*>::iterator		m_viMonster;


	//��ũ �ɾ��� ��ü
	cBaseObject*	m_pPlayer;
	cTerrain*		m_pTerrain;

public:
	cMonsterManager();
	~cMonsterManager();

	HRESULT Init();
	void Release();
	void Update(float timeDelta);
	void Render();

	void LoadMonsters();

	void CreateMonster(MONSTER_TYPE type, D3DXVECTOR3 pos);

	void SetPlayer(cBaseObject* pPlayer) { m_pPlayer = pPlayer; }
	void SetTerrain(cTerrain* pTerrain) { m_pTerrain = pTerrain; }
};

