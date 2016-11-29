#pragma once
#include "cSkill_Round.h"


class cSkill_AmorCrash : public cSkill_Round
{
	//차지 이펙트
	cQuadParticleEmitter*  m_chargeEfc;
	cQuadParticleEmitter*  m_chargeEfc_under;


	// 스노우 스톰
	cQuadParticleEmitter*  m_snowStrom;
	cQuadParticleEmitter*  m_snowStrom_under;





	bool                   m_isSnowStorm;
	int                    m_aniCount;


public:
	cSkill_AmorCrash();
	~cSkill_AmorCrash();

	void Effect_Init();
	void Effect_Update(float timeDelta);
	void Effect_Render();
};

