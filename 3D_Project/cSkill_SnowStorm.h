#pragma once
#include "cSkill_Surround.h"


class cSkill_SnowStorm : public cSkill_Surround
{

	//cXMesh_Static*         m_DarkDorm;


	// ½º³ë¿ì ½ºÅè
	cQuadParticleEmitter*  m_snowStrom;
	cQuadParticleEmitter*  m_snowStrom_under;
	cPartcleEmitter*       m_snow;
	bool                   m_isSnowStorm;
	int                    m_aniCount;


public:
	cSkill_SnowStorm();
	~cSkill_SnowStorm();

	void Effect_Init();
	void Effect_Update(float timeDelta);
	void Effect_Render();


};

