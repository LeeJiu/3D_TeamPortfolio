#pragma once
#include "cPlayer.h"
#include "cSkill_Swing.h"
#include "cSkill_Howling.h"
#include "cSkill_Burserk.h"
#include "cTickFunc.h"

#define CONTROL_KEY 5
#define TICKMAX 3

enum BK_SKILL //틱 클래스에서 쓸꺼. 
{
	BK_HOWL, BK_SWING, BK_ACCEL
};

class cShowDamage;

class cBerserker : public cPlayer
{
private:
	cShowDamage*		m_ShowDamage;
	cSkill_Surround*    m_pSurroundSkill;	//주변범위
	
	cTickFunc*			m_tick[TICKMAX];	//틱데미쥐

	//스킬
	int					m_atkCnt;		//평타단계 수
	int					m_aniCount;		//애니메이션 카운터
	float				m_time;			//커맨드체크할 타이머
	float				m_fadeOut;		//애니 끝나는시간

	//스킬2
	cSkill_Howling*		m_Howling;		//하울링

	//스킬3 
	cSkill_Swing*		m_Swing;		//스윙스킬

	//스킬5
	cSkill_Burserk*		m_Burserk;		//버서크모드

	int					m_SwingCnt;

	float				m_testtime;		//로그찎는용 타이머

public:
	cBerserker();
	~cBerserker();

	void BaseObjectEnable();
	void BaseObjectUpdate(float timeDelta);			//BaseObject 가 Update 때 실행....
	void BaseObjectRender();
	void BaseSpriteRender();
	void BaseObjectBoundBox();

private:
	void Damage(float damage);

	void Attack01();
	void Attack02();
	void Attack03();

	void SkillInit();

	void SKILL01();			//평타
	void SKILL02();			//내려찍기	(타겟, 범위기)
	void SKILL03();			//휠윈드 (원형 범위기)
	void SKILL04();			//버프기

	void BasixWeaponSet();
	void SetTickCount();
	void UiUpdate(float timeDelta, cCamera* camera);		//버서커유아이
};

