#pragma once
#include "cBaseObject.h"

class cWayPoint;

class cMonster : public cBaseObject
{
private:
	cWayPoint*		m_pWayPoint;

public:
	cMonster();
	~cMonster();

	void BaseObjectEnable();
	void BaseObjectUpdate(float timeDelta);			//BaseObject �� Update �� ����....

	void BaseObjectBoundBox();
};

