#pragma once
#include "cSkill_Surround.h"

class cSkill_Swing : public cSkill_Surround
{
private:
	// ½ºÀ®
	cQuadParticleEmitter*  m_SwingStrom;
	cQuadParticleEmitter*  m_SwingStrom_under;
	//cPartcleEmitter*       m_snow;
	bool                   m_Swing;
	int                    m_aniCount;

public:
	cSkill_Swing();
	~cSkill_Swing();

	void Effect_Init();
	void Effect_Update(float timeDelta);
	void Effect_Render();
};

