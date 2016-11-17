#pragma once
#include "cSpider.h"

class cPlayer;
class cTerrain;

class cMonsterManager
{
private:
	vector<cMonster*>				m_vMonster;
	vector<cMonster*>::iterator		m_viMonster;


	//링크 걸어줄 객체
	cPlayer*		m_pPlayer;
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

	void SetPlayer(cPlayer* pPlayer) { m_pPlayer = pPlayer; }
	void SetTerrain(cTerrain* pTerrain) { m_pTerrain = pTerrain; }
};

