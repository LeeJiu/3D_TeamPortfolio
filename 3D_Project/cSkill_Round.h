#pragma once
#include "cBaseObject.h"
#include "cPartcleEmitter.h"
#include "cQuadParticleEmitter.h"



class cSkill_Round : public cBaseObject
{
protected:

	bool               m_IsSelect;         // 스킬 마우스 오버중이니
	bool               m_IsCasting;        // 스킬 캐스팅 중이니
	bool               m_IsAttacking;      // 스킬 공격 중이니
	bool               m_IsCoolTime;       // 스킬 쿨타임 중이니


	int                   m_CastTimeCount; //캐스팅 재는 타임
	int                   m_CastTime;      //캐스팅 풀 타임

	int                   m_CoolTimeCount; //쿨타임 잰다
	int                   m_CoolTime;      //쿨타임

	int                   m_AttackingCount; //공격 시전시간을 잰다
	int                   m_AttackingTime;

	float                 m_CastEfcScale;



	cQuadParticleEmitter*   m_CircleEfc;     //파란 범위 
	cQuadParticleEmitter*   m_CastEfc;       //빨간 범위
	cQuadParticleEmitter*   m_SurroundEfc;   //사거리 범위
	int                     m_MaxDistance; //최대 사거리

	D3DXVECTOR3             m_MousePos;
	D3DXVECTOR3             m_CasterWorldPos; //시전자의 위치
	D3DXVECTOR3             m_AttackPos;       //공격하는 범위의 포지션
	float                   m_SurroundLength; //범위


	cBoundSphere     m_BoundSphere;







public:
	cSkill_Round();
	~cSkill_Round();

	void BaseObjectEnable(D3DXVECTOR3  casterWorldPos, float surroundLength, int maxDistance, int castTime, int attackingTime, int coolTime);

	void BaseObjectUpdate(float timeDelta, D3DXVECTOR3 casterWorldPos, D3DXVECTOR3 mousePos);

	void BaseObjectRender();

	void SelectSkill(); //UI에 스킬을 마우스 오버 했을때 불러주자

	void StartCasting(); //스킬을 사용한다 즉시시전 스킬도 이 함수를 불러주자

	int  GetCastCount()   { return m_CastTimeCount; } //시전시작시 모션을 지정해줘야할 경우 가져가주자
	int  GetAtkCount()   { return m_AttackingCount; }
	bool GetIsSelecting() { return m_IsSelect; } //선택중이니?
	bool GetIsAttacking() { return m_IsAttacking; } //공격하고있니?


protected:
	//이펙트 함수가 필요하면..

	virtual void Effect_Init() {};
	virtual void Effect_Update(float timeDelta) {};
	virtual void Effect_Render() {};

};



