#pragma once
#include "cBaseObject.h"

class cQuadParticleEmitter;


class cSkill_Round : public cBaseObject
{
private:


	bool               m_IsSelect;         // 스킬 마우스 오버중이니
	bool               m_IsCasting;        // 스킬 캐스팅 중이니
	bool               m_IsAttacking;      // 스킬 공격 중이니
	bool               m_IsCoolTime;       // 스킬 쿨타임 중이니



	cQuadParticleEmitter*   m_CircleEfc;     //파란 범위 
	cQuadParticleEmitter*   m_CastEfc;       //빨간 범위
	cQuadParticleEmitter*   m_SurroundEfc;   //사거리 범위


	int                   m_CastTime;
	int                   m_CastTimeMax;
	float                 m_CastEfcScale;
	int                   m_MaxDistance; //최대 사거리
	D3DXVECTOR3           m_MousePos;


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
	cSkill_Round();
	~cSkill_Round();

	void BaseObjectEnable(float surroundLength, int castTime, int maxDistance);

	void BaseObjectUpdate(D3DXVECTOR3 CasterWorldPos, float timeDelta, D3DXVECTOR3 mousePos);

	void BaseObjectRender();

	void SelectSkill(); //스킬을 선택하자

	void StartCasting();

	void UseSkill();  //스킬을 사용하자

};



