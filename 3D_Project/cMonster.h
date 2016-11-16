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
	
	float			m_fHP;
	float			m_fRange;
	ACTOR_STATE		m_state;
	string			m_strName;

public:
	cMonster();
	~cMonster();

	void BaseObjectEnable();
	void BaseObjectUpdate(float timeDelta);			//BaseObject 가 Update 때 실행....
	void BaseObjectBoundBox();

	void MoveToPlayer();
	void Attack01();
	void Damage(float fDamage);

	void SetPlayerMemoryLink(cBaseObject* pPlayer) { m_pPlayer = pPlayer; }
	void SetBoundObjects(vector<cBaseObject*> vObjects) { m_vObjects = vObjects; }
};

