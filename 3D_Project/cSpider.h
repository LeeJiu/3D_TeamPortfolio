#pragma once
#include "cMonster.h"

class cSpider : public cMonster
{
private:
	float			m_fRange2;
	bool			m_bHit;

	float			m_fAtkTime;
	float			m_fDeadTime;

public:
	cSpider();
	~cSpider();

	void BaseObjectEnable();
	void BaseObjectUpdate(float timeDelta);			//BaseObject �� Update �� ����....
	void BaseObjectBoundBox();
	void BaseObjectRender();

	void Attack01(float timeDelta);
	void Damage(float fDamage);
	void SetAniState();

	void SetPlayer(cPlayer* pPlayer) { m_pPlayer = pPlayer; }
};

