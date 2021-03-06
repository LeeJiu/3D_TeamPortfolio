#pragma once
#include "cScene.h"
#include "cMonsterManager.h"
#include "cBerserker.h"

class cBaseObject;
class cCamera;

class cDragonTest : public cScene
{
	std::vector<cMonster*>				vMonsters;
	std::vector<cMonster*>::iterator	viMonsters;
private:
	cTerrain*				m_pTerrain;
	cPlayer*				pBerserker;

	cMonsterManager*		m_pMonMgr;
	cTransform*				pTransForCamera;		//카메라용

	// 도형 피킹에 쓸것.
	Ray						cRay; //케릭터에 들어갈 레이.
	bool                    objectHit;

	// 움직임에 써볼것.
	bool isMove;
	bool isObject;
	bool isTerrain;
	bool isClick;

	bool isCharView, isAltView;		//카메라용
	std::vector<cLight*>	lights;

	bool			m_bMove;
	cBaseObject*	m_Land;			//컬링된 오브젝트

	D3DXMATRIXA16 temp;


public:
	cDragonTest(void);
	~cDragonTest(void);

	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timeDelta);

	virtual void Scene_Render1();

	virtual void Scene_RenderSprite();

};




