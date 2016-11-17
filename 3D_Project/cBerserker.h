#pragma once
#include "cBaseObject.h"
#include "moveClass.h"

#define CONTROL_KEY 5

class cTerrain;
class cCamera;
class cInputHandler;
class cWeapon;
class cMonster;

class cBerserker : public cBaseObject
{
private:
	std::vector<cMonster*>			 m_Vmon;
	std::vector<cMonster*>::iterator m_VmonIter;

private:
	cCamera*			m_camera;
	cWeapon*			m_Weapon;

	cBoundBox*          m_ATKBox;
	cTransform*         m_ATKBoxTrans;

	ACTOR_STATE			m_state;
	std::string			m_Aniname;
	std::map<int, bool> m_InputKeys;
	bool				m_isMove;

	//컴포넌트를 달아준다.
	cInputHandler*		m_pInput;
	moveClass*			m_pMove;
	D3DXVECTOR3			m_mousePos;

	//스킬
	bool				m_isAttack;

	int					m_atkCnt;		//평타단계 수
	float				m_time;			//커맨드체크할 타이머
	float				m_fadeOut;		//애니 끝나는시간

	cMonster*			m_target;

	//status
	float				m_hp;
	float				m_sp;
	float				m_attackLength;//공격가능범위
	int					m_damage;

	float				m_testtime;		//로그찎는용 타이머

public:
	cBerserker();
	~cBerserker();

	void BaseObjectEnable();
	void BaseObjectUpdate(float timeDelta);			//BaseObject 가 Update 때 실행....
	void ATKBoxRender();
	void WeaponRender();

	void SetCamera(cCamera* camera) { m_camera = camera; }
	void SetMonsters(std::vector<cMonster*>	vmon) { m_Vmon = vmon; }

	cBoundBox* GetATKBox() { return m_ATKBox; }
	cTransform* GetATKBoxTrans() { return m_ATKBoxTrans; }

private:
	void Monster_pick();
	void GetDamaged();

	bool LengthCheck();
	void Attac_first();
	void Attac_second();
	void Attac_third();
};

