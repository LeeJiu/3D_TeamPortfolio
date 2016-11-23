#pragma once
#include "cBaseObject.h"
#include "cPartcleEmitter.h"
#include "cQuadParticleEmitter.h"

class cSkill_Escape : public cBaseObject
{
protected:

	bool               m_IsSelect;       // 스킬 마우스 오버중이니
	bool               m_IsCasting;      // 스킬 캐스팅 중이니
	bool               m_IsInBuff;       // 버프 적용중이니
	bool               m_IsCoolTime;     // 스킬 쿨타임 중이니


	// 회피기를 누르면 지정한 범위로 이동해야한다.
	

	int                   m_CastTimeCount; //캐스팅 재는 타임
	int                   m_CastTime;      //캐스팅 풀 타임

	int                   m_CoolTimeCount; //쿨타임 잰다
	int                   m_CoolTime;      //쿨타임

	int                   m_BuffCount; //지속시간
	int                   m_BuffTime; //버프 지속시간

	float                 m_CastEfcScale;



	cQuadParticleEmitter*   m_CircleEfc;     //파란 범위 


	D3DXVECTOR3      m_CasterWorldPos; //시전자의 위치
	D3DXVECTOR3      m_LookDir;
	float            m_MoveLength;    //시전자가 직선으로 이동할 거리값
	D3DXVECTOR3      m_CasterMovePos; //직선으로 이동할 포지션


public:
	cSkill_Escape();
	~cSkill_Escape();

	void BaseObjectEnable(D3DXVECTOR3  casterWorldPos, float moveLength, int castTime, int buffCount, int coolTime);

	void BaseObjectUpdate(float timeDelta, D3DXVECTOR3 CasterWorldPos, D3DXVECTOR3 lookDir);

	void BaseObjectRender();

	void SelectSkill(); //UI에 스킬을 마우스 오버 했을때 불러주자

	void StartCasting(); //스킬을 사용한다 즉시시전 스킬도 이 함수를 불러주자

	int         GetBuffCount() { return m_BuffCount; }
	bool        GetIsInBuff() { return m_IsInBuff; } //회피버프 중이니?
	D3DXVECTOR3 GetEscapePos() { return pTransform->GetWorldPosition(); }

protected:
	//이펙트 함수가 필요하면..

	virtual void Effect_Init() {};
	virtual void Effect_Update(float timeDelta) {};
	virtual void Effect_Render() {};
};

