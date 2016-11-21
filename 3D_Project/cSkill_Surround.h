#pragma once
#include "cBaseObject.h"

class cQuadParticleEmitter;

class cSkill_Surround : public cBaseObject
{

private:
	
	bool               m_IsSelect; // 스킬 마우스 오버중이니
	bool               m_IsCasting; // 스킬 캐스팅 중이니
	bool               m_IsAttacking; // 스킬 공격 중이니
	bool               m_IsCoolTime;  // 스킬 쿨타임 중이니



	cQuadParticleEmitter*   m_CircleEfc;
	cQuadParticleEmitter*   m_CastEfc;
	int                   m_CastTime;
	int                   m_CastTimeMax;
	float                   m_CastEfcScale;

	D3DXVECTOR3      m_CasterWorldPos; //시전자의 위치
	float            m_SurroundLength; //범위



	cBoundSphere     m_BoundSphere;
	cTransform*      m_CasterPos;       //시전자의 위치
	float            m_SurroundRadius;  //시전 범위
	

	// int              m_HitMax;          //타격인원
	float            m_tickTime;
	float            m_timeTemp;

	int              m_Damage;
	int              m_UseSP;




	bool             m_IsHit;              //적이 맞았니?


public:
	cSkill_Surround();
	~cSkill_Surround();

	void BaseObjectEnable(D3DXVECTOR3  casterWorldPos, float surroundLength, int castTime);

	void BaseObjectUpdate(float timeDelta, D3DXVECTOR3 CasterWorldPos);

	void BaseObjectRender();

	void SelectSkill(); //스킬을 선택하자

	void StartCasting();

	void UseSkill();  //스킬을 사용하자



};

