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
	
	cBaseObject*		object;
	cBaseObject*		object2;
	cXMesh_Static*		selectObject;
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

