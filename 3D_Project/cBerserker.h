#pragma once
#include "cPlayer.h"

#define CONTROL_KEY 5

class cBerserker : public cPlayer
{
private:
	//스킬
	int					m_atkCnt;		//평타단계 수
	float				m_time;			//커맨드체크할 타이머
	float				m_fadeOut;		//애니 끝나는시간

	//스킬3 
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

	void SKILL01();			//평타
	void SKILL02();			//내려찍기	(타겟, 범위기)
	void SKILL03();			//휠윈드 (원형 범위기)
	void SKILL04();			//버프기
};

