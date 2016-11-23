#pragma once
#include "cScene.h"
#include "cMonsterManager.h"
#include "cMage.h"

class cBaseObject;
class cCamera;
class cPet;



class mage_Test : public cScene
{
	std::vector<cMonster*>				vMonsters;
	std::vector<cMonster*>::iterator	viMonsters;

private:
	cTerrain*		m_pTerrain;
	cPlayer*	    pMage;

	cMonsterManager*		m_pMonMgr;
	cTransform*				pTransForCamera;		//ī�޶��

	cPet*                   pPet;


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
	mage_Test(void);
	~mage_Test(void);


	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timeDelta);

	virtual void Scene_Render1();

	virtual void Scene_RenderSprite();

};



