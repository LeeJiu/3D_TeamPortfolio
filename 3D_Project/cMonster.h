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
	void BaseObjectUpdate(float timeDelta);			//BaseObject 가 Update 때 실행....

	void BaseObjectBoundBox();
};

