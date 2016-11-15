#pragma once
#include "cBaseObject.h"

class cWayPoint;
class cBaseObject;

class cMonster : public cBaseObject
{
private:
	cWayPoint*		m_pWayPoint;
	cBaseObject*	m_pPlayer;

	std::vector<cBaseObject*>		m_vObjects;
	
	float			range;

public:
	cMonster();
	~cMonster();

	void BaseObjectEnable();
	void BaseObjectUpdate(float timeDelta);			//BaseObject 가 Update 때 실행....
	void BaseObjectBoundBox();

	void MoveToPlayer();

	void SetPlayerMemoryLink(cBaseObject* pPlayer) { m_pPlayer = pPlayer; }
	void SetBoundObjects(vector<cBaseObject*> vObjects) { m_vObjects = vObjects; }
};

