#pragma once
#include "cPlayer.h"
#include "cSkill_Surround.h"
#include "cSkill_Round.h"
#include "cSkill_SnowStorm.h"
#include "cSkill_DarkRain.h"
#include "cSkill_Front.h"
#include "cSkill_MagicShild.h"
#include "cSKill_Escape.h"
#include "cSkill_FlameRoad.h"


#define CONTROL_KEY 5


//��ų����Ʈ�� ���Ѱ�
class cQuadParticleEmitter;
class cPartcleEmitter;
class cParticleQuad;
class cParticle;

class cMage : public cPlayer
{
private:


	int                   m_StateCount;
	bool                  m_isTarget;
	bool                  m_MobCollision;
	bool                  m_MobHit;
	int                   m_MobHitCount;

	cBaseObject*           m_ATKBox;

	bool                m_isPetOn;

	// ��ų
	int m_atkCnt;
	float m_time;
	float m_fadeOut;



	int                    m_aniCount;

	//��ų�� ���� ��
	cSkill_Surround*     m_pSurroundSkill;
	cSkill_Round*        m_pRoundSkill;
	cSkill_SnowStorm*    m_pSkill_SnowStorm;
	cSkill_DarkRain*     m_pSkill_DarkRain;
	cSkill_Front*        m_pSkill_Front;
	cSkill_MagicShild*   m_pSkill_magicShild;
	cSkill_FlameRoad*    m_pSkill_FlameRoad;

	cSkill_Escape*       m_pSkill_Escape;


	//��Ÿ
	cQuadParticleEmitter*  m_magicATK;
	cQuadParticleEmitter*  m_magicATK2;





public:
	cMage();
	~cMage();

	void BaseObjectEnable();
	void BaseObjectUpdate(float timeDelta);			//BaseObject �� Update �� ����....
	void BaseObjectRender();
	void WeaponRender();
	void BaseObjectBoundBox();


private:


	//��
	void PetOnUpdate();

	void SkillInit();
	void SkillUpdate();


	//��ų
	void MagicATKInit();
	


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


