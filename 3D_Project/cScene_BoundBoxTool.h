#pragma once
#include "cScene.h"


class cTerrain;
class cLight;
class cSetBoundObject;
class cMonster;


class cScene_BoundBoxTool : public cScene
{
private:
	cTerrain*			m_pTerrain;
	
	cBaseObject*							m_pSelectObject;
	std::vector<cBaseObject*>				m_vObjects;
	std::vector<cBaseObject*>::iterator		m_viObjects;

	cSetBoundObject*				selectBound;
	std::vector<cSetBoundObject*>	boundObjects;

	cBaseObject*							m_pSelectMonster;
	std::vector<cBaseObject*>				m_vMonsters;
	std::vector<cBaseObject*>::iterator		m_viMonsters;

	std::vector<cLight*>	lights;

	cXMesh*		m_pMesh;

	bool		m_bSelectObj;
	bool		m_bSelectMon;

	bool		m_bSwapSelection;

public:
	cScene_BoundBoxTool();
	~cScene_BoundBoxTool();

	HRESULT Scene_Init();

	void Scene_Release();

	void Scene_Update(float timeDelta);

	void Scene_Render1();

	void KeyControl(float timeDelta);
	void ControlObjects(float timeDelta);
	void ControlMonsters(float timeDelta);

	void SetObjects();
	void SelectObject();
	void DeleteObject();
	
	void SetMonsters();
	void SelectMonster();
	void DeleteMonster();

	void SelectObjMesh(OBJECT_TYPE type);
	void SelectMonMesh(MONSTER_TYPE type);

	void SaveObjects();
	void LoadObjects();

	void SaveMonsters();
	void LoadMonsters();
};

