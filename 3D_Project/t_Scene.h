#pragma once
#include "cScene.h"

enum c_STATE {
	IDLE,
	WALK
};

class cBaseObject;
class cCamera;
class cTerrain;
class cSkinnedAnimation;

class t_Scene : public cScene
{
private:
	cSkinnedAnimation*		pSkinned1;
	cTransform*				pSkinnedTrans;

	std::vector<cLight*>	lights;

	cTerrain*		m_pTerrain;
	D3DXVECTOR3		m_hitPos;
	D3DXVECTOR3		m_hitDir;
	bool			m_bMove;

	float			m_time;
	cBaseObject*	m_Land;			//컬링된 오브젝트
	
	D3DXMATRIXA16 temp;

	c_STATE			m_state;


public:
	t_Scene(void);
	~t_Scene(void);


	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timeDelta);

	virtual void Scene_Render1();

	virtual void Scene_RenderSprite();


};

