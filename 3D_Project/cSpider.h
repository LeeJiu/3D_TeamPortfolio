#pragma once
#include "cMonster.h"

class cSpider : public cMonster
{
private:


public:
	cSpider(float fHP, float fRange);
	~cSpider();

	void BaseObjectEnable();
	void BaseObjectUpdate(float timeDelta);			//BaseObject �� Update �� ����....
	void BaseObjectBoundBox();

	void Attack01();
	void Damage(float fDamage);

	void SetPlayer(cBaseObject* pPlayer) { m_pPlayer = pPlayer; }
};

