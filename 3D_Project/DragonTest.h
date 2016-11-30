#pragma once
#include "cScene.h"
#include "cMonsterManager.h"
#include "cBerserker.h"
#include "cUI_Container.h"

class cBaseObject;
class cCamera;

class DragonTest : public cScene
{
	std::vector<cMonster*>				vMonsters;
	std::vector<cMonster*>::iterator	viMonsters;
	std::vector<cLight*>				extraLights;			//�߰� ������

	std::vector<cBaseObject*>			m_vObject;
	std::vector<cBaseObject*>			m_vBoundBox;

	std::vector<cBaseObject*>			m_vRender;
	std::vector<cBaseObject*>			m_vCulling;

private:
	cTerrain*				m_pTerrain;
	cPlayer*				pBerserker;

	cMonsterManager*		m_pMonMgr;
	cTransform*				pTransForCamera;		//ī�޶��
	

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

	cBaseObject*    castle;

	D3DXMATRIXA16 temp;
public:
	DragonTest(void);
	~DragonTest(void);

	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timeDelta);

	virtual void Scene_Render1();

	virtual void Scene_RenderSprite();
	virtual void Scene_FontSprite();

};




