#pragma once
#include "cScene.h"
#include "cSetBoundObject.h"

class cTerrain;
class cMonster;
class cLight;

class cScene_BoundBoxTool : public cScene
{
private:
	cTerrain*			m_pTerrain;
	cMonster*			m_pMonster;


	//보정 행렬 변수
	D3DXVECTOR3			vecScale;
	D3DXVECTOR3			vecRotate;

	
	cBaseObject*					selectObject;
	std::vector<cBaseObject*>		objects;

	cSetBoundObject*				selectBound;
	std::vector<cSetBoundObject*>	boundObjects;

	std::vector<cLight*>	lights;

public:
	cScene_BoundBoxTool();
	~cScene_BoundBoxTool();

	HRESULT Scene_Init();

	void Scene_Release();

	void Scene_Update(float timeDelta);

	void Scene_Render1();

	void KeyControl(float timeDelta);
};

