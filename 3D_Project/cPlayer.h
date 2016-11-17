#pragma once
#include "cBaseObject.h"

class cTerrain;
class cCamera;
class cMonsterManager;
class cWeapon;
class cMonster;

class cPlayer : public cBaseObject 
{
protected:
	vector<cMonster*>				m_vMonster;
	vector<cMonster*>::iterator		m_viMonster;

	cCamera*			m_camera;
	cWeapon*			m_Weapon;
	cMonster*			m_target;			//타겟몬스터 

	cMonsterManager*	m_pMonMgr;

public:
	cPlayer();
	virtual ~cPlayer();

	virtual void BaseObjectEnable();
	virtual void BaseObjectUpdate(float timeDelta);			//BaseObject 가 Update 때 실행....
	virtual void BaseObjectRender();

	virtual void Monster_pick();
	virtual bool LengthCheck();

	virtual void Attack01() = 0;
	virtual void Attack02() = 0;
	virtual void Attack03() = 0;
	virtual void Damage(float damage) = 0;

	virtual void SetCamera(cCamera* camera) { m_camera = camera; }
	virtual void SetMonsterManager(cMonsterManager* pMonMgr) { m_pMonMgr = pMonMgr; }
};

