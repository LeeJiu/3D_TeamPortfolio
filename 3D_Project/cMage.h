#pragma once
#include "cPlayer.h"

#define CONTROL_KEY 5


//스킬이펙트에 관한것
class cQuadParticleEmitter;
class cPartcleEmitter;
class cParticleQuad;
class cParticle;



class cMage : public cPlayer
{
private:

	//몬스터에 관한것
	cBaseObject*          m_pMonster;
	int                   m_StateCount;
	bool                  m_isTarget;
	bool                  m_MobCollision;
	bool                  m_MobHit;
	int                   m_MobHitCount;

	cBaseObject*           m_ATKBox;

	bool                m_isPetOn;

	// 스킬
	int m_atkCnt;
	float m_time;
	float m_fadeOut;





	//스킬에 관한 것
	//매직 실드
	cQuadParticleEmitter*  m_magicShild;
	bool                   m_isMagicShild;


	// 스노우 스톰
	cQuadParticleEmitter*  m_snowStrom;
	cQuadParticleEmitter*  m_snowStrom_under;
	cPartcleEmitter*       m_snow;
	bool                   m_isSnowStorm;
	int                    m_aniCount;


	// 플레임 로드
	cQuadParticleEmitter*  m_flameRoad;
	cQuadParticleEmitter*  m_flameRoad2;
	cPartcleEmitter*       m_flameRoad3;
	bool                   m_isFlameRoad;
	bool                   m_flameRoad_cast;
	int                    m_flameRoad_cast_count;


	//평타
	cQuadParticleEmitter*  m_magicATK;
	cQuadParticleEmitter*  m_magicATK2;





public:
	cMage();
	~cMage();

	void BaseObjectEnable();
	void BaseObjectUpdate(float timeDelta);			//BaseObject 가 Update 때 실행....
	void BaseObjectRender();
	void WeaponRender();


private:
	//몬스터와의 상호교류
	void MonsterInit();

	void MonsterUpdate(float timeDelta);
	void MonsterCollision(float timeDelta); //충돌 체크하고

	void MonsterRender();


	//펫
	void PetOnUpdate();

	void SkillInit();
	void SkillUpdate();
	void SkillRender();

	//스킬
	void MagicATKInit();
	void MagicShildInit();

	void FlameRoadInit();



	void SnowStormInit();
	void SnowStormUpdate();
	void SnowStormRender();

	void Damage(float damage);

	void Attack01();
	void Attack02();
	void Attack03();

	void SKILL01();
	void SKILL02();
	void SKILL03();
	void SKILL04();



	void SetCamera(cCamera* camera) { m_camera = camera; }

	cBaseObject* GetATKBox() { return m_ATKBox; }
	cTransform* GetATKBoxTrans() { return m_ATKBox->pTransform; }
	bool        GetIsPetOn() { return m_isPetOn; }
};


