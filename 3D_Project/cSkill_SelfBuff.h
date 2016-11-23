#pragma once
#include "cBaseObject.h"
#include "cPartcleEmitter.h"
#include "cQuadParticleEmitter.h"


class cSkill_SelfBuff : public cBaseObject
{
protected:

	bool               m_IsSelect;       // 스킬 마우스 오버중이니
	bool               m_IsCasting;      // 스킬 캐스팅 중이니
	bool               m_IsInBuff;       // 버프 적용중이니
	bool               m_IsCoolTime;     // 스킬 쿨타임 중이니


	// (셀프 버프이기 때문에 범위표시가 없다)


	int                   m_CastTimeCount; //캐스팅 재는 타임
	int                   m_CastTime;      //캐스팅 풀 타임

	int                   m_CoolTimeCount; //쿨타임 잰다
	int                   m_CoolTime;      //쿨타임

	int                   m_BuffCount; //지속시간
	int                   m_BuffTime; //버프 지속시간

	float                 m_CastEfcScale;


	D3DXVECTOR3      m_CasterWorldPos; //시전자의 위치



public:
	cSkill_SelfBuff();
	~cSkill_SelfBuff();

	void BaseObjectEnable(D3DXVECTOR3  casterWorldPos, int castTime, int buffCount, int coolTime);

	void BaseObjectUpdate(float timeDelta, D3DXVECTOR3 CasterWorldPos);

	void SelectSkill(); //UI에 스킬을 마우스 오버 했을때 불러주자

	void StartCasting(); //스킬을 사용한다 즉시시전 스킬도 이 함수를 불러주자


	bool GetIsInBuff() { return m_IsInBuff; } //공격하고있니?


protected:
	//이펙트 함수가 필요하면..

	virtual void Effect_Init() {};
	virtual void Effect_Update(float timeDelta) {};
	virtual void Effect_Render() {};


};

