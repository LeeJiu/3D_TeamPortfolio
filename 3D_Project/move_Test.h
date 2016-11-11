
#pragma once
#include "cScene.h"

class cBaseObject;
class cCamera;
class cTerrain;
class cSkinnedAnimation;

class move_Test : public cScene
{
private:

	cSkinnedAnimation*		pSkinned1;
	cBoundBox*              pSkinnedBox;
	cTransform*				pSkinnedTrans;
	//
	cTransform*             colliTest;
	cBoundBox*              testBox;

	D3DXVECTOR3             quad[6];

	// 도형 피킹에 쓸것.
	Ray						cRay; //케릭터에 들어갈 레이.
	Ray						frontRay; //케릭터에 들어갈 레이.

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

	
	std::vector<cLight*>	lights;

	cTerrain*		m_pTerrain;
	D3DXVECTOR3		m_hitPos;


	D3DXVECTOR3		m_hitDir;
	bool			m_bMove;

	cBaseObject*	m_Land;			//컬링된 오브젝트

	D3DXMATRIXA16 temp;

	bool boundHit;

public:
	move_Test(void);
	~move_Test(void);


	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timeDelta);

	virtual void Scene_Render1();

	virtual void Scene_RenderSprite();

	//==== 나의 quad 벡터 , 행 , 렬 , 나의 트렌스 , 생성할 좌표.
	void createQuad(D3DXVECTOR3* quad,float row,float col,cTransform* myTrans,D3DXVECTOR3* createPos);

	void QuadRender();
	
	//GIZMO_MGR->Line(startPos, finalPos, 0xff00ff00);
	//GIZMO_MGR->Line(startPos, finalPos2, 0xff00ff00);
};

