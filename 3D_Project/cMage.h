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

//스킬이펙트에 관한것
class cQuadParticleEmitter;
class cPartcleEmitter;
class cParticleQuad;
class cParticle;



class cMage : public cBaseObject
{
private:

	cWeapon*             pWeapon;
	

	cCamera*			m_camera;
	
	cBoundBox*           m_ATKBox;
	cTransform*          m_ATKBoxTrans;

	ACTOR_STATE			m_state;
	std::string			m_current_Ani;
	std::string			m_Aniname;
	std::map<int, bool> m_InputKeys;

	bool                m_isPetOn;
	bool				m_isMove;

	//컴포넌트를 달아준다.
	cInputHandler*		m_pInput;
	moveClass*			m_pMove;


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

	//평타
	cQuadParticleEmitter*  m_magicATK;
	cQuadParticleEmitter*  m_magicATK2;
	bool                   m_isMagicATK;




public:
	cMage();
	~cMage();

	void BaseObjectEnable();
	void BaseObjectUpdate(float timeDelta);			//BaseObject 가 Update 때 실행....
	void ATKBoxRender();
	void WeaponRender();
	
	//펫
	void PetOnUpdate();

	void SkillInit();
	void SkillUpdate();
	void SkillRender();

	//스킬
	void MagicATKInit();
	void MagicShildInit();


	void SnowStormInit();
	void SnowStormUpdate();
	void SnowStormRender();


	void SetCamera(cCamera* camera) { m_camera = camera; }

	cBoundBox* GetATKBox() { return m_ATKBox; }
	cTransform* GetATKBoxTrans() { return m_ATKBoxTrans; }
	bool        GetIsPetOn() { return m_isPetOn; }
};


