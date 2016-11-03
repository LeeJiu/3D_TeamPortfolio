
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
	cTransform*				pSkinnedTrans;
	// ���� ��ŷ�� ����.
	Ray                   cRay; //�ɸ��Ϳ� �� ����.
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


public:
	move_Test(void);
	~move_Test(void);


	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timeDelta);

	virtual void Scene_Render1();

	virtual void Scene_RenderSprite();


};

