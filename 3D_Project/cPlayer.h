#pragma once
#include "cBaseObject.h"
#include "cTestCommand.h"
#include "cTestCommand2.h"
#include "moveClass.h"


class cTerrain;
class cCamera;
class cInputHandler;

class cPlayer : public cBaseObject 
{
private:
	cCamera*			m_camera;


	//웨이 포인트
	int						m_nIndex;
	bool					m_bMove;
	vector<D3DXVECTOR3>				m_vWayPoint;
	vector<D3DXVECTOR3>::iterator	m_viWayPoint;

	//컴포넌트를 달아준다.
	cInputHandler*		m_pInput;

public:
	cPlayer();
	~cPlayer();

	void BaseObjectEnable();
	void BaseObjectUpdate(float timeDelta);			//BaseObject 가 Update 때 실행....
	void BaseObjectRender();
	
	void KeyControl(float timeDelta);
	void MovePoint(float timeDelta);


	void SetCamera(cCamera* camera) { m_camera = camera; }
};

