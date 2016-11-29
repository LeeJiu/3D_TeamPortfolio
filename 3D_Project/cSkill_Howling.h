#pragma once
#include "cSkill_Surround.h"

class cSkill_Howling : public cSkill_Surround
{
	//cQuadParticleEmitter*  m_snowStrom;
	//cQuadParticleEmitter*  m_snowStrom_under;
	//cPartcleEmitter*       m_snow;
	bool                   m_howling;
	int                    m_aniCount;

public:
	cSkill_Howling();
	~cSkill_Howling();

	void Effect_Init();
	void Effect_Update(float timeDelta);
	void Effect_Render();

};

