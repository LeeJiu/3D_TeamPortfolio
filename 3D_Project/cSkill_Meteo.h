#pragma once
#include "cSkill_Round.h"

class cSkill_Meteo : public cSkill_Round
{

	cXMesh_Static*         m_lavaStone;
	cTransform*            m_lavaStoneTrans;
	float                  m_speed; //용성락 가속도

	// 스노우 스톰
	cQuadParticleEmitter*  m_snowStrom;
	cQuadParticleEmitter*  m_snowStrom_under;
	cPartcleEmitter*       m_snow;
	bool                   m_isSnowStorm;
	int                    m_aniCount;



public:
	cSkill_Meteo();
	~cSkill_Meteo();

	void Effect_Init();
	void Effect_Update(float timeDelta);
	void Effect_Render();

};
