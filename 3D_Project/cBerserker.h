#pragma once
#include "cPlayer.h"
#include "moveClass.h"

#define CONTROL_KEY 5

class cBerserker : public cPlayer
{
private:
	ACTOR_STATE			m_state;
	std::string			m_strName;
	std::map<int, bool> m_InputKeys;
	bool				m_isMove;

	//컴포넌트를 달아준다.
	moveClass*			m_pMove;
	D3DXVECTOR3			m_mousePos;

	//스킬
	bool				m_isAttack;

	int					m_atkCnt;		//평타단계 수
	float				m_time;			//커맨드체크할 타이머
	float				m_fadeOut;		//애니 끝나는시간


	//status
	float				m_fHP;
	float				m_sp;
	float				m_attackLength;//공격가능범위
	int					m_damage;

	float				m_testtime;		//로그찎는용 타이머

public:
	cBerserker();
	~cBerserker();

	void BaseObjectEnable();
	void BaseObjectUpdate(float timeDelta);			//BaseObject 가 Update 때 실행....
	void BaseObjectRender();

	//void SetMonsters(std::vector<cMonster*>	vmon) { m_Vmon = vmon; }

private:
	void Damage(float damage);
	bool LengthCheck();

	void Attack01();
	void Attack02();
	void Attack03();
};

