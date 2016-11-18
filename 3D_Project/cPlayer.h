#pragma once
#include "cBaseObject.h"
#include "moveClass.h"

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

	ACTOR_STATE			m_state;
	std::string			m_strName;
	std::map<int, bool> m_InputKeys;

	moveClass*			m_pMove;
	cCamera*			m_camera;
	cWeapon*			m_Weapon;
	
	cMonster*			m_target;			//타겟몬스터 
	cMonsterManager*	m_pMonMgr;

	//status
	float				m_fHP;
	float				m_sp;
	float				m_attackLength;//공격가능범위
	int					m_damage;

	bool				m_isMove;
	bool				m_isAttack;
public:
	cPlayer();
	virtual ~cPlayer();

	virtual void BaseObjectEnable();
	virtual void BaseObjectUpdate(float timeDelta);			//BaseObject 가 Update 때 실행....
	virtual void BaseObjectRender();

	virtual void Move(float timeDelta);
	virtual void Monster_pick();

	virtual void Attack01() = 0;
	virtual void Attack02() = 0;
	virtual void Attack03() = 0;

	virtual void SKILL01() = 0;
	virtual void SKILL02() = 0;
	virtual void SKILL03() = 0;
	virtual void SKILL04() = 0;

	virtual void Damage(float damage) = 0;
	virtual bool LengthCheck();
	virtual void RangeCheck(float range);		//범위체크

	virtual void SetMoveKeys();
	
	virtual void SetCamera(cCamera* camera) { m_camera = camera; }
	virtual void SetMonsterManager(cMonsterManager* pMonMgr) { m_pMonMgr = pMonMgr; }
};

