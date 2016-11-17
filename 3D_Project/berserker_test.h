#pragma once
#include "cScene.h"

class cBaseObject;
class cCamera;
class cTerrain;
class cSkinnedAnimation;
class cPlayer;
class cBerserker;
class cMonster;
class cSpider;

class berserker_test : public cScene
{
	std::vector<cMonster*>				vMonsters;
	std::vector<cMonster*>::iterator	viMonsters;
private:
	cBerserker*				pBerserker;
	cMonster*				pGriff;

	cTransform*				pTransForCamera;		//카메라용

													// 도형 피킹에 쓸것.
	Ray						cRay; //케릭터에 들어갈 레이.
	bool                    objectHit;

	// 움직임에 써볼것.
	D3DXVECTOR3		m_currentPos;// 내 케릭터의 위치
	bool isMove;
	bool isObject;
	bool isTerrain;
	bool isClick;

	bool isCharView, isAltView;		//카메라용

	std::vector<cLight*>	lights;

	cTerrain*		m_pTerrain;
	bool			m_bMove;

	cBaseObject*	m_Land;			//컬링된 오브젝트

	D3DXMATRIXA16 temp;


public:
	berserker_test(void);
	~berserker_test(void);

	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timeDelta);

	virtual void Scene_Render1();

	virtual void Scene_RenderSprite();

};




