#pragma once
#include "cScene.h"
#include "cMonster.h"
#include "cSetBoundObject.h"


class cScene_testMonster : public cScene
{
private:
	cTerrain*					m_pTerrain;
	cMonster*					m_pMonster;

	//임시로 바운드 박스들을 설치할 변수
	cSetBoundObject*				selectBound;
	std::vector<cSetBoundObject*>	boundObjects;

	std::vector<cLight*>		lights;

public:
	cScene_testMonster();
	~cScene_testMonster();

	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timeDelta);

	virtual void Scene_Render1();
};

