#pragma once
#include "cMonster.h"

class cSpider : public cMonster
{
private:
	float			m_fRange2;
	float			m_damage;

public:
	cSpider();
	~cSpider();

	void BaseObjectEnable();
	void BaseObjectUpdate(float timeDelta);			//BaseObject 가 Update 때 실행....
	void BaseObjectBoundBox();
	void BaseObjectRender();

	void Attack01(float timeDelta);
	void Damage(float fDamage);
	void SetAniState();

	void Alert();
	void RangeIn(float timeDelta);
	void RangeOut();

	void SetPlayer(cPlayer* pPlayer) { m_pPlayer = pPlayer; }
};

