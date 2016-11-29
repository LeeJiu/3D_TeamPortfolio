#pragma once
#include "cSkill_SelfBuff.h"


class cSkill_Burserk : public cSkill_SelfBuff
{

	cQuadParticleEmitter*  m_burserking;
	cQuadParticleEmitter*  m_burserking_under;
	cQuadParticleEmitter*  m_DarkStorm_under;


public:
	cSkill_Burserk();
	~cSkill_Burserk();

	void Effect_Init();
	void Effect_Update(float timeDelta);
	void Effect_Render();
};

