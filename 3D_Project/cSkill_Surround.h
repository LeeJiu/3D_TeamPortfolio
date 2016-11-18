#pragma once
#include "cBaseObject.h"

class cSkill_Surround : cBaseObject
{
private:

	cTransform*      m_CasterPos;       //�������� ��ġ
	float        m_SurroundRadius;  //���� ����
	D3DXVECTOR3      m_CasterWorldPos;

	// int              m_HitMax;          //Ÿ���ο�
	float            m_tickTime;
	float            m_timeTemp;

	int              m_Damage;
	int              m_UseSP;


	int              m_CoolTime;
	int              m_CastTime;
	int              m_ActionTime;


	bool             m_UseSkill;           //��ų�� ����Ѵ�
	bool             m_IsCasting;          //��ų�� ĳ���� ���̳�
	bool             m_IsAction;           //��ų�� �������̴�

	bool             m_IsHit;              //���� �¾Ҵ�?


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

