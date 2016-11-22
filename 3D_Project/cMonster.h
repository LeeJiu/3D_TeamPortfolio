#pragma once
#include "cBaseObject.h"

class cWayPoint;
class cPlayer;


class cMonster : public cBaseObject
{
protected:
	cWayPoint*		m_pWayPoint;
	cPlayer*		m_pPlayer;

	std::vector<cBaseObject*>		m_vObjects;
	
	float			m_fHP;
	float			m_fRange;
	ACTOR_STATE		m_state;
	string			m_strName;

	bool			m_inRange;

public:
	cMonster();
	virtual ~cMonster();

	virtual void BaseObjectEnable();
	virtual void BaseObjectUpdate(float timeDelta);			//BaseObject 가 Update 때 실행....
	virtual void BaseObjectBoundBox();
	virtual void BaseObjectRender();

	virtual void MoveToPlayer();
	virtual void Attack01() {};
	virtual void Damage(float fDamage) = 0;

	virtual bool GetInRange() { return m_inRange; }

	virtual void SetPlayer(cPlayer* pPlayer) { m_pPlayer = pPlayer; }
	virtual void SetBoundObjects(vector<cBaseObject*> vObjects) { m_vObjects = vObjects; }
	virtual void SetInRange(bool check) { m_inRange = check; }


};

