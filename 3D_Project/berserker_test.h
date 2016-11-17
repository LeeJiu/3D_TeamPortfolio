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

	cTransform*				pTransForCamera;		//ī�޶��

													// ���� ��ŷ�� ����.
	Ray						cRay; //�ɸ��Ϳ� �� ����.
	bool                    objectHit;

	// �����ӿ� �Ẽ��.
	D3DXVECTOR3		m_currentPos;// �� �ɸ����� ��ġ
	bool isMove;
	bool isObject;
	bool isTerrain;
	bool isClick;

	bool isCharView, isAltView;		//ī�޶��

	std::vector<cLight*>	lights;

	cTerrain*		m_pTerrain;
	bool			m_bMove;

	cBaseObject*	m_Land;			//�ø��� ������Ʈ

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




