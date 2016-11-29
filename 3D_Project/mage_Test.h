#pragma once
#include "cScene.h"
#include "cMage.h"
#include "cMonsterManager.h"


class cBaseObject;
class cCamera;
class cPet;



class mage_Test : public cScene
{
private:

	cTerrain*		m_pTerrain;
	cPlayer*	    m_pPlayer;

	cMonsterManager*		m_pMonMgr;
	//cTransform*				pTransForCamera;		//카메라용

	cPet*                   pPet;

	std::vector<cLight*>	lights;

	//// 도형 피킹에 쓸것.
	//Ray						cRay; //케릭터에 들어갈 레이.
	//bool                    objectHit;
	//
	//// 움직임에 써볼것.
	//bool isMove;
	//bool isObject;
	//bool isTerrain;
	//bool isClick;
	//
	//
	//bool isCharView, isAltView;		//카메라용



	//bool			m_bMove;
	//cBaseObject*	m_Land;			//컬링된 오브젝트
	//
	//D3DXMATRIXA16 temp;



public:
	mage_Test(void);
	~mage_Test(void);


	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timeDelta);

	virtual void Scene_Render1();

	virtual void Scene_RenderSprite();

	virtual void Scene_RenderFont();
};



