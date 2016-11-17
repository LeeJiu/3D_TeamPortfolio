#pragma once
#include "cScene.h"
#include "cSetBoundObject.h"

class cTerrain;
class cLight;

class cScene_BoundBoxTool : public cScene
{
private:
	cTerrain*			m_pTerrain;
	
	cBaseObject*					m_pSelectObject;
	std::vector<cBaseObject*>		objects;
	vector<cBaseObject*>::iterator	m_viObjects;

	cSetBoundObject*				selectBound;
	std::vector<cSetBoundObject*>	boundObjects;

	std::vector<cLight*>	lights;

	cXMesh*		m_pMesh;

	bool		m_bSelectObj;

public:
	cScene_BoundBoxTool();
	~cScene_BoundBoxTool();

	HRESULT Scene_Init();

	void Scene_Release();

	void Scene_Update(float timeDelta);

	void Scene_Render1();

	void KeyControl(float timeDelta);
	void SetObjects();
	void SelectObject();
	void DeleteObject();
	
	void SelectObjMesh(OBJECT_TYPE type);
	void SelectMonMesh(MONSTER_TYPE type);

	void SaveObjects();
	void LoadObjects();


};

