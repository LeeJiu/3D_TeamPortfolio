
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

	// ���� ��ŷ�� ����.
	Ray						cRay; //�ɸ��Ϳ� �� ����.
	Ray						frontRay; //�ɸ��Ϳ� �� ����.

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

	
	std::vector<cLight*>	lights;

	cTerrain*		m_pTerrain;
	D3DXVECTOR3		m_hitPos;


	D3DXVECTOR3		m_hitDir;
	bool			m_bMove;

	cBaseObject*	m_Land;			//�ø��� ������Ʈ

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

	//==== ���� quad ���� , �� , �� , ���� Ʈ���� , ������ ��ǥ.
	void createQuad(D3DXVECTOR3* quad,float row,float col,cTransform* myTrans,D3DXVECTOR3* createPos);

	void QuadRender();
	
	//GIZMO_MGR->Line(startPos, finalPos, 0xff00ff00);
	//GIZMO_MGR->Line(startPos, finalPos2, 0xff00ff00);
};

