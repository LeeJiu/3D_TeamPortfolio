#pragma once
#include "cScene.h"

class cBaseObject;
class cCamera;
class cTerrain;
class cSkinnedAnimation;


class monster_Test : public cScene
{
private:
	cSkinnedAnimation*		pSkinned1;
	cTransform*				pSkinnedTrans;

	cBoundBox*            pATK;
	cTransform*           pATKTrans;
	D3DXVECTOR3             pATKLength;
	bool                  isATK;
	float                 pPlayerSpeed;

	cSkinnedAnimation*      pMonster[10];
	cTransform*             pMonsterTrans[10];
	Ray                     cMobRay[10];
	bool                    isMobMove[10];
	D3DXVECTOR3             m_mob_currentPos[10];
	D3DXVECTOR3             m_mob_prePos[10];
	D3DXVECTOR3             m_mob_lastPos[10];
	D3DXVECTOR3             m_mob_firstPos[10];
	float                   m_mob_Speed[10];
	std::string             m_mob_currentAni[10];

	bool                    isTarget;

	cTransform*				pTransForCamera;

	Ray						cRay; //�ɸ��Ϳ� �� ����.
	bool                    objectHit;

	// �����ӿ� �Ẽ��.
	D3DXVECTOR3		m_currentPos;// �� �ɸ����� ��ġ
	D3DXVECTOR3		m_prePos;// ���� ������ ��ġ
	D3DXVECTOR3		m_lastPos;// ���� ���� y���� ��ȯ ��ų�� ����.
	D3DXVECTOR3		m_mousePos;// Ŭ�������� ��ġ.

	bool isMove;
	bool isObject;
	bool isTerrain;
	bool isClick;


	std::string current_Ani;


	std::vector<cLight*>	lights;

	cTerrain*		m_pTerrain;
	D3DXVECTOR3		m_hitPos;


	D3DXVECTOR3		m_hitDir;
	bool			m_bMove;

	cBaseObject*	m_Land;			//�ø��� ������Ʈ

	D3DXMATRIXA16 temp;
	D3DXMATRIXA16 m_matCorrection;

	int  aniCount[10];

public:
	monster_Test();
	~monster_Test();

	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timeDelta);

	virtual void Scene_Render1();

	virtual void Scene_RenderSprite();

	void Light_Push();

	void Terrain_Init();
	void TestLand_Init();

	void Player_Init();
	void Player_Update(float timeDelta);
	void Player_Render();

	void Player_ATK_Init();
	void Player_ATK_Update(float timeDelta);

	void Monster_Init();
	void Monster_Update(float timeDelta);
	void Monster_Render();




};

