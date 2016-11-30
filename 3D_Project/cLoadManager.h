#pragma once
#include "cSingletonBase.h"
#include "cBaseObject.h"
#include "cXMesh.h"


class cLoadManager : public cSingletonBase<cLoadManager>
{
private:
	cXMesh*		m_pMesh;

public:
	cLoadManager();
	~cLoadManager();
	
	HRESULT Init();
	void Release();

	void LoadObjects(vector<cBaseObject*>* vObjects);
	void LoadBoundBox(vector<cBaseObject*>* vObjects);

	void SelectObjMesh(OBJECT_TYPE type);
};

#define LOAD_MGR cLoadManager::GetInstance()