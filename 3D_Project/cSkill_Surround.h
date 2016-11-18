#pragma once
#include "cBaseObject.h"

class cSkill_Surround : cBaseObject
{
private:

	cTransform*      m_CasterPos;       //시전자의 위치
	float        m_SurroundRadius;  //시전 범위
	D3DXVECTOR3      m_CasterWorldPos;

	// int              m_HitMax;          //타격인원
	float            m_tickTime;
	float            m_timeTemp;

	int              m_Damage;
	int              m_UseSP;


	int              m_CoolTime;
	int              m_CastTime;
	int              m_ActionTime;


	bool             m_UseSkill;           //스킬을 사용한다
	bool             m_IsCasting;          //스킬이 캐스팅 중이냐
	bool             m_IsAction;           //스킬이 시전중이니

	bool             m_IsHit;              //적이 맞았니?


public:
	cSkill_Surround();
	~cSkill_Surround();

	void BaseObjectEnable();

	void SkillInit(
		D3DXVECTOR3      casterWorldPos,
		float            surroundRadius,
		int              hitMax,
		int              damage,
		int              useSP,
		int              coolTime,
		int              castTime,
		int              actionTime
		);

	void SkillUpdate(float timeDelta);

	//cBoundSphere* GetBoundSphere() { return m_BoundSphere; }
	bool GetUseSkill() { return m_UseSkill; }
	bool GetIsCasting() { return m_IsCasting; }
	bool GetIsAction() { return m_IsAction; }
	bool GetIsHit() { return m_IsHit; }




};

