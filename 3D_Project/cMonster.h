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

	float			m_fAtkTime;
	float			m_fDeadTime;

	bool			m_bHit;
	bool			m_bIsOverlap;
	bool			m_inRange;

	//몬스터의 어택용 트랜스와 바운드박스
	cTransform*		m_pHitTrans;
	cBoundBox		m_pHitBound;

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
	virtual ACTOR_STATE GetState() { return m_state; }
	//virtual cBoundBox GetBodyBound() { return BoundBox; }

	virtual void SetPlayer(cPlayer* pPlayer) { m_pPlayer = pPlayer; }
	virtual void SetBoundObjects(vector<cBaseObject*> vObjects) { m_vObjects = vObjects; }
	virtual void SetInRange(bool check) { m_inRange = check; }


};

