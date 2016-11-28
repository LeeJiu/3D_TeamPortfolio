#pragma once
#include "cBaseObject.h"
#include "cPartcleEmitter.h"
#include "cQuadParticleEmitter.h"

// 발사형 스킬들 
// 발사 버튼 클릭시 지정한 지점(또는 몬스터와의 거리까지 발사된다)



class cSkill_Shot : public cBaseObject
{
protected:


	bool               m_IsShot;           // 스킬 발사중이니?
	bool               m_IsInRange;        // 발사할 스킬이 사거리 안이니?
	bool               m_IsAttacking;      // 스킬이 닿아서 공격하고 있니?

	int                m_AttackingCount;   //공격 시전시간을 잰다
	int                m_AttackingTime;    //스킬이 머물러 있는 시간을 잰다

	float                   m_MaxDistance;   //전방 사거리

	D3DXVECTOR3             m_LookDir;         //바라보는 방향
	D3DXVECTOR3             m_CasterWorldPos;   //시전자의 위치
	D3DXVECTOR3             m_EnemyPos;       //공격할 몬스터의 포즈

	cBoundBox               m_BoundBox;


public:
	cSkill_Shot();
	~cSkill_Shot();

	void BaseObjectEnable(D3DXVECTOR3 casterWorldPos, float maxDistance, int attackingTime);

	void BaseObjectUpdate(float timeDelta, D3DXVECTOR3 casterWorldPos, D3DXVECTOR3 lookDir);

	void BaseObjectRender();

	void ShotSkill(); //스킬을 발사하려면
	void MakeAtk();



	bool GetIsShot() { return m_IsShot; }       // 발사 중이니
	bool GetIsAttacking() { return m_IsAttacking; } //공격하고있니?

protected:
	//이펙트 함수가 필요하면..

	virtual void Effect_Init() {};
	virtual void Effect_Update(float timeDelta) {};
	virtual void Effect_Render() {};


};

