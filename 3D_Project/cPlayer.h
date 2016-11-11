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


	//���� ����Ʈ
	int						m_nIndex;
	bool					m_bMove;
	vector<D3DXVECTOR3>				m_vWayPoint;
	vector<D3DXVECTOR3>::iterator	m_viWayPoint;

	//������Ʈ�� �޾��ش�.
	cInputHandler*		m_pInput;

public:
	cPlayer();
	~cPlayer();

	void BaseObjectEnable();
	void BaseObjectUpdate(float timeDelta);			//BaseObject �� Update �� ����....
	void BaseObjectRender();
	
	void KeyControl(float timeDelta);
	void MovePoint(float timeDelta);


	void SetCamera(cCamera* camera) { m_camera = camera; }
};

