#pragma once
#include "cPlayer.h"

#define CONTROL_KEY 5


//��ų����Ʈ�� ���Ѱ�
class cQuadParticleEmitter;
class cPartcleEmitter;
class cParticleQuad;
class cParticle;



class cMage : public cPlayer
{
private:

	//���Ϳ� ���Ѱ�
	cBaseObject*          m_pMonster;
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





	//��ų�� ���� ��
	//���� �ǵ�
	cQuadParticleEmitter*  m_magicShild;
	bool                   m_isMagicShild;


	// ����� ����
	cQuadParticleEmitter*  m_snowStrom;
	cQuadParticleEmitter*  m_snowStrom_under;
	cPartcleEmitter*       m_snow;
	bool                   m_isSnowStorm;
	int                    m_aniCount;


	// �÷��� �ε�
	cQuadParticleEmitter*  m_flameRoad;
	cQuadParticleEmitter*  m_flameRoad2;
	cPartcleEmitter*       m_flameRoad3;
	bool                   m_isFlameRoad;
	bool                   m_flameRoad_cast;
	int                    m_flameRoad_cast_count;


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


private:
	//���Ϳ��� ��ȣ����
	void MonsterInit();

	void MonsterUpdate(float timeDelta);
	void MonsterCollision(float timeDelta); //�浹 üũ�ϰ�

	void MonsterRender();


	//��
	void PetOnUpdate();

	void SkillInit();
	void SkillUpdate();
	void SkillRender();

	//��ų
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


