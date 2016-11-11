
#pragma once
#include "cScene.h"
#include "moveClass.h"

class cBaseObject;
class cCamera;
class cTerrain;
class cSkinnedAnimation;
class moveClass;

class move_Test2 : public cScene
{
private:

	cSkinnedAnimation*		pSkinned1;
	cTransform*				pSkinnedTrans;
	cBoundBox*              pSkinnedBound;
	// 도형 피킹에 쓸것.
	Ray						cRay; //케릭터에 들어갈 레이.
	bool                    objectHit;

	bool isObject;
	bool isTerrain;
	bool isClick;


	std::vector<cLight*>	lights;

	cTerrain*		m_pTerrain;
	D3DXVECTOR3		m_hitPos;


	D3DXVECTOR3		m_hitDir;
	bool			m_bMove;

	cBaseObject*	m_Land;			//컬링된 오브젝트

	D3DXMATRIXA16 temp;

	moveClass* move;

	cTransform*				collTrans;
	cBoundBox*              collBox;

public:
	move_Test2(void);
	~move_Test2(void);


	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timeDelta);

	virtual void Scene_Render1();

	virtual void Scene_RenderSprite();


};

