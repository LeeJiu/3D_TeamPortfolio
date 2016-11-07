#pragma once
#include "cScene.h"

class cBaseObject;
class cCamera;
class cTerrain;
class cSkinnedAnimation;

class sector_Test : public cScene
{
private:
	cSkinnedAnimation*		pSkinned1;
	cSkinnedAnimation*		pSkinned2;
	cTransform*				pSkinnedTrans;
	cTransform*				pSkinnedTrans2;

	std::vector<cLight*>	lights;

	D3DXVECTOR3		m_hitPos;
	D3DXVECTOR3		m_hitDir;
	bool			m_bMove;

	float			m_time;

	D3DXMATRIXA16 temp;

	float			m_sight;
	float			m_sightLength;

	bool			m_crush;

public:
	sector_Test();
	~sector_Test();


	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timeDelta);

	virtual void Scene_Render1();

private:

	//bool	intersectSector(const cTransform* Trans1, const cTransform* Trans2, float length, float sight);
};


