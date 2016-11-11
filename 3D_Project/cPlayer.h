#pragma once
#include "cBaseObject.h"
#include "cTestCommand.h"
#include "cTestCommand2.h"


class cTerrain;
class cCamera;
class cInputHandler;

class cPlayer : public cBaseObject 
{
private:
	cCamera*			m_camera;

	//컴포넌트를 달아준다.
	cInputHandler*		m_pInput;

public:
	cPlayer();
	~cPlayer();

	void BaseObjectEnable();
	void BaseObjectUpdate(float timeDelta);			//BaseObject 가 Update 때 실행....
	void BaseObjectRender();

	void SetCamera(cCamera* camera) { m_camera = camera; }
};

