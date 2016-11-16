#pragma once
#include "cBaseObject.h"

class cWayPoint;
class cBaseObject;

class cMonster : public cBaseObject
{
protected:
	cWayPoint*		m_pWayPoint;
	cBaseObject*	m_pPlayer;

	std::vector<cBaseObject*>		m_vObjects;
	
	float			m_fHP;
	float			m_fRange;
	ACTOR_STATE		m_state;
	string			m_strName;

public:
	cMonster();
	virtual ~cMonster();

	virtual void BaseObjectEnable();
	virtual void BaseObjectUpdate(float timeDelta);			//BaseObject 가 Update 때 실행....
	virtual void BaseObjectBoundBox();

	virtual void MoveToPlayer();
	virtual void Attack01() = 0;
	virtual void Damage(float fDamage) = 0;

	virtual void SetPlayer(cBaseObject* pPlayer) { m_pPlayer = pPlayer; }
	virtual void SetBoundObjects(vector<cBaseObject*> vObjects) { m_vObjects = vObjects; }
};

