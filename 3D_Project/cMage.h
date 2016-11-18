#pragma once
#include "cBaseObject.h"
#include "cTestCommand.h"
#include "cTestCommand2.h"
#include "moveClass.h"


#define CONTROL_KEY 5

class cTerrain;
class cCamera;
class cInputHandler;
class cStateHandler;
class cWeapon;
class cSkill_Surround;


//��ų����Ʈ�� ���Ѱ�
class cQuadParticleEmitter;
class cPartcleEmitter;
class cParticleQuad;
class cParticle;



class cMage : public cBaseObject
{
private:
	//�����⿡ ���Ѱ�
	cSkill_Surround*     m_SkillSurround;

	//���Ϳ� ���Ѱ�
	cBaseObject*          m_pMonster;
	int                   m_StateCount;
	bool                  m_isTarget;
	bool                  m_MobCollision;
	bool                  m_MobHit;
	int                   m_MobHitCount;



	cWeapon*             pWeapon;
	

	cCamera*			m_camera;
	
	cBaseObject*           m_ATKBox;

	ACTOR_STATE			m_state;
	std::string			m_current_Ani;
	std::string			m_Aniname;
	std::map<int, bool> m_InputKeys;

	bool                m_isPetOn;
	bool				m_isMove;

	//������Ʈ�� �޾��ش�.
	cInputHandler*		m_pInput;
	moveClass*			m_pMove;


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
	bool                   m_isMagicATK;




public:
	cMage();
	~cMage();

	void BaseObjectEnable();
	void BaseObjectUpdate(float timeDelta);			//BaseObject �� Update �� ����....
	void ATKBoxRender();
	void WeaponRender();

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


	void SetCamera(cCamera* camera) { m_camera = camera; }

	cBaseObject* GetATKBox() { return m_ATKBox; }
	cTransform* GetATKBoxTrans() { return m_ATKBox->pTransform; }
	bool        GetIsPetOn() { return m_isPetOn; }
};


