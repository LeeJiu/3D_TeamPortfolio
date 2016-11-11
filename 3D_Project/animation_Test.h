#pragma once
#include "cScene.h"

class cBaseObject;
class cCamera;
class cTerrain;
class cSkinnedAnimation;
class cPlayer;
class cMage;

class animation_Test : public cScene
{
private:

	cSkinnedAnimation*		pSkinned1;
	cPlayer*				pPlayer;
	cMage*					pMage;
	cTransform*				pSkinnedTrans;
	cTransform*				pTransForCamera;		//카메라용

													// 도형 피킹에 쓸것.
	Ray						cRay; //케릭터에 들어갈 레이.
	bool                    objectHit;

	// 움직임에 써볼것.
	D3DXVECTOR3		m_currentPos;// 내 케릭터의 위치
	D3DXVECTOR3		m_prePos;// 내가 갈곳의 위치
	D3DXVECTOR3		m_lastPos;// 가장 높은 y값을 반환 시킬떄 쓸놈.
	D3DXVECTOR3		m_mousePos;// 클릭했을때 위치.

	bool isMove;
	bool isObject;
	bool isTerrain;
	bool isClick;


	bool isCharView, isAltView;		//카메라용

	ACTOR_STATE current_State;
	ACTOR_STATE m_state;
	std::string current_Ani;


	std::vector<cLight*>	lights;

	cTerrain*		m_pTerrain;
	D3DXVECTOR3		m_hitPos;


	D3DXVECTOR3		m_hitDir;
	bool			m_bMove;

	cBaseObject*	m_Land;			//컬링된 오브젝트

	D3DXMATRIXA16 temp;


public:
	animation_Test(void);
	~animation_Test(void);


	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timeDelta);

	virtual void Scene_Render1();

	virtual void Scene_RenderSprite();


};

