#pragma once
#include "cscene.h"

class cBaseObject;
class cCamera;

class cScene_00 : public cScene
{
private:
	std::vector<cBaseObject*>			renderObjects;			//씬에 배치된 랜더 오브젝트 배열
	std::vector<cBaseObject*>			cullObjects;			//컬링된 오브젝트
	

	






public:
	cScene_00(void);
	~cScene_00(void);


	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update( float timDelta );

	virtual void Scene_Render1();

	virtual void Scene_RenderSprite();


};

