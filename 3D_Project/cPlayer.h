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
	cTerrain*	m_pTerrain;

	cCamera*	m_camera;

	cInputHandler*		m_pInput;


public:
	cPlayer();
	~cPlayer();

	void BaseObjectUpdate(float timeDelta);			//BaseObject 가 Update 때 실행....
	
	void SetCamera(cCamera* camera) { m_camera = camera; }
	void SetTerrain(cTerrain* terrain) { m_pTerrain = terrain; }
};

