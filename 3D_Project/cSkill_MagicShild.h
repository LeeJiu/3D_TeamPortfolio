#pragma once
#include "cSkill_SelfBuff.h"

class cSkill_MagicShild : public cSkill_SelfBuff
{

	cQuadParticleEmitter*  m_magicShild;
	cQuadParticleEmitter*  m_snowStrom_under;




public:
	cSkill_MagicShild();
	~cSkill_MagicShild();

	void Effect_Init();
	void Effect_Update(float timeDelta);
	void Effect_Render();

};

