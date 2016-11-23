#pragma once
#include "cScene.h"
#include "cMonsterManager.h"
#include "cBerserker.h"

class cBaseObject;
class cCamera;

class DragonTest : public cScene
{
	std::vector<cMonster*>				vMonsters;
	std::vector<cMonster*>::iterator	viMonsters;
private:
	cTerrain*				m_pTerrain;
	cPlayer*				pBerserker;

	cMonsterManager*		m_pMonMgr;
	cTransform*				pTransForCamera;		//ī�޶��

	// ���� ��ŷ�� ����.
	Ray						cRay; //�ɸ��Ϳ� �� ����.
	bool                    objectHit;

	// �����ӿ� �Ẽ��.
	bool isMove;
	bool isObject;
	bool isTerrain;
	bool isClick;

	bool isCharView, isAltView;		//ī�޶��
	std::vector<cLight*>	lights;

	bool			m_bMove;
	cBaseObject*	m_Land;			//�ø��� ������Ʈ

	D3DXMATRIXA16 temp;


public:
	DragonTest(void);
	~DragonTest(void);

	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timeDelta);

	virtual void Scene_Render1();

	virtual void Scene_RenderSprite();

};




