#pragma once
#include "cscene.h"

class cBaseObject;
class cCamera;
class cTerrain;
class cSkinnedAnimation;

class t_Scene : public cScene
{
private:

	cBaseObject*						object;




public:
	t_Scene(void);
	~t_Scene(void);


	virtual HRESULT Scene_Init();

	virtual void Scene_Release();

	virtual void Scene_Update(float timeDelta);

	virtual void Scene_Render1();

	virtual void Scene_RenderSprite();


};

