#pragma once
#include "cBaseObject.h"
#include "cPartcleEmitter.h"
#include "cQuadParticleEmitter.h"



class cSkill_Front : public cBaseObject
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

	

	cQuadParticleEmitter*   m_CastEfc;       //선택 범위
	
	
	float                   m_MaxDistance;   //전방 사거리
	float                   m_MaxWidth;      //전방 폭

	D3DXVECTOR3             m_LookDir;          //바라보는 방향
	D3DXVECTOR3             m_CasterWorldPos;   //시전자의 위치
	D3DXVECTOR3             m_AttackPos;


	cBoundBox               m_BoundBox;


public:
	cSkill_Front();
	~cSkill_Front();



	void BaseObjectEnable(D3DXVECTOR3 casterWorldPos, float maxDistance, float maxWidth, int castTime, int attackingTime, int coolTime);

	void BaseObjectUpdate(float timeDelta, D3DXVECTOR3 casterWorldPos, D3DXVECTOR3 mousePos);

	void BaseObjectRender();

	void SelectSkill(); //UI에 스킬을 마우스 오버 했을때 불러주자

	void StartCasting(); //스킬을 사용한다 즉시시전 스킬도 이 함수를 불러주자


	bool GetIsSelecting() { return m_IsSelect; } //선택중이니?
	bool GetIsAttacking() { return m_IsAttacking; } //공격하고있니?

protected:
	//이펙트 함수가 필요하면..

	virtual void Effect_Init() {};
	virtual void Effect_Update(float timeDelta) {};
	virtual void Effect_Render() {};


};
