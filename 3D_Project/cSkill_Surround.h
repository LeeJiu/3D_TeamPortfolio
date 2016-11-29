#pragma once
#include "cBaseObject.h"
#include "cPartcleEmitter.h"
#include "cQuadParticleEmitter.h"


class cSkill_Surround : public cBaseObject
{
public:
	int                   m_CastTimeCount; //캐스팅 재는 타임
	int                   m_CastTime;      //캐스팅 풀 타임

	int                   m_CoolTimeCount; //쿨타임 잰다
	int                   m_CoolTime;      //쿨타임

	int                   m_AttackingCount; //공격 시전시간을 잰다
	int                   m_AttackingTime;	//공격시간

protected:
	bool               m_IsSelect;       // 스킬 마우스 오버중이니
	bool               m_IsCasting;      // 스킬 캐스팅 중이니
	bool               m_IsAttacking;    // 스킬 공격 중이니
	bool               m_IsCoolTime;     // 스킬 쿨타임 중이니


	// 기본 마법진에 대한 초기화 

	cQuadParticleEmitter*   m_CircleEfc;
	cQuadParticleEmitter*   m_CastEfc;

	float                 m_CastEfcScale;

	cBoundSphere     m_BoundSphere;

	D3DXVECTOR3      m_CasterWorldPos; //시전자의 위치
	float            m_SurroundLength; //범위



public:
	cSkill_Surround();
	~cSkill_Surround();

	void BaseObjectEnable(D3DXVECTOR3  casterWorldPos, float surroundLength, int castTime, int attackingTime, int coolTime);

	void BaseObjectUpdate(float timeDelta, D3DXVECTOR3 CasterWorldPos);

	void BaseObjectRender();

	void SelectSkill(); //UI에 스킬을 마우스 오버 했을때 불러주자

	void StartCasting(); //스킬을 사용한다 즉시시전 스킬도 이 함수를 불러주자



	bool GetIsAttacking() { return m_IsAttacking; } //공격하고있니?
	bool GetIsCool() { return m_IsCoolTime; }

protected:
	//이펙트 함수가 필요하면..

	virtual void Effect_Init() {};
	virtual void Effect_Update(float timeDelta) {};
	virtual void Effect_Render() {};
};

