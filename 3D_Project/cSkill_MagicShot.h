#pragma once
#include "cSkill_Shot.h"


class cSkill_MagicShot : public cSkill_Shot
{

	cQuadParticleEmitter*  m_magicATK;
	cQuadParticleEmitter*  m_magicATK2;

public:
	cSkill_MagicShot();
	~cSkill_MagicShot();

	virtual void Effect_Init();
	virtual void Effect_Update(float timeDelta);
	virtual void Effect_Render();
};

