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

	//������Ʈ�� �޾��ش�.
	cInputHandler*		m_pInput;

public:
	cPlayer();
	~cPlayer();

	void BaseObjectEnable();
	void BaseObjectUpdate(float timeDelta);			//BaseObject �� Update �� ����....
	void BaseObjectRender();

	void SetCamera(cCamera* camera) { m_camera = camera; }
};

