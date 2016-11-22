#pragma once
#include "cSkill_Round.h"

class cSkill_DarkRain : public cSkill_Round
{


	// ½º³ë¿ì ½ºÅè
	cQuadParticleEmitter*  m_snowStrom;
	cQuadParticleEmitter*  m_snowStrom_under;
	cPartcleEmitter*       m_snow;
	bool                   m_isSnowStorm;
	int                    m_aniCount;



public:
	cSkill_DarkRain();
	~cSkill_DarkRain();

	void Effect_Init();
	void Effect_Update(float timeDelta);
	void Effect_Render();

};

